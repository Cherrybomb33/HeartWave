#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDateTime>
#include <QTime>
#include <QVector>
#include <QPointF>

//To store information about a session connecting the database and mainwindow
class Record {

public:
    //constructor
    Record(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph);

    //getters and setters
    QDateTime getStartTime();
    int getchallengeLevel();
    double getLowPercentage(); 
    double getMedPercentage(); 
    double getHighPercentage(); 
    double getAverageCoherence();
    int getLength();
    double getAchievementScore();
    QVector<QPointF> getHrvGraph() const;

private:
    QDateTime startTime;     //session start
    int challengeLevel;      //challenge level of the session
    double lowPercentage;    //percentage of time in low coherence level
    double medPercentage;    //percentage of time in medium coherence level
    double highPercentage;   //percentage of time in high coherence level
    double averageCoherence; //average coherence score of the session
    int length;              //total measurement time of the session
    double achievementScore; //the sum of coherence scores during the length of the session
    QVector<QPointF> hrvGraph; // HRV graph data of the session
};

#endif
