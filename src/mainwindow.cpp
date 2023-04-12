#include "mainwindow.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    setupConnections();
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
    bpProgress = 0;
    bpIsIncreasing = true;
    currentBattery = 100.0;
    currentSession = nullptr;
    setting = new Setting();

    //set initial sensor status
    sensorOn = false;

    //create database connection
    database = new DBController();

    //create menu tree
    currentMenu = new Menu("MAIN MENU", {"START NEW SESSION","HISTORY", "SETTING"}, nullptr);
    mainMenu = currentMenu;
    initializeMenu(currentMenu);

    // Initialize the main menu view
    //activeQListWidget = ui->menuListWidget;
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
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::navigateUpMenu);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::navigateDownMenu);
    connect(ui->selectButton, &QPushButton::pressed, this, &MainWindow::navigateSubMenu);
    connect(ui->menuButton, &QPushButton::pressed, this, &MainWindow::navigateToMainMenu);
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::navigateBack);
    connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::parameterPlus);
    connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::parameterMinus);
//    connect(ui->sensorButton, &QPushButton::clicked, this, QOverload<bool>::of(&MainWindow::activateSensor));  //this one is replaced by the next line
    connect(ui->sensorButton, &QPushButton::clicked, [this]() {activateSensor(!sensorOn);});

    // prevent signals from being emitted(send signals only for BP interval setting interaction)
    ui->leftButton->blockSignals(true);
    ui->rightButton->blockSignals(true);

    //sensor QComboBox connections
    //connect(ui->sensorComboBox, QOverload<int>::of(&QComboBox::activated), this, QOverload<int>::of(&MainWindow::activateSensor));

    // Initialize battery levels
    ui->batterySpinBox->setValue(currentBattery);
    
    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);
    
    //Load records from the database
    initializeHistory();
}

void MainWindow::initializeMenu(Menu* menu) {
    QStringList settingList;
    QStringList historyList;

    //create submenu options of setting
    settingList.append("RESET");
    settingList.append("BREATH PACER INTERVAL");

    //create submenu options of history
    historyList = database->getHistory();
    
    Menu* sessionMenu = new Menu("START NEW SESSION", {}, menu);
    Menu* settingMenu = new Menu("SETTINGS", settingList, menu);
    Menu* historyMenu = new Menu("HISTORY", historyList, menu);

    menu->addChildMenu(sessionMenu);
    menu->addChildMenu(settingMenu);
    menu->addChildMenu(historyMenu);

    Menu* resetMenu = new Menu("RESET", {"YES","NO"}, settingMenu);
    settingMenu->addChildMenu(resetMenu);
    
    //create menus and submenus for each record in historyMenu
    for (const QString &str : historyList) {
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
        QDateTime datetime = QDateTime::fromString(str.left(19), "yyyy-MM-dd HH:mm:ss");

        //create the Record object for the datetime and add it to the QVector
        Record* record = nullptr;
        database->getRecord(datetime, &record);
        records.append(record);
    }
}

void MainWindow::startSession() {
    currentSession = new Session();
    // set all coherence level light invisible????
    ui->lowLabel->setVisible(false);
    ui->medLabel->setVisible(false);
    ui->highLabel->setVisible(false);
    ui->contact->setVisible(sensorOn);
    //ui->sessionView->setVisible(true);
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);   //session page
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
    ui->lengthValue->setNum(currentTimerCount);
    updateBP(setting->getBpInterval());
    // update session data every 5 seconds
    if (currentTimerCount % 5 == 0 && currentBattery > 0) {
        updateSession();
    }
}

