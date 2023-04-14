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
    
    QStringList getHistory();
    bool getRecord(const QDateTime& time, Record** record);
    

    bool addRecord(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph);
    bool deleteRecord(const QDateTime& time);
    bool reset();

private:
    QSqlDatabase heartwaveDB;

    bool dbInit();
    bool isValidRecord(const QDateTime& time,  const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore);

};

#endif
