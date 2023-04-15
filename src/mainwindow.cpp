#include "mainwindow.h"
#include "ui_mainwindow.h"

//constructor that initializes the main window and its UI components
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupConnections();
}

//destructor
MainWindow::~MainWindow() {
    mainMenu->deleteAllSubMenus();
    delete mainMenu;
    delete ui;

    for (int i = 0; i < records.size(); i++) {
        delete records[i];
    }

    delete batteryTimer;
    delete setting;
    delete database;
}

//set up the connections and initialize menu, database, setting, and UI elements
void MainWindow::setupConnections(){
    // Initialize member variables
    currentTimerCount = -1;
    bpProgress = 0;
    bpIsIncreasing = true;
    currentBattery = 100.0;
    batteryTimer = new QTimer();
    currentSession = nullptr;
    setting = new Setting();

    //set initial sensor status to off
    sensorOn = false;

    //create database connection
    database = new DBController();

    //Load records from the database
    initializeHistory();

    //create and initialize the main menu tree
    currentMenu = new Menu("MAIN MENU", {"START NEW SESSION","HISTORY", "SETTING"}, nullptr);
    mainMenu = currentMenu;
    initializeMenu(currentMenu);

    // Initialize the main menu view
    ui->menuListWidget->addItems(currentMenu->getMenuOptions());
    ui->menuListWidget->setCurrentRow(0);
    ui->menuLabel->setText(currentMenu->getName());

    //set initial power status to off
    powerOn = false;
    changePowerStatus();

    //connect the power button to the powerSwitch slot
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerSwitch);

    //connect the battery charge button to the chargeBattery slot
    connect(ui->batteryPushButton, &QPushButton::released, this, &MainWindow::chargeBattery);

    //connect the battery level spinbox to the changeBatteryCapacity slot
    connect(ui->batterySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeBatteryCapacity);

    //Initialize battery consumption timer
    connect(batteryTimer, &QTimer::timeout, [this] () {consumeBattery(0.2);});

    //connect interface buttons to their corresponding slots
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::scrollUp);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::scrollDown);
    connect(ui->selectButton, &QPushButton::pressed, this, &MainWindow::selectAction);
    connect(ui->menuButton, &QPushButton::pressed, this, &MainWindow::backToMainMenu);
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::backToPrevious);
    connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::parameterPlus);
    connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::parameterMinus);

    //connect sensor button to toggle sensor activation
    connect(ui->sensorButton, &QPushButton::clicked, [this]() {activateSensor(!sensorOn);});

    // Initialize battery levels
    ui->batterySpinBox->setValue(currentBattery);
    
    //set initial visibility for stacked widget and labels
    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);
    ui->lowLabel->setVisible(false);
    ui->medLabel->setVisible(false);
    ui->highLabel->setVisible(false);
}

//initialize the main menu and its submenus and populate with options
void MainWindow::initializeMenu(Menu* menu) {
    QStringList settingList;

    //create submenu options for setting menu
    settingList.append("RESET");
    settingList.append("BREATH PACER INTERVAL: 10");
    settingList.append("CHALLENGE LEVEL: 1");

    //create submenu options for history menu
    Menu* sessionMenu = new Menu("START NEW SESSION", {}, menu);
    Menu* historyMenu = new Menu("HISTORY", allRecords, menu);
    Menu* settingMenu = new Menu("SETTINGS", settingList, menu);

    //add submenus to the main menu
    menu->addChildMenu(sessionMenu);
    menu->addChildMenu(historyMenu);
    menu->addChildMenu(settingMenu);

    //create reset menu under the settings menu
    Menu* resetMenu = new Menu("RESET", {"YES","NO"}, settingMenu);
    settingMenu->addChildMenu(resetMenu);

    //create menus and submenus for each record in history menu
    for (const QString &str : allRecords) {
        //set "yyyy-MM-dd hh:mm:ss" part as the menu name
        Menu* record = new Menu(str.left(19), {"VIEW", "DELETE"}, historyMenu);

        //add view and delete submenus under each record menu
        record->addChildMenu(new Menu("VIEW",{}, record));
        record->addChildMenu(new Menu("DELETE", {}, record));

        historyMenu->addChildMenu(record);
    }
}