void MainWindow::updateSession() {
    consumeBattery(0.5);
    if (currentBattery > 0) {
        currentSession->updateAll();
        updateSessionView();
        plot();
        if (currentSession->getLength() >= MAX_SESSION_DURATION) {
            endSession();
        }
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

    Record* newRecord = new Record(currentSession->getStartTime(),currentTimerCount, currentSession->getLowPercentage(),
                                   currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                                   currentSession->getAchievementScore()*5/currentSession->getLength(),
                                   currentSession->getAchievementScore(), *(currentSession->getHRVData()));
    records.push_back(newRecord);

    database->addRecord(currentSession->getStartTime(),currentTimerCount, currentSession->getLowPercentage(),
                        currentSession->getmediumPercentage(), currentSession->getHighPercentage(),
                        currentSession->getAchievementScore()*5/currentSession->getLength(),
                        currentSession->getAchievementScore(), *(currentSession->getHRVData()));
    currentTimerCount = -1;
    bpProgress = 0;
    bpIsIncreasing = true;
    ui->bp->setValue(0);
    // set all coherence level light visible????
    ui->lowLabel->setVisible(true);
    ui->medLabel->setVisible(true);
    ui->highLabel->setVisible(true);

    delete currentSession;
    currentSession = nullptr;
    displayReview(newRecord);
}

void MainWindow::updateSessionView() {
    ui->coherenceValue->setNum(currentSession->getCoherenceScore());
    ui->achievementScore->setNum(currentSession->getAchievementScore());
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
    ui->date->setText((newRecord->getStartTime()).toString("yyyy-MM-dd hh:mm:ss"));
    ui->avgScore->setNum(newRecord->getAverageCoherence());
    ui->achScore->setNum(newRecord->getAchievementScore());
    ui->lenScore->setNum(newRecord->getLength());
    ui->lowPercentage->setText(QString::number(newRecord->getLowPercentage())+"%");
    ui->mediumPercentage->setText(QString::number(newRecord->getMedPercentage())+"%");
    ui->highPercentage->setText(QString::number(newRecord->getHighPercentage())+"%");
    //how to show hrv graph?
    plotHistory(newRecord);

    ui->stackedWidget->setCurrentIndex(1);
}

//Disable UI for power-off, and enable the UI for power-on
void MainWindow::changePowerStatus() {

    ui->menuListWidget->setVisible(powerOn);
    ui->menuLabel->setVisible(powerOn);
    ui->status->setVisible(powerOn);   //display battery level and sensor detector
    ui->stackedWidget->setVisible(powerOn);
    //ui->sessionViewWidget->setVisible(powerOn);

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
    ui->selectButton->setEnabled(powerOn);
    ui->backButton->setEnabled(powerOn);
    ui->sensorButton->setEnabled(powerOn);
    //ui->sensorComboBox->setEnabled(powerOn);  //control panel
}

//set power on/off state
void MainWindow::powerSwitch() {
    if (currentBattery > 0) {
        powerOn  = !powerOn;
        changePowerStatus();
    }

    //handle poweroff event during session measurement  ??
    if (currentTimerCount != 0) {
        //Save Record and end session
        if (currentMenu->getName() == "Session") {
            endSession();
        }

        activateSensor(false);
    }
}


void MainWindow::chargeBattery() {

    int fullyCharged = 100;
    changeBatteryCapacity(fullyCharged);
}


void MainWindow::navigateUpMenu() {

    int nextIndex = ui->menuListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = ui->menuListWidget->count() - 1;
    }

    ui->menuListWidget->setCurrentRow(nextIndex);
}


void MainWindow::navigateDownMenu() {

    int nextIndex = ui->menuListWidget->currentRow() + 1;

    if (nextIndex > ui->menuListWidget->count() - 1) {
        nextIndex = 0;
    }

    ui->menuListWidget->setCurrentRow(nextIndex);
}

//press selectButton
void MainWindow::navigateSubMenu() {

    int index = ui->menuListWidget->currentRow();
    if (index < 0) return;

    // Prevent crash if ok button is selected in view
    //if (currentMenu->getName() == "VIEW") {
        //return;
    //}

    //when the menu is the reset menu
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

    //If the menu is a parent and clicking on it will display sub menus.
    if (currentMenu->get(index)->getMenuOptions().length() > 0) {
        currentMenu = currentMenu->get(index);
        MainWindow::updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());

     //If the menu is not a parent and clicking on it starts a session
    }else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->get(index)->getName() == "START NEW SESSION") {
        //Update new menu info
        currentMenu = currentMenu->get(index);
        MainWindow::updateMenu("Measuring", {});
        MainWindow::startSession();

    }else if (currentMenu->get(index)->getMenuOptions().length() == 0 && currentMenu->get(index)->getName() == "DELETE") {
        //currentMenu = currentMenu->get(index);
        QString datatimeString = currentMenu->getParentMenu()->getName().left(19); //get datetime Qstring
        QDateTime datetime = QDateTime::fromString(datatimeString, "yyyy-MM-dd HH:mm:ss");   //convert the datetime string to a QDateTime object

        for (int i = 0; i < records.size(); i++) {
            if (records[i]->getStartTime() == datetime) {
                database->deleteRecord(datetime);
                delete records[i];
                records.remove(i);
                qDebug() << "Record deleted successfully!";
                return;
            }
        }

        qDebug() << "No matching record found.";

    //If the button pressed should display the records.
    }else if (currentMenu->get(index)->getName() == "VIEW") {
        QString datatimeString = currentMenu->getParentMenu()->getName().left(19); //get datetime Qstring
        QDateTime datetime = QDateTime::fromString(datatimeString, "yyyy-MM-dd HH:mm:ss");   //convert the datetime string to a QDateTime object
        currentMenu = currentMenu->get(index);
        updateMenu("Record", {});

        for (Record* record : records) {
            if (record->getStartTime() == datetime) {
                displayReview(record);
                return;
            }
        }

        qDebug() << "No matching record found.";
    }
}

