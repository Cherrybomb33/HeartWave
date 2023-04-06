#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QVariant>
#include <QVector>
#include <QList>
#include <QApplication>

//Manages interactions between application and database
class DBController {

public:
    DBController();  //constructor

    const QString DATE_FORMAT = "yyyy-MM-dd hh:mm:ss";   //time format in database
    static const QString DATABASE_PATH;    //path of the database
    QVector<Record*> getRecords();    //get a list of Record objects

    bool addRecord(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph);
    bool deleteRecord(const QDateTime& time);
    //void resetDevice();    //  if isReset == true, call reset() and set isReset to false;

private:
    QSqlDatabase heartwaveDB;    //database object
    //Setting setting;
    //bool isReset;  //initialize to false      

    bool dbInit();    //initializes the database
    bool isValidRecord(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore);
    //void reset();   //wipe all data and restore the device to the initial install condition

};

#endif
