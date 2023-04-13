#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupConnections();
}

//destructor
MainWindow::~MainWindow() {
    //mainMenu->deleteAllSubMenus();
    delete mainMenu;
    delete ui;

    for (int i = 0; i < records.size(); i++) {
        delete records[i];
    }

    delete database;
}

void MainWindow::setupConnections(){
    // Initialize timer counter
    currentTimerCount = -1;
    bpProgress = 0;
    bpIsIncreasing = true;
    currentBattery = 100.0;
    currentSession = nullptr;
    setting = new Setting();

    //set initial sensor status
    sensorOn = false;

    //create database connection
    database = new DBController();

    //Load records from the database
    initializeHistory();

    //create menu tree
    currentMenu = new Menu("MAIN MENU", {"START NEW SESSION","HISTORY", "SETTING"}, nullptr);
    mainMenu = currentMenu;
    initializeMenu(currentMenu);

    // Initialize the main menu view
    ui->menuListWidget->addItems(currentMenu->getMenuOptions());
    ui->menuListWidget->setCurrentRow(0);
    ui->menuLabel->setText(currentMenu->getName());

    powerOn = false;
    changePowerStatus();
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerSwitch);

    // charge button connection
    connect(ui->batteryPushButton, &QPushButton::released, this, &MainWindow::chargeBattery);

    // Battery level spinbox connection
    connect(ui->batterySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeBatteryCapacity);

    //interface buttons connections
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::scrollUp);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::scrollDown);
    connect(ui->selectButton, &QPushButton::pressed, this, &MainWindow::selectAction);
    connect(ui->menuButton, &QPushButton::pressed, this, &MainWindow::backToMainMenu);
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::backToPrevious);
    connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::parameterPlus);
    connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::parameterMinus);
    connect(ui->sensorButton, &QPushButton::clicked, [this]() {activateSensor(!sensorOn);});

    // Initialize battery levels
    ui->batterySpinBox->setValue(currentBattery);
    
    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);
    ui->lowLabel->setVisible(false);
    ui->medLabel->setVisible(false);
    ui->highLabel->setVisible(false);
}

void MainWindow::initializeMenu(Menu* menu) {
    QStringList settingList;

    //create submenu options of setting
    settingList.append("RESET");
    settingList.append("BREATH PACER INTERVAL:  10");

    //create submenu options of history
    Menu* sessionMenu = new Menu("START NEW SESSION", {}, menu);
    Menu* historyMenu = new Menu("HISTORY", allRecords, menu);
    Menu* settingMenu = new Menu("SETTINGS", settingList, menu);

    menu->addChildMenu(sessionMenu);
    menu->addChildMenu(historyMenu);
    menu->addChildMenu(settingMenu);

    Menu* resetMenu = new Menu("RESET", {"YES","NO"}, settingMenu);
    settingMenu->addChildMenu(resetMenu);

    //create menus and submenus for each record in historyMenu
    for (const QString &str : allRecords) {
        //set "yyyy-MM-dd hh:mm:ss" part as the menu name
        Menu* record = new Menu(str.left(19), {"VIEW", "DELETE"}, historyMenu);
        record->addChildMenu(new Menu("VIEW",{}, record));
        record->addChildMenu(new Menu("DELETE", {}, record));
        historyMenu->addChildMenu(record);
    }
}

