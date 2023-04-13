#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QListWidget>
#include <QGraphicsView>
#include <QTime>
#include <QStatusBar>
#include <QVector>
#include <QPointF>
#include <QtGlobal>
#include <QDebug>

#include "menu.h"
#include "session.h"
#include "dbController.h"
#include "setting.h"
#include "record.h"

#define MAX_SESSION_DURATION 120

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Menu* currentMenu;  //the current node of the menu tree that the user is on
    Menu* mainMenu;  //the original main menu node, need this in order to delete without memory leaks

    Ui::MainWindow *ui;   //A ui pointer for the UI in mainwindow
    QVector<Record*> records;   //a vector holding the record objects

    QStringList allRecords;  //A list of strings where each string is a string representation of a record object
    Session* currentSession;  //A pointer for the current running measurement session
    DBController* database;
    Setting* setting;

    bool powerOn;
    bool sensorOn;
    double currentBattery;
    int currentTimerCount;
    int bpProgress;
    bool bpIsIncreasing;
    
    void setupConnections();
    void updateMenu(const QString menuName, const QStringList menuOptions);
    void initializeMenu(Menu* menu);   //Dynamically allocate all the menu objects
    void initializeHistory();
    void startSession();  //Display the session page, and initialize data to run the session if user click the sensorOn button
    void changePowerStatus(); //Disable UI for power-off, and enable the UI for power-on
    void consumeBattery(double consumption);  //Contains an equation of how much to drain the battery by then calling another function to change it

    void updateSession();
    void plot();
    void plotHistory(Record *Record);
    void displayReview(Record *newRecord);
    void updateBP(int interval);
    void endSession();
    void updateSessionView();
    void changeBatteryCapacity(double capacity);
    void deleteAction();
    void viewAction(int index);

private slots:
    void powerSwitch();   //set power on/off state
    void chargeBattery();  //Change the currentPowerLevel to 100

    void scrollDown();   //Navigate down on a menu
    void scrollUp();    //Navigate up on a menu
    void selectAction();   //Connected to the selector button, go into a submenu
    void backToMainMenu();   //Navigate to main menu
    void backToPrevious();     //Navigate the previous menu
    void parameterPlus();
    void parameterMinus();
    
    void activateSensor(bool isOn);   //Start/stop the session timer if they are on a measurement session

    void sessionTimerSlot();
};

#endif
