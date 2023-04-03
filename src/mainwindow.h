#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QListWidget>
#include <QGraphicsView>
#include <QTime>
#include <QStatusBar>
#include <QVector>
#include <QtGlobal>

#include "menu.h"
#include "session.h"
#include "dbController.h"
#include "setting.h"
#include "record.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Menu* masterMenu;  //the current node of the menu tree that the user is on
    Menu* mainMenuOG;  //the original main menu node, need this in order to delete without memory leaks

    Ui::MainWindow *ui;   //A ui pointer for the UI in mainwindow
    QListWidget *activeQListWidget;    //A widget for displaying the menus

    QVector<Session*> sessions;  //a vector holding the session objects
    QVector<Record*> records;   //a vector holding the record objects

    QStringList allRecords;  //A list of strings where each string is a string representation of a record object

    Session* currentSession;  //A pointer for the current running measurement session
    DBManager* db;
    Setting* setting;

    bool powerOn;
    bool sensorOn;
    int currentBattery;
    int currentTimerCount;

    QString timeString; //a string representation of how long the session runs

    void updateMenu(const QString, const QStringList);
    void initializeMainMenu(Menu*);   //Dynamically allocate all the menu objects
    void initializeSessions();   //Dynamically allocate all the sessions
    void initializeTimer(QTimer*);   //Initalize the timer
    void startSession(Session*);  //Display the session page, and initialize data to run the session if user click the sensorOn button
    void changePowerStatus(); //Disable UI for power-off, and enable the UI for power-on
    void drainBattery();  //Contains an equation of how much to drain the battery by then calling another function to change it


private slots:
    void updateTimer();  //Update the timer displayed on the session screen
    void powerChange();   //set power on/off state
    void rechargeBattery();  //Change the currentPowerLevel to 100

    void navigateDownMenu();   //Navigate down on a menu
    void navigateUpMenu();    //Navigate up on a menu
    void navigateSubMenu();   //Connected to the selector button, go into a submenu
    void navigateToMainMenu();   //Navigate to main menu
    void navigateBack();     //Navigate the previous menu

    void sensorOn(bool);   //Start/stop the session timer if they are on a measurement session
    void sensorOn(int);  //Start/stop the session from the admin panel

};

#endif
