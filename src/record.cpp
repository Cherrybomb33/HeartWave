#include "record.h"

Record::Record(const QDateTime& time, const int challengeLevel, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const int length, const double achievementScore, const vector<double>& hrvGraph) {

    if (startTime.isValid()) {
        this->startTime = time;
        this->challengeLevel = challengeLevel;
        this->lowPercentage = lowPercentage;
        this->medPercentage = medPercentage;
        this->highPercentage = highPercentage;
        this->averageCoherence = averageCoherence;
        this->length = length;
        this->achievementScore = achievementScore;
    }
}

QString Record::toString() {
    QString newString = 
            "Session record:\n";
            + startTime.toString("ddd h:mm ap") + "\n"
            + "   ChallengeLevel: " + QString::number(challengeLevel) + "\n"
            + "Low percentage: " + QString::number(lowPercentage) + "\n"
            + "Medium percentage: " + QString::number(medPercentage) + "\n"
            + "High percentage: " + QString::number(highPercentage) + "\n"
            + "Average coherence: " + QString::number(averageCoherence) + "\n"
            + "Length: " + QString::number(length) + " seconds\n"
            + "Achievement score: " + QString::number(achievementScore) + "\n"
            + "HRV graph: ";
    for (double value : hrvGraph) {
        newString += QString::number(value) + " ";
    }
    newString += "\n";
    return newString;
}
//getters
QDateTime Record::getStartTime() { return startTime;}
int Record::getchallengeLevel() { return challengeLevel; }
double Record::getLowPercentage() { return lowPercentage; }
double Record::getMedPercentage() { return medPercentage; }
double Record::getHighPercentage() { return highPercentage; }
double Record::getAverageCoherence() { return averageCoherence; }
int Record::getLength(){return length;}
double Record::getAchievementScore(){return achievementScore;}