//initializa history menu
void MainWindow::initializeHistory() {
    //Load records from the database
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

void MainWindow::startSession() {
    //display the session view
    currentSession = new Session();
    ui->lowLabel->setVisible(false);
    ui->medLabel->setVisible(false);
    ui->highLabel->setVisible(false);
    ui->contact->setVisible(sensorOn);
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
    plot(); //generate initial empty plot

    //Connect timer to update all session data
    QTimer* sessionTimer = currentSession->getTimer();
    currentTimerCount = 0;
    connect(sessionTimer, &QTimer::timeout, this, &MainWindow::sessionTimerSlot);
    if (sensorOn == true) {
        sessionTimer->start(1000);
    }
}

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

void MainWindow::updateSession() {
    consumeBattery(0.5);
    //session can only update when battery is 10% above
    if (currentBattery > 10.0) {
        currentSession->updateAll();
        updateSessionView();
        plot();
        if (currentTimerCount >= MAX_SESSION_DURATION) {
            endSession();
        }
    }else {
        qDebug() << "Battery is under 10%, this session cannot continue, please charge";
        endSession();
    }
}

void MainWindow::endSession() {
    currentSession->getTimer()->stop();
    currentSession->getTimer()->disconnect();
    currentSession->calCLPercentage();

    //to fill up enough data according to the actual running time
    if (currentTimerCount > currentSession->getLength()) {
        QVector<double>* newDoubles = currentSession->simulateHeartIntervals(currentTimerCount - currentSession->getLength());
        QVector<QPointF>* newPoints = currentSession->calPoints(&newDoubles);
        currentSession->updateHRVData(newPoints);
        delete newDoubles;
    }

    //save new record to database and check its validity
    bool flag = database->addRecord(currentSession->getStartTime(),currentTimerCount, currentSession->getLowPercentage(),
                        currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                        (currentSession->getAchievementScore()*5)/currentSession->getLength(),
                        currentSession->getAchievementScore(), *(currentSession->getHRVData()));
    Record* newRecord = new Record(currentSession->getStartTime(),currentTimerCount, currentSession->getLowPercentage(),
                                   currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                                   currentSession->getAchievementScore()*5/currentSession->getLength(),
                                   currentSession->getAchievementScore(), *(currentSession->getHRVData()));

    //only add it in memory and create history option for it if it is valid
    if (flag) {
        records.push_back(newRecord);

        // add new menu option to the history tab after a session ends
        Menu* historyMenu = mainMenu->get(1);
        Menu* newHistoryRecord = new Menu(currentSession->getStartTime().toString("yyyy-MM-dd HH:mm:ss"), {"VIEW", "DELETE"}, historyMenu);
        newHistoryRecord->addChildMenu(new Menu("VIEW",{}, newHistoryRecord));
        newHistoryRecord->addChildMenu(new Menu("DELETE", {}, newHistoryRecord));
        historyMenu->addChildMenu(newHistoryRecord);
        QString newRecordString = newHistoryRecord->getName() + "\n"
            + "   Length: " + QString::number(currentTimerCount / 60)
            + ((currentTimerCount % 60 < 10) ? ":0" + QString::number(currentTimerCount % 60) : ":" + QString::number(currentTimerCount % 60));
        QStringList temp = historyMenu->getMenuOptions();
        temp.push_back(newRecordString);
        historyMenu->setMenuOptions(temp);
    }else {delete newRecord;}

    currentTimerCount = -1;
    sensorOn = false;
    bpProgress = 0;
    bpIsIncreasing = true;

    delete currentSession;
    currentSession = nullptr;

    ui->bp->setValue(0);
    ui->lowLabel->setVisible(false);
    ui->medLabel->setVisible(false);
    ui->highLabel->setVisible(false);
    ui->coherenceValue->setText("0.00");
    ui->lengthValue->setText("00:00");
    ui->achievementScore->setText("0.00");

    //display review right after session ends if this record is valid
    if (flag) {displayReview(newRecord);}
    else {backToPrevious();}
}

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

void MainWindow::displayReview(Record* newRecord) {
    //display indicators' values
    ui->date->setText((newRecord->getStartTime()).toString("yyyy-MM-dd hh:mm:ss"));
    ui->avgScore->setText(QString::number(newRecord->getAverageCoherence(),'f',2));
    ui->achScore->setText(QString::number(newRecord->getAchievementScore(),'f',2));
    ui->lenScore->setText(QString::number(newRecord->getLength())+"s");
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
}

//Disable user UI for power-off, and enable user UI for power-on
void MainWindow::changePowerStatus() {

    ui->menuListWidget->setVisible(powerOn);
    ui->menuLabel->setVisible(powerOn);
    ui->status->setVisible(powerOn);   //display battery level and sensor detector
    ui->stackedWidget->setVisible(powerOn);

    //Remove this if we want the menu to stay in the same position when the power is off
    if (powerOn) {
        MainWindow::backToMainMenu();
        ui->sensorButton->setChecked(false);
        activateSensor(false);
    }

    ui->upButton->setEnabled(powerOn);
    ui->downButton->setEnabled(powerOn);
    ui->leftButton->setEnabled(powerOn);
    ui->rightButton->setEnabled(powerOn);
    ui->menuButton->setEnabled(powerOn);
    ui->selectButton->setEnabled(powerOn);
    ui->backButton->setEnabled(powerOn);
    ui->sensorButton->setEnabled(powerOn);
}

//set power on/off state
void MainWindow::powerSwitch() {
    if (currentBattery > 0) {
        powerOn  = !powerOn;
        changePowerStatus();
    }

    //handle poweroff event during session measurement  ??
    if (currentTimerCount != -1) {
        //Save Record and end session
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
            backToMainMenu();
        }

        activateSensor(false);
    }
}


