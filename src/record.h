#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDateTime>
#include <QTime>
#include <QVector>
#include <QPointF>

//To store information about a session in the database and in mainwindow
class Record {

public:
    Record(const QDateTime& time, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph);

    QString toString();
    QDateTime getStartTime();
//    int getchallengeLevel();
    double getLowPercentage(); 
    double getMedPercentage(); 
    double getHighPercentage(); 
    double getAverageCoherence();
    int getLength();
    double getAchievementScore();
    QVector<QPointF> getHrvGraph() const;

private:
    QDateTime startTime;
//    int challengeLevel;
    double lowPercentage;
    double medPercentage;
    double highPercentage;
    double averageCoherence;
    int length;
    double achievementScore; 
    QVector<QPointF> hrvGraph;
};

#endif
