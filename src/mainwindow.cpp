#include "mainWindow.h"

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

    historyMenu->addChildMenu(new Menu(,{}));
    
    //create menus and submenus for each record in historyMenu
    for (const QString &str : historyList) {
        //set "yyyy-MM-dd hh:mm:ss" part as the menu name
        Menu* record = new Menu(str.left(19), {"VIEW", "DELETE"}, historyMenu);
        record->addChildMenu(new Menu("VIEW",{}, record));
        record->addChildMenu(new Menu("DELETE", {}, record));
        historyMenu->addChildMenu(record);
    }
}
