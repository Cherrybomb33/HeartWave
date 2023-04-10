#include "mainwindow.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    setupConnections();

    currentSession = nullptr;
}

//destructor
MainWindow::~MainWindow() {
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

    //set Initial sensor status
    sensorOn = false;

    //create database connection
    database = new DBController();

    //create menu tree
    currentMenu = new Menu("MAIN MENU", {"START NEW SESSION","HISTORY", "SETTING"}, nullptr);
    mainMenu = currentMenu;
    initializeMenu(currentMenu);

    // Initialize the main menu view
    activeQListWidget = ui->mainMenuListView;
    activeQListWidget->addItems(currentMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);
    ui->menuLabel->setText(currentMenu->getName());

    powerOn = false;
    changePowerStatus();
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerSwitch);

    // charge button connection
    connect(ui->chargeButton, &QPushButton::released, this, &MainWindow::chargeBattery);

    // Battery level spin box connection
    connect(ui->batteryLevelSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeBatteryLevel);

    //interface buttons connections
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::navigateUpMenu);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::navigateDownMenu);
    connect(ui->selectorButton, &QPushButton::pressed, this, &MainWindow::navigateSubMenu);
    connect(ui->menuButton, &QPushButton::pressed, this, &MainWindow::navigateToMainMenu);
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::navigateBack);
    connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::ParameterPlus);
    connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::ParameterMinus);
    connect(ui->sensorButton, &QPushButton::clicked, this, QOverload<bool>::of(&MainWindow::activateSensor));

    // Disable Power Buttons
    ui->rightButton->blockSignals(true);
    ui->leftButton->blockSignals(true);


    //sensor QComboBox connections
    connect(ui->sensorComboBox, QOverload<int>::of(&QComboBox::activated), this, QOverload<int>::of(&MainWindow::activateSensor));

    // Change power level from panel
    connect(ui->powerLevelSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::changePowerLevel);

    // Initialize battery levels
    ui->batteryLevelSpinBox->setValue(99.9);
    
    ui->sessionViewWidget->setVisible(false);
    ui->sensorLabel->setVisible(false);
    
    //Load records from the database
    allRecords = database->getHistory();
}

void MainWindow::initializeMenu(Menu* m) {
    QStringList settingList;
    QStringList historyList;

    //create submenu options of setting
    settingList.append("CHALLENGE LEVEL");
    settingList.append("BREATH PACER INTERVAL");
    settingList.append("RESET");

    //create submenu options of history
    historyList = database.getHistory();
    
    Menu* sessionMenu = new Menu("START NEW SESSION", {}, m);
    Menu* settingMenu = new Menu("SETTINGS", settingList, m);
    Menu* historyMenu = new Menu("HISTORY", historyList, m);

    m->addChildMenu(sessionMenu);
    m->addChildMenu(settingMenu);
    m->addChildMenu(historyMenu);

    Menu* resetMenu = new Menu("RESET", {"YES","NO"}, settingMenu);
    settingMenu->addChildMenu(resetMenu);

    //historyMenu->addChildMenu(new Menu(,{}));
    
    //create menus and submenus for each record in historyMenu
    for (const QString &str : historyList) {
        //set "yyyy-MM-dd hh:mm:ss" part as the menu name
        Menu* record = new Menu(str.left(19), {"VIEW", "DELETE"}, historyMenu);
        record->addChildMenu(new Menu("VIEW",{}, record));
        record->addChildMenu(new Menu("DELETE", {}, record));
        historyMenu->addChildMenu(record);
    }
}

void MainWindow::startSession() {
    currentSession = new Session();
    ui->contact->setVisible(true);
    ui->sessionView->setVisible(true);

    //Connect timer to update all session data
    QTimer* sessionTimer = currentSession->getTimer();
    connect(sessionTimer, &QTimer::timeout, this, &MainWindow::updateSession);
    if (sensorOn == true) {
        sessionTimer->start(5000);
    }

    //Power Buttons and left and right buttons are blocked
    ui->powerButton->blockSignals(true);
    ui->rightButton->blockSignals(true);
    ui->leftButton->blockSignals(true);
}

void MainWindow::updateSession() {

    drainBattery();
    currentSession->updateAll();
    plot();

    if (currentSession->getLength() >= MAX_SESSION_DURATION) {
        //Save record
        Record* newRecord = new Record(QDateTime::currentDateTime(),currentSession->getLength(), currentSession->getLowPercentage(),
                                       currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                                       currentSession->getAchievementScore()/currentSession->getLength(),
                                       currentSession->getAchievementScore(), *(currentSession->getHRVData()));

        database->addRecord(QDateTime::currentDateTime(),currentSession->getLength(), currentSession->getLowPercentage(),
                            currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                            currentSession->getAchievementScore()/currentSession->getLength(),
                            currentSession->getAchievementScore(), *(currentSession->getHRVData()));

        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        delete currentSession;
        currentSession = nullptr;
        displayReview(newRecord);
    }
}

