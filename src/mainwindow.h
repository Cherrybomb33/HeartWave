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

//    void plot(QVector<QPointF> **points); //Plot the HRV graph based on points parameter
//    void addPlot(QVector<QPointF> **points);//Add more points to the HRV graph based on points parameter

private:
    Menu* currentMenu;  //the current node of the menu tree that the user is on
    Menu* mainMenu;  //the original main menu node, need this in order to delete without memory leaks

    Ui::MainWindow *ui;   //A ui pointer for the UI in mainwindow
    //QListWidget *activeQListWidget;    //A widget for displaying the menus

    //QVector<Session*> sessions;  //a vector holding the session objects
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

    QString timeString; //a string representation of how long the session runs
    
    void setupConnections();
    void updateMenu(const QString, const QStringList);
    void initializeMenu(Menu*);   //Dynamically allocate all the menu objects
    void initializeHistory();
    //void initializeSessions();   //Dynamically allocate all the sessions
    //void initializeTimer(QTimer*);   //Initalize the timer
    void startSession();  //Display the session page, and initialize data to run the session if user click the sensorOn button
    void changePowerStatus(); //Disable UI for power-off, and enable the UI for power-on
    void consumeBattery(double consumption);  //Contains an equation of how much to drain the battery by then calling another function to change it

//    QVector<QPointF>* calPoints(QVector<double>** times);
    void updateSession();
    void plot();
    void plotHstory(Record *Record);
    void displayReview(Record *newRecord);
    void updateBP(int interval);
    void endSession();
    void updateSessionView();
    void changeBatteryCapacity(double capacity);
private slots:
    void powerSwitch();   //set power on/off state
    void chargeBattery();  //Change the currentPowerLevel to 100

    void navigateDownMenu();   //Navigate down on a menu
    void navigateUpMenu();    //Navigate up on a menu
    void navigateSubMenu();   //Connected to the selector button, go into a submenu
    void navigateToMainMenu();   //Navigate to main menu
    void navigateBack();     //Navigate the previous menu
    void parameterPlus();
    void parameterMinus();
    
    void activateSensor(bool);   //Start/stop the session timer if they are on a measurement session
    void activateSensor(int);  //Start/stop the session from the admin panel

//    void another5Sec(); //Generato another 5 seconds data and add it to the plot
    void sessionTimerSlot();
};

#endif
