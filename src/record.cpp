#include "record.h"

//constructor
Record::Record(const QDateTime& time, const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF>& hrvGraph) {
    if (time.isValid()) {
        this->startTime = time;
        this->challengeLevel = challengeLevel;
        this->lowPercentage = lowPercentage;
        this->medPercentage = medPercentage;
        this->highPercentage = highPercentage;
        this->averageCoherence = averageCoherence;
        this->length = length;
        this->achievementScore = achievementScore;
        this->hrvGraph = hrvGraph;
    }
}

//getters
QDateTime Record::getStartTime(){
    return startTime;
}

int Record::getchallengeLevel(){
    return challengeLevel;
}

double Record::getLowPercentage(){
    return lowPercentage;
}

double Record::getMedPercentage(){
    return medPercentage;
}

double Record::getHighPercentage(){
    return highPercentage;
}

double Record::getAverageCoherence(){
    return averageCoherence;
}

int Record::getLength(){
    return length;
}

double Record::getAchievementScore(){
    return achievementScore;
}

QVector<QPointF> Record::getHrvGraph() const{
    return hrvGraph;
}
