#include "session.h"

// constructor to create a new session object
Session::Session() {
    this->startTime = QDateTime::currentDateTime();
    this->length = 0;
    this->timer = new QTimer();
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
    lostTime = 0.0;
}

// destructor to clean up memory used by the session object
Session::~Session() {
    delete hrvData;
    delete timer;
}

QDateTime Session::getStartTime() {return startTime;}

// getter function to return the length of the session
double Session::getLength() {return this->length;}

QTimer* Session::getTimer() {return this->timer;}

// getter function to return the coherence score
double Session::getCoherenceScore() {return this->coherenceScore;}

// getter function to return the achievement score of the session
double Session::getAchievementScore() {return this->achievementScore;}

// 1 is low, 2 is medium, 3 is high
int Session::getCoherenceLevel() {return coherenceLevel;}

// getter function to return the percentage of low coherence levels
double Session::getLowPercentage() {return lowPercentage;}

// getter function to return the percentage of medium coherence levels
double Session::getmediumPercentage() {return mediumPercentage;}

// getter function to return the percentage of high coherence levels
double Session::getHighPercentage() {return highPercentage;}

QVector<QPointF> *Session::getHRVData() {return hrvData;}

// setter function to set the length of the session
void Session::setLength(double length) {this->length = length;}

// setter function to set the achievement score of the session
void Session::setAchievementScore(double ach) {this->achievementScore = ach;}

// setter function to set whether HR contact is on
void Session::setHRContact(bool value) {isHRContact = value;}

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
    heartIntervals->pop_back();
    lostTime = timeLimit - curTotal + randomNum;
    return heartIntervals;
}

// calculate percentage of time in different coherence levels. eg: lowPercentage = lowCount /(lowCount + mediumCount + highCount)
void Session::calCLPercentage() {
    int totalCount = lowCount + mediumCount + highCount;
    if (totalCount != 0) {
        lowPercentage = lowCount * 100 / (double)totalCount;
        mediumPercentage = mediumCount * 100 / (double)totalCount;
        highPercentage = highCount * 100 / (double)totalCount;
    }
}

// function to update the coherence score of the session
void Session::updateCoherenceScore() {
    this->coherenceScore = generateRandomDouble(0,3);
    if (this->coherenceScore < 1) {
        lowCount++;
    } else if (this->coherenceScore >= 1 && this->coherenceScore < 2) {
        mediumCount++;
    } else {
        highCount++;
    }
}

// function to update the achievement score of the session
void Session::updateAchievementScore() {
    achievementScore += coherenceScore;
}

//function to update the coherence level of the session
void Session::updateCoherenceLevel() {
    int tempLevel;
    if (this->coherenceScore < 1) {
        tempLevel = 0;
    } else if (this->coherenceScore >= 1 && this->coherenceScore < 2) {
        tempLevel = 1;
    } else {
        tempLevel = 2;
    }
    if (tempLevel != coherenceLevel) {
        beep();
    }
    coherenceLevel = tempLevel;
}

// function to update the HRV data of the session (append newData into hrvData)
void Session::updateHRVData(QVector<QPointF>* newData) {
    for (auto it = newData->begin(); it != newData->end();++it) {
        this->hrvData->append(*it);
    }
}

void Session::updateAll() {
    updateCoherenceScore();
    updateAchievementScore();
    setLength(length+TIME_UPDATE);
    updateCoherenceLevel();
    QVector<double>* newDoubles = simulateHeartIntervals(TIME_UPDATE + lostTime);
    QVector<QPointF>* newPoints = calPoints(&newDoubles);
    updateHRVData(newPoints);
    delete newDoubles;
}

// to check if HR contact is on
bool Session::isHRContactOn() {
    return this->isHRContact;
}

// function to emit a beep signal
void Session::beep() {
    // implement the beep sound
    qInfo() << "***BEEP*** New coherence level is reached";
}

QVector<QPointF>* Session::calPoints(QVector<double>** times) {
    QVector<QPointF>* points = new QVector<QPointF>();
    for (int i = 0;i < (*times)->size();i++) {
        QPointF newPoint((*times)->at(i),60/(*times)->at(i));
        points->push_back(newPoint);
    }
    return points;
}

// This is used for generate random double for the simulateHeartIntervals(int size) function
double Session::generateRandomDouble(double min, double max) {
    double temp = (double)rand() / RAND_MAX;
    return min + temp * (max - min);
}