void MainWindow::chargeBattery() {

    int fullyCharged = 100;
    changeBatteryCapacity(fullyCharged);
}

//press up button
void MainWindow::scrollUp() {

    int nextIndex = ui->menuListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = ui->menuListWidget->count() - 1;
    }

    ui->menuListWidget->setCurrentRow(nextIndex);
}

//press down button
void MainWindow::scrollDown() {

    int nextIndex = ui->menuListWidget->currentRow() + 1;

    if (nextIndex > ui->menuListWidget->count() - 1) {
        nextIndex = 0;
    }

    ui->menuListWidget->setCurrentRow(nextIndex);
}

//press selectButton
void MainWindow::selectAction() {
    //when user presses the button during the measurement session
    if (currentTimerCount != -1) {
        //Save record and end session
        if (currentMenu->getName() == "START NEW SESSION" && currentTimerCount!=0) {
            endSession();
            return;
        }
    }

    int index = ui->menuListWidget->currentRow();
    if (index < 0) return;
    if (currentMenu->getName() == "SETTINGS" && index==1){return;} //handle when user presses select button during BPInterval setting scenario

    //reset to initial state
    if (currentMenu->getName() == "RESET") {
        if (currentMenu->getMenuOptions()[index] == "YES") {
            //resetAction();
            for (int i = 0; i < records.size(); i++) {
                delete records[i];
            }
            records.clear();

            database->reset();
            setting->reset();

            // delete original main menu object and regenerate a new menu object for resetting, then navigate to main menu
            mainMenu->deleteAllSubMenus();
            initializeHistory();
            currentMenu = new Menu("MAIN MENU", {"START NEW SESSION","HISTORY", "SETTING"}, nullptr);
            mainMenu = currentMenu;
            initializeMenu(currentMenu);
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
     //If the menu is not a parent and clicking on it starts a session
    }else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->get(index)->getName() == "START NEW SESSION") {
        if (currentBattery <= 10.0) {
            qDebug()<<"Battery is under 10%, cannot start a new session, please charge";
            return;
        }

        //Update new menu info
        currentMenu = currentMenu->get(index);
        updateMenu("Measuring", {});
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
    qDebug() << "No matching record found";
}

void MainWindow::deleteAction(){
    QString datetimeString = currentMenu->getName().left(19); //get datetime Qstring
    QDateTime datetime = QDateTime::fromString(datetimeString, "yyyy-MM-dd HH:mm:ss");   //convert the datetime string to a QDateTime object

    for (int i = 0; i < records.size(); i++) {
        if (records[i]->getStartTime().toString("yyyy-MM-dd HH:mm:ss") == datetimeString) {
            database->deleteRecord(datetime);
            delete records[i];
            records.remove(i);
            //qDebug() << "Record deleted successfully!";
            break;
        }
    }

    Menu* tempMenu = currentMenu;
    backToPrevious(); // Navigate back to the parent menu

    currentMenu->deleteChildMenu(tempMenu);
    updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
}

void MainWindow::updateMenu(const QString menuName, const QStringList menuOptions) {

    ui->menuListWidget->clear();
    ui->menuListWidget->addItems(menuOptions);
    ui->menuListWidget->setCurrentRow(0);

    ui->menuLabel->setText(menuName);
    ui->menuLabel->setStyleSheet("QLabel { font-weight: 600; color: #e9b96e; qproperty-alignment: 'AlignHCenter | AlignVCenter'; background-color: white;}");
}

//mainMenu button slot
void MainWindow::backToMainMenu() {

    //handle session interuption
    if (currentTimerCount != -1) {
        //Save record and end session
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
            return;
        }
    }

    currentMenu = mainMenu;
    updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);
}


void MainWindow::backToPrevious() {

    //handle session interuption
    if (currentTimerCount != -1) {
        //Save record
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
            return;
        }
    }

    if (currentMenu->getName() == "MAIN MENU") {
        ui->menuListWidget->setCurrentRow(0);
    }
    else {
        currentMenu = currentMenu->getParentMenu();
        updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
    }

    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);
}


