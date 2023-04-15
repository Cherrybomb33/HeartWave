#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QString>
#include <QStringList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QVariant>
#include <QVector>
#include <QPointF>
#include <QList>
#include <QApplication>
#include <QPropertyAnimation>
#include "record.h"

//manage interaction between app and database
class DBController {

public:
    DBController();  //constructor

    const QString DATE_FORMAT = "yyyy-MM-dd hh:mm:ss";   //time format in database
    static const QString DATABASE_PATH;                  //path of the database
    
    QStringList getHistory();    //get a QStringlist of records from the sessionRecords table in the database
    bool getRecord(const QDateTime& time, Record** record);    //get the record with the specified datetime from the database
    
    //add a session record to the database
    bool addRecord(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph);
    bool deleteRecord(const QDateTime& time);   //delete a record from the database and return true it the removal is successful or false otherwise
    bool reset();        //reset database to the initial contidion

private:
    QSqlDatabase heartwaveDB;

    bool dbInit();    //initialize heartwave database with two records
    //check the record parameters are valid or not
    bool isValidRecord(const QDateTime& time,  const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore);

};

#endif