//initialize History menu
void MainWindow::initializeHistory() {
    //load records from the database
    allRecords = database->getHistory();

    //create corresponding Record objects and add them to records
    for (const QString& str : allRecords) {
        //convert the datetime string to a QDateTime object
        QDateTime datetime = QDateTime::fromString(str.mid(0,19), "yyyy-MM-dd HH:mm:ss");

        //create the Record object for the datetime and add it to the QVector
        Record* record = nullptr;
        database->getRecord(datetime, &record);
        records.append(record);
    }
}

//the function starts a new session, initializing and displaying the session view.
//It also sets up the timer and connects it to update session data periodically.
void MainWindow::startSession() {
    //create a Session object
    currentSession = new Session();

    //set initial visibility for labels and widgets
    ui->sensorButton->setDisabled(false);
    ui->lowLabel->setVisible(false);
    ui->medLabel->setVisible(false);
    ui->highLabel->setVisible(false);
    ui->contact->setVisible(sensorOn);
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
    plot(); //generate initial empty plot

    //connect session timer to update all session data and session view
    QTimer* sessionTimer = currentSession->getTimer();
    currentTimerCount = 0;
    connect(sessionTimer, &QTimer::timeout, this, &MainWindow::sessionTimerSlot);

    //start the session timer if the sensor is on
    if (sensorOn == true) {
        sessionTimer->start(1000);
        batteryTimer->stop();
    }
}

//slot function for the session timer
//this slot function is responsible for updating session and breath pacer
void MainWindow::sessionTimerSlot() {
    currentTimerCount++;

    // change length in sessionView and update breath pacer every 1 second
    ui->lengthValue->setText(QString("%1:%2").arg(QString::number(currentTimerCount / 60),2,'0').arg(QString::number(currentTimerCount % 60),2,'0'));
    updateBP(setting->getBpInterval());

    // update session data every 5 seconds
    if (currentTimerCount % 5 == 0 && currentBattery > 0) {
        updateSession();
    }
}

//Update the current session, including battery consumption, session data, and the session view.
//It also checks whether the session has reached maximum duration or if the batterylevel is too low to continue.
void MainWindow::updateSession() {
    //consume battery during the session
    consumeBattery(0.5);

    //session can only update when battery is above 15%
    if (currentBattery > 15.0) {
        //update session data,session vew and HRV graph
        currentSession->updateAll(setting->getChallengeLevel());
        updateSessionView();
        plot();

        //check if the session has reached its maximum duration and end it if needed
        if (currentTimerCount >= MAX_SESSION_DURATION) {
            endSession();
        }
    }else {
        qDebug() << "Battery is under 15%, this session cannot continue, please charge";
        endSession();
    }
}

