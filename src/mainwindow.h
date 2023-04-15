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

//MainWindow class inherits from QMainWindow and manages the application's main window
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    //constructor and destructor
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Menu* currentMenu;  //pointer to the current menu node
    Menu* mainMenu;     //pointer to the main menu node

    Ui::MainWindow *ui;   //pointer to the UI object for the main window
    QVector<Record*> records;   //a vector holding pointers to Record objects
    QTimer* batteryTimer;   //a timer for consuming battery

    QStringList allRecords;   //A list of QStrings where each is the string representation of a Record object
    Session* currentSession;  //pointer to the current running measurement session
    DBController* database;   //pointer to the database controller object
    Setting* setting;         //pointer to the setting object

    bool powerOn;             //indicate if the device is powered on
    bool sensorOn;            //indicates if the sensor is activated
    double currentBattery;    //current battery level
    int currentTimerCount;    //current timer count
    int bpProgress;           //current progress of the Breath Pacer
    bool bpIsIncreasing;      //indicates if BP is increasing
    
    void setupConnections();           //set up and connect UI elements to their corresponding slots
    void initializeMenu(Menu* menu);   //initialize menu and the corresponding sub-menus.
    void initializeHistory();          //load data from the database and create a vector of Record objects
    void startSession();               //display the session page, and initialize data to run the session if user click the sensorOn button
    void updateSession();              //update the current session data
    void updateSessionView();          //update the session view
    void endSession();                 //end the current session and save data to Record object and database
    void displayReview(Record *newRecord);  //display a review of the session data

    void changePowerStatus();                      //toggle power status and enable/disable UI elements accordingly
    void consumeBattery(double consumption);       //drain the battery according to the given consumption value
    void changeBatteryCapacity(double capacity);   //update the battery capacity

    void updateMenu(const QString menuName, const QStringList menuOptions);  //update the menu UI
    void plot();                       //plot the HRV graph when start a new session
    void plotHistory(Record *Record);  //plot the HRV graph when user views history review
    void updateBP(int interval);       //update BP measurement progress
    void deleteAction();               //delete a record from the history
    void viewAction(int index);        //view a record from the history

//slot functions connected to UI elements
private slots:
    void powerSwitch();    //toggle power on/off
    void chargeBattery();  //charge the battery to full capacity

    void scrollDown();     //move the menu selection down
    void scrollUp();       //move the menu selection up
    void selectAction();   //select a menu item and start/stop session measurement mode
    void backToMainMenu(); //return to the main menu
    void backToPrevious(); //return to the previous menu
    void parameterPlus();  //increase a parameter value
    void parameterMinus(); //decrease a parameter value
    
    void activateSensor(bool isOn);   //start or stop the session timer during a measurement session
    void sessionTimerSlot();          //slot function for the session timer
};

#endif