void MainWindow::parameterPlus() {
    int index = ui->menuListWidget->currentRow();
    //int currentChallengeLevel = setting->getChallengeLevel();
    int currentBpInterval = setting->getBpInterval();

    if (currentMenu->getName() == "SETTINGS"){
        if (index == 1 && currentBpInterval <=29){
            setting->setBpInterval(currentBpInterval+1);

            QStringList settingList;
            settingList.append("RESET");
            settingList.append("BREATH PACER INTERVAL: " + (QString::number(setting->getBpInterval())));

            ui->menuListWidget->clear();
            ui->menuListWidget->addItems(settingList);
            ui->menuListWidget->setCurrentRow(1);
            ui->menuLabel->setText(currentMenu->getName());
            currentMenu->setMenuOptions(settingList);
        }
    }
}


void MainWindow::parameterMinus() {

    int index = ui->menuListWidget->currentRow();
    //int currentChallengeLevel = setting->getChallengeLevel();
    int currentBpInterval = setting->getBpInterval();

    if (currentMenu->getName() == "SETTINGS"){
        if (index == 1 && currentBpInterval >1){
            setting->setBpInterval(currentBpInterval-1);

            QStringList settingList;
            settingList.append("RESET");
            settingList.append("BREATH PACER INTERVAL: " + (QString::number(setting->getBpInterval())));

            ui->menuListWidget->clear();
            ui->menuListWidget->addItems(settingList);
            ui->menuListWidget->setCurrentRow(1);
            ui->menuLabel->setText(currentMenu->getName());
            currentMenu->setMenuOptions(settingList);
        }
    }
}

//Slot to change the battery level from the control panel
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
    }
}

//Starts/stops the session timer if they are on a session
void MainWindow::activateSensor(bool checked) {
    sensorOn = checked;

    if (currentTimerCount != -1) {
        if (!sensorOn) {
            currentSession->getTimer()->stop();
        }
        else {
            currentSession->getTimer()->start(1000);
        }
        ui->contact->setVisible(sensorOn);
    }
}

void MainWindow::consumeBattery(double consumption) {
    changeBatteryCapacity(currentBattery - consumption);
}

//void MainWindow::changeChallengeLevel(int level) {

    //setting->setChallengeLevel(level);
    //ui->ChallengeLevelLabel->setText("Challenge Level: " + QString::number(level));
//}

void MainWindow::plot() {
    QVector<QPointF>* points = currentSession->getHRVData();
    int size = points->size();
    double previousX = 0;
    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++) {
      x[i] = points->at(i).x() + previousX;
      y[i] = points->at(i).y();
      previousX = x[i];
//      qInfo() << x[i] << "|" << y[i];
    }
    ui->sessionGraph->QCustomPlot::addGraph();
    ui->sessionGraph->graph(0)->setData(x, y);
    ui->sessionGraph->xAxis->setLabel("Time (s)");
    ui->sessionGraph->yAxis->setLabel("HR (bps)");
    ui->sessionGraph->xAxis->setRange(0, MAX_SESSION_DURATION);
    ui->sessionGraph->yAxis->setRange(55, 105);
    ui->sessionGraph->replot();
}


void MainWindow::plotHistory(Record* record) {
    QVector<QPointF> points = record->getHrvGraph();

    int size = points.size();
    double previousX = 0;
    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++) {
      x[i] = points[i].x() + previousX;
      y[i] = points[i].y();
      previousX = x[i];
    }

    ui->historyGraph->QCustomPlot::addGraph();
    ui->historyGraph->graph(0)->setData(x, y);
    ui->sessionGraph->xAxis->setLabel("Time (s)");
    ui->sessionGraph->yAxis->setLabel("HR (bps)");
    ui->historyGraph->xAxis->setRange(0, record->getLength());
    ui->historyGraph->yAxis->setRange(55, 105);
    ui->historyGraph->replot();
}

void MainWindow::updateBP(int interval) {
    if (bpIsIncreasing) {
        bpProgress += (200/interval);
        if (bpProgress >= 100) {
            bpIsIncreasing = false;
        }
    } else {
        bpProgress -= (200/interval);
        if (bpProgress <= 0) {
            bpIsIncreasing = true;
        }
    }
    ui->bp->setValue(bpProgress);
}