//end the current session, stop the timer and calculate the percentage of coherence levels
//save the session data to database and Record and display a review
void MainWindow::endSession() {
    //stop and disconnect the session timer
    currentSession->getTimer()->stop();
    currentSession->getTimer()->disconnect();

    batteryTimer->start(10000);

    //calculate coherence level percentages
    currentSession->calCLPercentage();

    //fill up enough data according to the actual running time
    if (currentTimerCount > currentSession->getLength()) {
        QVector<double>* newDoubles = currentSession->simulateHeartIntervals(currentTimerCount - currentSession->getLength());
        QVector<QPointF>* newPoints = currentSession->calPoints(&newDoubles);
        currentSession->updateHRVData(newPoints);
        delete newDoubles;
    }

    //save new record to database and check its validity
    bool flag = database->addRecord(currentSession->getStartTime(),setting->getChallengeLevel(),currentTimerCount, currentSession->getLowPercentage(),
                        currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                        (currentSession->getAchievementScore()*5)/currentSession->getLength(),
                        currentSession->getAchievementScore(), *(currentSession->getHRVData()));
    Record* newRecord = new Record(currentSession->getStartTime(),setting->getChallengeLevel(),currentTimerCount, currentSession->getLowPercentage(),
                                   currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                                   currentSession->getAchievementScore()*5/currentSession->getLength(),
                                   currentSession->getAchievementScore(), *(currentSession->getHRVData()));

    //only add it in memory and create history option for it if it is valid
    if (flag) {
        records.push_back(newRecord);

        //add new menu option to the history tab after a session ends
        Menu* historyMenu = mainMenu->get(1);
        Menu* newHistoryRecord = new Menu(currentSession->getStartTime().toString("yyyy-MM-dd HH:mm:ss"), {"VIEW", "DELETE"}, historyMenu);
        newHistoryRecord->addChildMenu(new Menu("VIEW",{}, newHistoryRecord));
        newHistoryRecord->addChildMenu(new Menu("DELETE", {}, newHistoryRecord));
        historyMenu->addChildMenu(newHistoryRecord);

        //update history menu options with the new record
        QString newRecordString = newHistoryRecord->getName() + "\n"
            + "   Challenge Level: Level " + QString::number(newRecord->getchallengeLevel()) + "\n"
            + "   Length: " + QString::number(currentTimerCount / 60)
            + ((currentTimerCount % 60 < 10) ? ":0" + QString::number(currentTimerCount % 60) : ":" + QString::number(currentTimerCount % 60));
        QStringList temp = historyMenu->getMenuOptions();
        temp.push_back(newRecordString);
        historyMenu->setMenuOptions(temp);
    }else {
        delete newRecord;
    }

    //reset session-related variables and delete the current session
    currentTimerCount = -1;
    sensorOn = false;
    bpProgress = 0;
    bpIsIncreasing = true;

    delete currentSession;
    currentSession = nullptr;

    //reset the UI elements
    ui->bp->setValue(0);
    ui->lowLabel->setVisible(false);
    ui->medLabel->setVisible(false);
    ui->highLabel->setVisible(false);
    ui->coherenceValue->setText("0.00");
    ui->lengthValue->setText("00:00");
    ui->achievementScore->setText("0.00");
    ui->sensorButton->setDisabled(true);

    //display review right after session ends if this record is valid
    if (flag) {
        qDebug() << "Session ends.";
        displayReview(newRecord);
    }else {
        backToMainMenu();
    }
}

//update session view and display the appropriate coherence level label (low, medium, or high)
void MainWindow::updateSessionView() {
    ui->coherenceValue->setText(QString::number(currentSession->getCoherenceScore(),'f',2));
    ui->achievementScore->setText(QString::number(currentSession->getAchievementScore(),'f',2));
    int coherenceLevel = currentSession->getCoherenceLevel();
    switch(coherenceLevel) {
        case 0 :
            ui->lowLabel->setVisible(true);
            ui->medLabel->setVisible(false);
            ui->highLabel->setVisible(false);
            break;
        case 1 :
            ui->lowLabel->setVisible(false);
            ui->medLabel->setVisible(true);
            ui->highLabel->setVisible(false);
            break;
        case 2 :
            ui->lowLabel->setVisible(false);
            ui->medLabel->setVisible(false);
            ui->highLabel->setVisible(true);
            break;
        default:
            ui->lowLabel->setVisible(true);
            ui->medLabel->setVisible(false);
            ui->highLabel->setVisible(false);
            break;
    }
}

//display a review of the session data and HRV graph
void MainWindow::displayReview(Record* newRecord) {
    //display indicators' values
    ui->date->setText((newRecord->getStartTime()).toString("yyyy-MM-dd hh:mm:ss"));
    ui->avgScore->setText(QString::number(newRecord->getAverageCoherence(),'f',2));
    ui->achScore->setText(QString::number(newRecord->getAchievementScore(),'f',2));
    ui->lenScore->setText(QString::number(newRecord->getLength())+"s");
    ui->chaLvl->setText(QString::number(newRecord->getchallengeLevel()));
    ui->lowPercentage->setText(QString::number(newRecord->getLowPercentage(),'f',2)+"%");
    ui->lowPercentage->setStyleSheet("color: #a40000;");
    ui->mediumPercentage->setText(QString::number(newRecord->getMedPercentage(),'f',2)+"%");
    ui->mediumPercentage->setStyleSheet("color: #204a87;");
    ui->highPercentage->setText(QString::number(newRecord->getHighPercentage(),'f',2)+"%");
    ui->highPercentage->setStyleSheet("color: #4e9a06;");

    //show hrv graph
    plotHistory(newRecord);
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(1);

    qDebug() << "Display the record review.";
}

