#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QVariant>
#include <QVector>
#include <QVPointF>
#include <QList>
#include <QApplication>

//Manages interactions between application and database
class DBController {

public:
    DBController();  //constructor

    const QString DATE_FORMAT = "yyyy-MM-dd hh:mm:ss";   //time format in database
    static const QString DATABASE_PATH;    //path of the database
    
    QStringList getHistory();    //get a list of QString
    bool getRecord(const QDateTime& time, Record** record);   //get a Record object
    
    //add a session record to the database
    bool addRecord(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph);
    bool deleteRecord(const QDateTime& time);    //delete a record from the database
    bool reset();   //wipe all records and restore the database to the initial condition

private:
    QSqlDatabase heartwaveDB;    //database object     

    bool dbInit();    //initialize the database
    bool isValidRecord(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore);

};

#endif