void MainWindow::displayReview(Record* newRecord) {

}

//Disable UI for power-off, and enable the UI for power-on
void MainWindow::changePowerStatus() {

    activeQListWidget->setVisible(powerOn);
    ui->menuLabel->setVisible(powerOn);
    ui->statusBarQFrame->setVisible(powerOn);   //display battery level and sensor detector
    ui->sessionView->setVisible(powerOn);
    //ui->frequencyLabel->setVisible(powerOn);  //display sth at the bottom of the screen
    ui->sessionViewWidget->setVisible(powerOn);

    //Remove this if we want the menu to stay in the same position when the power is off
    if (powerOn) {
        MainWindow::navigateToMainMenu();
        ui->sensorButton->setChecked(false);
        activateSensor(false);
    }

    ui->upButton->setEnabled(powerOn);
    ui->downButton->setEnabled(powerOn);
    ui->leftButton->setEnabled(powerOn);
    ui->rightButton->setEnabled(powerOn);
    ui->menuButton->setEnabled(powerOn);
    ui->selectorButton->setEnabled(powerOn);
    ui->backButton->setEnabled(powerOn);
    ui->sensorButton->setEnabled(powerOn);
    ui->sensorComboBox->setEnabled(powerOn);  //control panel
}

//set power on/off state
void MainWindow::powerSwitch() {
    //??getBattery() not ready, should getBattery() in Setting?
    if (getBattery() > 0) {
        powerOn  = !powerOn;
        changePowerStatus();
    }

    //handle poweroff event during session measurement  ??
    if (currentTimerCount != -1) {
        //Save Record
        if (currentMenu->getName() == "Session") {
            //records.last()->setDuration((currentTherapy->getTime())-currentTimerCount);
            currentSession->saveRecord();
            //database->addRecord(records.last()->getTreatment(),records.last()->getStartTime(),records.last()->getPowerLevel(),records.last()->getDuration());
        }

        //allRecords += records.last()->toString();
        //Stop session
        currentTimerCount = -1;
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        activateSensor(false);
    }
}


void MainWindow::chargeBattery() {

    int batteryLevel = 100.0;
    changeBatteryLevel(batteryLevel);
}


void MainWindow::navigateUpMenu() {

    int nextIndex = activeQListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = activeQListWidget->count() - 1;
    }

    activeQListWidget->setCurrentRow(nextIndex);
}


void MainWindow::navigateDownMenu() {

    int nextIndex = activeQListWidget->currentRow() + 1;

    if (nextIndex > activeQListWidget->count() - 1) {
        nextIndex = 0;
    }

    activeQListWidget->setCurrentRow(nextIndex);
}

//press selectorButton
void MainWindow::navigateSubMenu() {

    int index = activeQListWidget->currentRow();
    if (index < 0) return;

    // Prevent crash if ok button is selected in view
    //if (currentMenu->getName() == "VIEW") {
        //return;
    //}

    //when the menu is the reset menu.
    if (currentMenu->getName() == "RESET") {
        if (currentMenu->getMenuOptions()[index] == "YES") {
            for (int i = 0; i < records.size(); i++) {
                delete records[i];
            }
            records.clear();

            database->reset();
            setting->reset();
   
            navigateBack();
            return;
        }
        else {
            navigateBack();
            return;
        }
    }

    //If the menu is a parent and clicking on it should display more menus.
    if (currentMenu->get(index)->getMenuOptions().length() > 0) {
        currentMenu = currentMenu->get(index);
        MainWindow::updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());


    }//If the menu is not a parent and clicking on it should start a session
    else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->getName() == "START NEW SESSION") {
        //Update new menu info
        currentMenu = currentMenu->get(index);
        MainWindow::updateMenu("Measuring", {});
        MainWindow::beginSession();

    }else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->getName() == "VIEW") {
        currentMenu = currentMenu->get(index);
        MainWindow::updateMenu("Record", {});
        MainWindow::displayRecord();
    }

    //If the button pressed should display the records.
    else if (currentMenu->get(index)->getName() == "VIEW") {
        QString datatime = currentMenu->getParentMenu()->text().left(19); //get datetime Qstring
        currentMenu = currentMenu->get(index);
        //display the record
        //MainWindow::updateMenu("RECORDS", allRecords);
    }
}