void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems) {

    ui->menuListWidget->clear();
    ui->menuListWidget->addItems(menuItems);
    ui->menuListWidget->setCurrentRow(0);

    ui->menuLabel->setText(selectedMenuItem);
}

//mainMenu button slot
void MainWindow::navigateToMainMenu() {

    //handle session interuption
    // ??cannot display review
    if (currentTimerCount != 0) {
        //Save record and end session
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
        }
    }

    //loop until return the main menu
    while (currentMenu->getName() != "MAIN MENU") {
        currentMenu = currentMenu->getParentMenu();
    }

    updateMenu(currentMenu->getName(), currentMenu->getMenuOptions());
    ui->stackedWidget->setVisible(false);
    ui->contact->setVisible(false);
}


void MainWindow::navigateBack() {
    // needed?
    //ui->leftButton->blockSignals(true);
    //ui->rightButton->blockSignals(true);

    //handle session interuption
    // ??cannot display review
    if (currentTimerCount != -1) {
        //Save record
        if (currentMenu->getName() == "START NEW SESSION") {
            endSession();
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

    if (currentMenu->getName() == "SETTING"){
        if (index == 1 && currentBpInterval <=29){
            setting->setBpInterval(currentBpInterval+1);
            ui->menuListWidget->item(index)->setText("BREATH PACER INTERVAL: " + QString::number(currentBpInterval));
        }
    }
}


void MainWindow::parameterMinus() {

    int index = ui->menuListWidget->currentRow();
    //int currentChallengeLevel = setting->getChallengeLevel();
    int currentBpInterval = setting->getBpInterval();

    if (currentMenu->getName() == "SETTING"){
        if (index == 1 && currentBpInterval >1){
            setting->setBpInterval(currentBpInterval-1);
            ui->menuListWidget->item(index)->setText("BREATH PACER INTERVAL: " + QString::number(currentBpInterval));
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
            navigateBack();
        }
        powerSwitch();
        currentBattery = 0;
    }
}

//Starts/stops the session timer if they are on a session
void MainWindow::activateSensor(bool checked) {

    //ui->sensorLabel->setPixmap(QPixmap(checked ? ":/icons/sensorOn.svg" : ":/icons/sensorOff.svg"));
    //ui->sensorComboBox->setCurrentIndex(checked ? 1 : 0);
    sensorOn = checked;

    if (currentTimerCount != -1) {
        if (!sensorOn) {
            currentSession->getTimer()->stop();
            //endSession();
        }
        else {
            currentSession->getTimer()->start(1000);
        }
        ui->contact->setVisible(sensorOn);
    }
}

void MainWindow::activateSensor(int value) {

    ui->sensorButton->setChecked(value == 1);
    activateSensor(value == 1);
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
    ui->sessionGraph->xAxis->setLabel("Time");
    ui->sessionGraph->yAxis->setLabel("HR");
    ui->sessionGraph->xAxis->setRange(0, MAX_SESSION_DURATION);
    ui->sessionGraph->yAxis->setRange(55, 105);
    ui->sessionGraph->replot();
}

//??
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
    ui->historyGraph->xAxis->setLabel("Time");
    ui->historyGraph->yAxis->setLabel("HR");
    ui->historyGraph->xAxis->setRange(0, MAX_SESSION_DURATION);
    ui->historyGraph->yAxis->setRange(55, 105);
    ui->historyGraph->replot();
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

//QVector<QPointF>* MainWindow::calPoints(QVector<double>** times) {
//    QVector<QPointF>* points = new QVector<QPointF>();
//    for (int i = 0;i < (*times)->size();i++) {
//        QPointF newPoint((*times)->at(i),60/(*times)->at(i));
//        points->push_back(newPoint);
//    }
//    return points;
//}