//disable user UI for power-off, and enable user UI for power-on
void MainWindow::changePowerStatus() {
    //show or hide UI elements based on power status
    ui->menuListWidget->setVisible(powerOn);
    ui->menuLabel->setVisible(powerOn);
    ui->status->setVisible(powerOn);   //display battery level and sensor detector
    ui->stackedWidget->setVisible(powerOn);

    //ensure the device stay on main page when power is on
    if (powerOn) {
        MainWindow::backToMainMenu();
        ui->sensorButton->setChecked(false);
        activateSensor(false);
    }

    //enable or disable UI buttons based on power status
    ui->upButton->setEnabled(powerOn);
    ui->downButton->setEnabled(powerOn);
    ui->leftButton->setEnabled(powerOn);
    ui->rightButton->setEnabled(powerOn);
    ui->menuButton->setEnabled(powerOn);
    ui->selectButton->setEnabled(powerOn);
    ui->backButton->setEnabled(powerOn);
    ui->sensorButton->setEnabled(powerOn);
}

//toggle the power state of the device and handle power off events during a session
void MainWindow::powerSwitch() {
    if (currentBattery > 0) {
        powerOn = !powerOn;
        changePowerStatus();
        if (powerOn) {
            batteryTimer->start(10000);
        }else {
            batteryTimer->stop();
        }
    }

    //handle poweroff event during session measurement
    if (currentTimerCount != -1) {
        //save Record and end session
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
            backToMainMenu();
        }

        activateSensor(false);
    }

    //print the message to the console for user interation
    if (powerOn){
        qDebug()<< "The device has been turned on." ;
    }else {
        qDebug()<< "The device has been turned off." ;
    }
}

//charge the battery to full capacity
void MainWindow::chargeBattery() {

    int fullyCharged = 100;
    changeBatteryCapacity(fullyCharged);
    qDebug() << "The battery has been charged to full capacity.";
}

//scroll up through the menu options
void MainWindow::scrollUp() {

    int nextIndex = ui->menuListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = ui->menuListWidget->count() - 1;
    }

    ui->menuListWidget->setCurrentRow(nextIndex);
    if (currentMenu->getName()!= "START NEW SESSION" && currentMenu->getName()!= "VIEW"){
        qDebug() << "Move to previous option";
    }
}

//scroll down through the menu options
void MainWindow::scrollDown() {

    int nextIndex = ui->menuListWidget->currentRow() + 1;

    if (nextIndex > ui->menuListWidget->count() - 1) {
        nextIndex = 0;
    }

    ui->menuListWidget->setCurrentRow(nextIndex);
    if (currentMenu->getName()!= "START NEW SESSION" && currentMenu->getName()!= "VIEW"){
        qDebug() << "Move to next option";
    }
}

//handle the select button action
void MainWindow::selectAction() {
    //when user presses the button during the measurement session
    if (currentTimerCount != -1) {
        //save record and end session
        if (currentMenu->getName() == "START NEW SESSION" && currentTimerCount!=0) {
            endSession();
            return;
        }
    }

    int index = ui->menuListWidget->currentRow();
    if (index < 0) {return;}

    //handle when user presses select button during BPInterval setting scenario
    if (currentMenu->getName() == "SETTINGS" && (index==1 || index== 2)){
        qDebug() << "Please use left/right button to adjust parameters.";
        return;
    }

    //reset to initial state
    if (currentMenu->getName() == "RESET") {
        if (currentMenu->getMenuOptions()[index] == "YES") {
            for (int i = 0; i < records.size(); i++) {
                delete records[i];
            }
            records.clear();

            database->reset();
            setting->reset();

            //delete original main menu object and regenerate a new menu object for resetting, then navigate to main menu
            mainMenu->deleteAllSubMenus();
            initializeHistory();
            currentMenu = new Menu("MAIN MENU", {"START NEW SESSION","HISTORY", "SETTING"}, nullptr);
            mainMenu = currentMenu;
            initializeMenu(currentMenu);
            qDebug() << "The device has been reset to the initial state.";
            backToMainMenu();

            return;
        }else {
            backToPrevious();
            return;
        }
    }

    //display child items
    if (currentMenu->get(index)->getMenuOptions().length() > 0) {
        currentMenu = currentMenu->get(index);
        updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
        qDebug() << "Enter child menu " + currentMenu->getName();
     //if user chooses the start a session option
    }else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->get(index)->getName() == "START NEW SESSION") {
        if (currentBattery <= 15.0) {
            qDebug()<<"Battery is under 15%, cannot start a new session, please charge";
            return;
        }

        //update new menu info
        currentMenu = currentMenu->get(index);
        updateMenu("Measuring", {});
        qDebug() << "Started a new session, sensor is off, HR contact is off. Please press sensor button to start measuring.";
        startSession();
    }
    //delete a record
    else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->get(index)->getName() == "DELETE") {
        deleteAction();
    }
    //display record summary
    else if (currentMenu->get(index)->getName() == "VIEW") {
        viewAction(index);
    }
    //remind user if there is no available history record
    else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->get(index)->getName() == "HISTORY") {
        qDebug() << "No history records available";
    }
}