void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems) {

    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);

    ui->menuLabel->setText(selectedMenuItem);
}

//??
void MainWindow::navigateToMainMenu() {

    if (currentTimerCount != -1) {
        //Save record
        if (currentMenu->getName() == "START NEW SESSION") {
            records.last()->setDuration((currentSession->getTime())-currentTimerCount);
    
            //database->addRecord(records.last()->getTreatment(),records.last()->getStartTime(),recordings.last()->getPowerLevel(),recordings.last()->getDuration());
        }

        //allRecords += records.last()->toString();

        //End session
        currentTimerCount = -1;
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        currentSession = nullptr;
    }

    while (currentMenu->getName() != "MAIN MENU") {
        currentMenu = currentMenu->getParentMenu();
    }

    updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
    ui->senssionViewWidget->setVisible(false);
    ui->sensorLabel->setVisible(false);
}


void MainWindow::navigateBack() {

    ui->rightButton->blockSignals(true);
    ui->leftButton->blockSignals(true);

    if (currentTimerCount != -1) {
        //Save record
        if (currentMenu->getName() == "START NEW SESSION") {
            records.last()->setDuration((currentSession->getTime())-currentTimerCount);
            //db->addRecord(recordings.last()->getStartTime(),records.last()->getChallengeLevel(),recordings.last()->getDuration());
        }

        //allRecords += records.last()->toString();

        //Stop session
        currentTimerCount = -1;
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        currentSession = nullptr;
    }

    if (currentMenu->getName() == "MAIN MENU") {
        activeQListWidget->setCurrentRow(0);
    }
    else {
        currentMenu = currentMenu->getParentMenu();
        updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
    }

    ui->sessionViewWidget->setVisible(false);
    ui->sensorLabel->setVisible(false);
}


void MainWindow::parameterPlus() {
    int index = activeQListWidget->currentRow();
    int currentChallengeLevel = setting->getChallengeLevel();
    int currentBpInterval = setting->getBpInterval();

    if (currentMenu->getName() == "SETTING"){
        if (index == 0 && currentChallengeLevel <=3){
            currentChallengeLevel = setting->setChallengeLevel(currentChallengeLevel + 1);
            activeQListWidget.item(index).setText("CHALLENGE LEVEL: " + QString::number(currentChallengeLevel));
                
        }else if (index == 1 && currentBpInterval <=29){
            currentBpInterval = setting->setBpInterval(currentBpInterval+1);
            activeQListWidget.item(index).setText("BREATH PACER INTERVAL: " + QString::number(currentBpInterval));
        }
    }
}


void MainWindow::parameterMinus() {

    int index = activeQListWidget->currentRow();
    int currentChallengeLevel = setting->getChallengeLevel();
    int currentBpInterval = setting->getBpInterval();

    if (currentMenu->getName() == "SETTING"){
        if (index == 0 && currentChallengeLevel >1){
            currentChallengeLevel = setting->setChallengeLevel(currentChallengeLevel - 1);
            activeQListWidget.item(index).setText("CHALLENGE LEVEL: " + QString::number(currentChallengeLevel));
                
        }else if (index == 1 && currentBpInterval >1){
            currentBpInterval = setting->setBpInterval(currentBpInterval-1);
            activeQListWidget.item(index).setText("BREATH PACER INTERVAL: " + QString::number(currentBpInterval));
        }
    }
}

//Slot to change the battery level from the control panel
void MainWindow::changeBatteryLevel(double newLevel) {

    if (newLevel >= 0.0 && newLevel <= 100.0) {
        if (newLevel == 0.0 && powerOn == true) {
            powerSwitch();
            setBattery(0);  //should this in Setting class
        }else{
            setBattery(newLevel);
        }

        ui->batteryLevelSpinBox->setValue(newLevel);
        int newLevelInt = int(newLevel);
        ui->batteryLevelBar->setValue(newLevelInt);

        QString highBatteryHealth = "QProgressBar { selection-background-color: rgb(78, 154, 6); background-color: rgb(0, 0, 0); }";
        QString mediumBatteryHealth = "QProgressBar { selection-background-color: rgb(196, 160, 0); background-color: rgb(0, 0, 0); }";
        QString lowBatteryHealth = "QProgressBar { selection-background-color: rgb(164, 0, 0); background-color: rgb(0, 0, 0); }";

        if (newLevelInt >= 50) {
            ui->batteryLevelBar->setStyleSheet(highBatteryHealth);
        }
        else if (newLevelInt >= 20) {
            ui->batteryLevelBar->setStyleSheet(mediumBatteryHealth);
        }
        else {
            ui->batteryLevelBar->setStyleSheet(lowBatteryHealth);
        }
    }
}

