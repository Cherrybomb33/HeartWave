#include "record.h"

Record::Record(const QDateTime& time, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph) {

    if (time.isValid()) {
        this->startTime = time;
//        this->challengeLevel = challengeLevel;
        this->lowPercentage = lowPercentage;
        this->medPercentage = medPercentage;
        this->highPercentage = highPercentage;
        this->averageCoherence = averageCoherence;
        this->length = length;
        this->achievementScore = achievementScore;
        this->hrvGraph = hrvGraph;
    }
}

//??this function needs to show hrv graph
QString Record::toString() {
    QString newString = 
            "Session record:\n";
            + startTime.toString("ddd h:mm ap") + "\n"
//            + "   ChallengeLevel: " + QString::number(challengeLevel) + "\n"
            + "Low percentage: " + QString::number(lowPercentage) + "\n"
            + "Medium percentage: " + QString::number(medPercentage) + "\n"
            + "High percentage: " + QString::number(highPercentage) + "\n"
            + "Average coherence: " + QString::number(averageCoherence) + "\n"
            + "Length: " + QString::number(length) + " seconds\n"
            + "Achievement score: " + QString::number(achievementScore) + "\n"
            + "HRV graph: See the graph";
    return newString;
}
//getters
QDateTime Record::getStartTime() { return startTime;}
//int Record::getchallengeLevel() { return challengeLevel; }
double Record::getLowPercentage() { return lowPercentage; }
double Record::getMedPercentage() { return medPercentage; }
double Record::getHighPercentage() { return highPercentage; }
double Record::getAverageCoherence() { return averageCoherence; }
int Record::getLength(){return length;}
double Record::getAchievementScore(){return achievementScore;}

QVector<QPointF> Record::getHrvGraph() const {
    return hrvGraph;
}
