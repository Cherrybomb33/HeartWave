#include "session.h"
#include <QDebug>

Session::Session() {
    this->length = 0;
    this->coherenceScore = 0;
    this->achievementScore = 0;
    this->isHRContact = true;
    this->coherenceLevel = 0;
    this->lowCount = 0;
    this->mediumCount = 0;
    this->highCount = 0;
    this->lowPercentage = 0.0;
    this->mediumPercentage = 0.0;
    this->highPercentage = 0.0;
    // initialize the HRV graph with empty data
    this->hrvData = new QVector<QPointF>();
}

Session::~Session() {
    delete this->hrvData;
}

double Session::getLength() {
    return this->length;
}

void Session::setLength(double length) {
    this->length = length;
}

double Session::getCoherenceScore() {
    return this->coherenceScore;
}

double Session::getAchievementScore() {
    return this->achievementScore;
}

bool Session::isHRContactOn() {
    return this->isHRContact;
}

int Session::getCoherenceLevel() {
    return coherenceLevel;
}

void Session::updateCoherenceLevel() {
    if (this->coherenceScore < 1) {
        coherenceLevel = 0;
    } else if (this->coherenceScore >= 1 && this->coherenceScore < 2) {
        coherenceLevel = 1;
    } else {
        coherenceLevel = 2;
    }
}

void Session::updateCoherenceScore() {
    this->coherenceScore = generateRandomDouble(0,3);
    if (this->coherenceScore < 1) {
        lowCount++;
    } else if (this->coherenceScore >= 1 && this->coherenceScore < 2) {
        mediumCount++;
    } else {
        highCount++;
    }
    updateAchievementScore(this->coherenceScore);
}

void Session::updateAchievementScore(double value) {
    achievementScore += value;
}

void Session::calCLPercentage() {
    int totalCount = lowCount + mediumCount + highCount;
    if (totalCount != 0) {
        lowPercentage = lowCount / (double)totalCount;
        mediumPercentage = mediumCount / (double)totalCount;
        highPercentage = highCount / (double)totalCount;
    }
}

double Session::getLowPercentage() {
    return lowPercentage;
}

double Session::getmediumPercentage() {
    return mediumPercentage;
}

double Session::getHighPercentage() {
    return highPercentage;
}

void Session::setHRContact(bool value) {
    isHRContact = value;
}

void Session::beep() {
    // implement the beep sound
    qDebug() << "beep";
}

// append newData into hrvData.
void Session::updateHRVData(QVector<QPointF>* newData) {
    for (auto it = newData->begin(); it != newData->end();++it) {
        this->hrvData->append(*it);
    }
}

// This function generates random heartbeat intervals as the original data for the program
// There are 3 phases of generation, and the interval generated by this function
// will be closer and closer to each other
// @param:
// timeLimit: the output data total time limit
QVector<double>* Session::simulateHeartIntervals(double timeLimit) {
    QVector<double>* heartIntervals = new QVector<double>();
    srand(time(NULL));
    double curTotal = 0;
    double randomNum = 0;
    while (curTotal < timeLimit) {

        if (curTotal < timeLimit/3) {
            randomNum = generateRandomDouble(0.6,1);
            heartIntervals->push_back(randomNum);
        }
        else if (curTotal >= timeLimit/3 && curTotal < timeLimit * 2 / 3) {
            randomNum = generateRandomDouble(0.7,0.9);
            heartIntervals->push_back(randomNum);
        }
        else {
            randomNum = generateRandomDouble(0.75,0.85);
            heartIntervals->push_back(randomNum);
        }
        curTotal += randomNum;
    }
    return heartIntervals;
}

// This is used for generate random double for the simulateHeartIntervals(int size) function
double Session::generateRandomDouble(double min, double max) {
    double temp = (double)rand() / RAND_MAX;
    return min + temp * (max - min);
}