//display a record summary based on the selected index
void MainWindow::viewAction(int index){
    QString datetimeString = currentMenu->getName().left(19); //get datetime Qstring
    currentMenu = currentMenu->get(index);
    updateMenu("Record", {});
    for (Record* record : records) {
        if (record->getStartTime().toString("yyyy-MM-dd HH:mm:ss") == datetimeString) { // compare menu string to every record's QDateTime string
            displayReview(record);
            return;
        }
    }
    //handles cases where a matching record is not found.
    qDebug() << "No matching record found";
}

//delete a record and navigates back to the parent menu after the deletion is complete
void MainWindow::deleteAction(){
    //get the datetime string of the current menu and convert to a QDateTime object
    QString datetimeString = currentMenu->getName().left(19);
    QDateTime datetime = QDateTime::fromString(datetimeString, "yyyy-MM-dd HH:mm:ss");

    //iterate through the records list
    for (int i = 0; i < records.size(); i++) {
        //if the record's start time matches the datetime string, delete the record
        if (records[i]->getStartTime().toString("yyyy-MM-dd HH:mm:ss") == datetimeString) {
            database->deleteRecord(datetime);
            delete records[i];
            records.remove(i);
            //qDebug() << "Record deleted successfully!";
            break;
        }
    }

    Menu* tempMenu = currentMenu;
    backToPrevious(); //navigate back to the parent menu

    //delete the child menu from the current menu and update the menu display
    currentMenu->deleteChildMenu(tempMenu);
    updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
}

//update the user interface menu with the given menu name and options.
void MainWindow::updateMenu(const QString menuName, const QStringList menuOptions) {
    //clear current menu items, add the new menu options to the menu list, and set the current row to the first option
    ui->menuListWidget->clear();
    ui->menuListWidget->addItems(menuOptions);
    ui->menuListWidget->setCurrentRow(0);

    //set the menu label to display the menu name and apply style
    ui->menuLabel->setText(menuName);
    ui->menuLabel->setStyleSheet("QLabel { font-weight: 600; color: #e9b96e; qproperty-alignment: 'AlignHCenter | AlignVCenter'; background-color: white;}");
}

//mainMenu button slot, which navigates the user interface back to the main menu
void MainWindow::backToMainMenu() {

    //handle session interuption
    if (currentTimerCount != -1) {
        //save record and end session
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
            return;
        }
    }

    currentMenu = mainMenu;
    updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());

    //hide the stacked widget and HR contact indicator
    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);

    if (currentMenu->getName()!= "MAIN MENU"){
        qDebug() << "Back to main menu.";
    }else{
        return;
    }
}

//back button slot, which navigates the user interface back to the previous menu
void MainWindow::backToPrevious() {

    //handle session interuption
    if (currentTimerCount != -1) {
        //save record
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
            return;
        }
    }

    if (currentMenu->getName() == "MAIN MENU") {
        ui->menuListWidget->setCurrentRow(0);
        qDebug() << "Already at main menu.";
    }
    else {
        currentMenu = currentMenu->getParentMenu();
        updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
        qDebug() << "Back to previous menu.";
    }

    //hide the stacked widget and HR contact indicator
    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);

}