//Starts/stops the session timer if they are on a session
void MainWindow::activateSensor(bool checked) {

    //ui->sensorLabel->setPixmap(QPixmap(checked ? ":/icons/sensorOn.svg" : ":/icons/sensorOff.svg"));
    ui->sensorComboBox->setCurrentIndex(checked ? 1 : 0);
    sensorOn = checked;

    if (currentTimerCount != -1) {
        if (!sensorOn) {
            currentSession->getTimer()->stop();
        }
        else {
            currentSession->getTimer()->start(1000);
        }
    }
}

void MainWindow::activateSensor(int value) {

    ui->sensorButton->setChecked(value == 1);
    activateSensor(value == 1);
}

void MainWindow::drainBattery() {

    //1000 constant because 15 minutes is the longest therapy and we feel as it should last at least 15 minutes at full power
    double batteryLevel = qMax(getBattery() - getBattery/1000.0, 0.0);

    changeBatteryLevel(batteryLevel);
}

void MainWindow::changeChallengeLevel(int level) {

    setting->setChallengeLevel(level);
    ui->ChallengeLevelLabel->setText("Challenge Level: " + QString::number(level));
}

void MainWindow::plot() {
    QVector<QPointF>* points = currentSession->getHRVData();
    int size = points->size();
    double previousX = 0;
    QVector<double> x(size), y(size);
    for (int i=0; i<size; i++) {
      x[i] = points->at(i).x() + previousX;
      y[i] = points->at(i).y();
      previousX = x[i];
      qInfo() << x[i] << "|" << y[i];
    }
    ui->sessionGraph->QCustomPlot::addGraph();
    ui->sessionGraph->graph(0)->setData(x, y);
    ui->sessionGraph->xAxis->setLabel("Time");
    ui->sessionGraph->yAxis->setLabel("HR");
    ui->sessionGraph->xAxis->setRange(0, 124);
    ui->sessionGraph->yAxis->setRange(55, 105);
    ui->sessionGraph->replot();
}

//void MainWindow::plot(QVector<QPointF>** points) {
//    int size = (*points)->size();
//    QVector<double> x(size), y(size);
//    for (int i=0; i<size; i++) {
//      x[i] = (*points)->at(i).x() + previousX;
//      y[i] = (*points)->at(i).y();
//      previousX = x[i];
//      qInfo() << x[i] << "|" << y[i];
//    }
//    ui->hrvGraph->QCustomPlot::addGraph();
//    ui->hrvGraph->graph(0)->setData(x, y);
//    ui->hrvGraph->xAxis->setLabel("Time");
//    ui->hrvGraph->yAxis->setLabel("HR");
//    ui->hrvGraph->xAxis->setRange(0, 124);
//    ui->hrvGraph->yAxis->setRange(55, 105);
//    ui->hrvGraph->replot();
//}

//void MainWindow::addPlot(QVector<QPointF>** points) {
//    int size = (*points)->size();
//    QVector<double> x(size), y(size);
//    for (int i=0; i<size; i++) {
//      x[i] = (*points)->at(i).x() + previousX;
//      y[i] = (*points)->at(i).y();
//      previousX = x[i];
//      qInfo()<< "????" << x[i] << "|" << y[i];
//    }
//    ui->hrvGraph->graph(0)->addData(x,y);
//    ui->hrvGraph->replot();
//}

//void MainWindow::another5Sec()
//{
//    QVector<double>* points = currentSession->simulateHeartIntervals(5);
//    QVector<QPointF>* tests = calPoints(&points);
//    addPlot(&tests);
//}

void MainWindow::initBP(QTimer* timer) {
    int progress = 0;
    bool isIncreasing = true;

    connect(timer, &QTimer::timeout,[this,&progress, &isIncreasing]() {
        if (isIncreasing) {
            progress += 20; // change this value to control the speed of progress change
            if (progress >= 100) {
                isIncreasing = false;
            }
        } else {
            progress -= 20; // change this value to control the speed of progress change
            if (progress <= 0) {
                isIncreasing = true;
            }
        }
        ui->bp->setValue(progress);
    });

    timer->start(1000);
}

//QVector<QPointF>* MainWindow::calPoints(QVector<double>** times) {
//    QVector<QPointF>* points = new QVector<QPointF>();
//    for (int i = 0;i < (*times)->size();i++) {
//        QPointF newPoint((*times)->at(i),60/(*times)->at(i));
//        points->push_back(newPoint);
//    }
//    return points;
//}