//increment a selected parameter in the settings menu
void MainWindow::parameterPlus() {
    int index = ui->menuListWidget->currentRow();
    int currentChallengeLevel = setting->getChallengeLevel();
    int currentBpInterval = setting->getBpInterval();

    if (currentMenu->getName() == "SETTINGS"){
        //if the breath pacer interval is selected and within the allowed range
        if (index == 1 && currentBpInterval <=29){
            //increment the breath pacer interval and update the settings
            setting->setBpInterval(currentBpInterval+1);

            //update the settings menu display
            QStringList settingList;
            settingList.append("RESET");
            settingList.append("BREATH PACER INTERVAL: " + (QString::number(setting->getBpInterval())));
            settingList.append("CHALLENGE LEVEL: " + (QString::number(setting->getChallengeLevel())));

            ui->menuListWidget->clear();
            ui->menuListWidget->addItems(settingList);
            ui->menuListWidget->setCurrentRow(1);
            ui->menuLabel->setText(currentMenu->getName());
            currentMenu->setMenuOptions(settingList);
            qDebug() << "BP Interval has increased to " + (QString::number(setting->getBpInterval()));

            //if the challenge level is selected and within the allowed range
        }else if (index == 2 && currentChallengeLevel <=3){
            //increment the challenge level and update the settings
            setting->setChallengeLevel(currentChallengeLevel+1);

            //update the settings menu display
            QStringList settingList;
            settingList.append("RESET");
            settingList.append("BREATH PACER INTERVAL: " + (QString::number(setting->getBpInterval())));
            settingList.append("CHALLENGE LEVEL: " + (QString::number(setting->getChallengeLevel())));

            ui->menuListWidget->clear();
            ui->menuListWidget->addItems(settingList);
            ui->menuListWidget->setCurrentRow(2);
            ui->menuLabel->setText(currentMenu->getName());
            currentMenu->setMenuOptions(settingList);
            qDebug() << "Challenge level has increased to " + (QString::number(setting->getChallengeLevel()));
        }else if (currentBpInterval == 30 || currentChallengeLevel == 4){
            qDebug() << "Breath Pacer interval is between 1-30 and challenge level is between 1 and 4.";
        }
    }
}

//decrement a selected parameter in the settings menu
void MainWindow::parameterMinus() {

    int index = ui->menuListWidget->currentRow();
    int currentChallengeLevel = setting->getChallengeLevel();
    int currentBpInterval = setting->getBpInterval();

    if (currentMenu->getName() == "SETTINGS"){
        //if the breath pacer interval is selected and within the allowed range
        if (index == 1 && currentBpInterval >1){
            //decrement the breath pacer interval and update the settings
            setting->setBpInterval(currentBpInterval-1);

            //update the settings menu display
            QStringList settingList;
            settingList.append("RESET");
            settingList.append("BREATH PACER INTERVAL: " + (QString::number(setting->getBpInterval())));
            settingList.append("CHALLENGE LEVEL: " + (QString::number(setting->getChallengeLevel())));

            ui->menuListWidget->clear();
            ui->menuListWidget->addItems(settingList);
            ui->menuListWidget->setCurrentRow(1);
            ui->menuLabel->setText(currentMenu->getName());
            currentMenu->setMenuOptions(settingList);
            qDebug() << "BP Interval has decreased to " + (QString::number(setting->getBpInterval()));

        //if the challenge level is selected and within the allowed range
        }else if (index == 2 && currentChallengeLevel >1){
            //decrement the challenge level and update the settings
            setting->setChallengeLevel(currentChallengeLevel-1);

            //update the settings menu display
            QStringList settingList;
            settingList.append("RESET");
            settingList.append("BREATH PACER INTERVAL: " + (QString::number(setting->getBpInterval())));
            settingList.append("CHALLENGE LEVEL: " + (QString::number(setting->getChallengeLevel())));

            ui->menuListWidget->clear();
            ui->menuListWidget->addItems(settingList);
            ui->menuListWidget->setCurrentRow(2);
            ui->menuLabel->setText(currentMenu->getName());
            currentMenu->setMenuOptions(settingList);
            qDebug() << "Challenge level has decreased to " + (QString::number(setting->getChallengeLevel()));
        }else if (currentBpInterval == 1 || currentChallengeLevel == 1){
            qDebug() << "Breath Pacer interval is between 1-30 and challenge level is between 1 and 4.";
        }
    }
}

//slot to change the battery level from the control panel
void MainWindow::changeBatteryCapacity(double capacity) {

    if (capacity > 0 && capacity <= 100) {
        currentBattery = capacity;
        ui->battery->setValue(currentBattery);
        ui->batterySpinBox->setValue(currentBattery);
    }else {
        if (currentTimerCount != -1) {
            backToPrevious();
        }
        powerSwitch();
        currentBattery = 0;
        ui->battery->setValue(currentBattery);
        ui->batterySpinBox->setValue(currentBattery);
    }

    //change the color of battery indicator based on current battery capacity
    if (currentBattery < 15.0) {
        ui->battery->setStyleSheet("QProgressBar { selection-background-color: rgb(164, 0, 0);}");
    }else if (currentBattery < 30.0){
        ui->battery->setStyleSheet("QProgressBar { selection-background-color: rgb(196, 160, 0);}");
    }else {
        ui->battery->setStyleSheet("QProgressBar { selection-background-color: rgb(0, 150, 0);}");
    }
}

//start or stop the session timer based on the sensor state
void MainWindow::activateSensor(bool checked) {
    sensorOn = checked;

    if (currentTimerCount != -1) {
        //if the sensor is off, stop the session timer
        if (!sensorOn) {
            currentSession->getTimer()->stop();
            batteryTimer->start(10000);
            qDebug() << "Sensor is off, HR contact is off. The measurement stops.";
        }
        //if the sensor is on, start the session timer with a 1000ms interval
        else {
            currentSession->getTimer()->start(1000);
            batteryTimer->stop();
            qDebug() << "Sensor is on, HR contact is on. The measurement starts.";
        }
        ui->contact->setVisible(sensorOn);
    }
}

//decrease the battery capacity based on the given consumption value
void MainWindow::consumeBattery(double consumption) {
    changeBatteryCapacity(currentBattery - consumption);
    if (currentBattery < 15.0 && powerOn) {qDebug("Battery is under 15%, need to be charged");}
}

//plot the HRV graph during a session measurement
void MainWindow::plot() {
    //get the HRV data points from the current session
    QVector<QPointF>* points = currentSession->getHRVData();
    int size = points->size();

    //initialize variables for data manipulation
    double previousX = 0;
    QVector<double> x(size), y(size);

    //prepare data for plotting
    for (int i=0; i<size; i++) {
      x[i] = points->at(i).x() + previousX;
      y[i] = points->at(i).y();
      previousX = x[i];
    }
    //add a new graph to the sessionGraph widget and set the data
    ui->sessionGraph->QCustomPlot::addGraph();
    ui->sessionGraph->graph(0)->setData(x, y);
    //set axis labels and ranges
    ui->sessionGraph->xAxis->setLabel("Time (s)");
    ui->sessionGraph->yAxis->setLabel("HR (bps)");
    ui->sessionGraph->xAxis->setRange(0, MAX_SESSION_DURATION);
    ui->sessionGraph->yAxis->setRange(55, 105);
    //replot the graph to update the display
    ui->sessionGraph->replot();
}

//plot the HRV graph for record review
void MainWindow::plotHistory(Record* record) {
    //get the HRV data points from the record
    QVector<QPointF> points = record->getHrvGraph();
    int size = points.size();

    double previousX = 0;
    QVector<double> x(size), y(size);

    //prepare data for plotting
    for (int i=0; i<size; i++) {
      x[i] = points[i].x() + previousX;
      y[i] = points[i].y();
      previousX = x[i];
    }

    //add a new graph to the historyGraph widget and set the data
    ui->historyGraph->QCustomPlot::addGraph();
    ui->historyGraph->graph(0)->setData(x, y);
    //set axis labels and ranges
    ui->sessionGraph->xAxis->setLabel("Time (s)");
    ui->sessionGraph->yAxis->setLabel("HR (bps)");
    ui->historyGraph->xAxis->setRange(0, record->getLength());
    ui->historyGraph->yAxis->setRange(55, 105);
    //replot the graph to update the display
    ui->historyGraph->replot();
}

//update the breath pacer progress based on the given interval
void MainWindow::updateBP(int interval) {
    if (bpIsIncreasing) {
        //calculate the progress increment based on the interval
        bpProgress += (200/interval);

        if (bpProgress >= 100) {
            bpProgress = 100;
            //indicate that the progress should start decreasing
            bpIsIncreasing = false;
        }
    } else {
        //calculate the progress decrement based on the interval
        bpProgress -= (200/interval);
        if (bpProgress <= 0) {
            bpProgress = 0;
            //indicate that the progress should start increasing
            bpIsIncreasing = true;
        }
    }
    //set the updated progress value to the bp widget
    ui->bp->setValue(bpProgress);
}
