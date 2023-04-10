#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <vector>
#include <random>
#include <time.h>
#include <QPointF>


using namespace std;
#define TIME_UPDATE 5
//Session object to hold information about a new session of measurement
class Session: public QObject {

    Q_OBJECT

    public: 
        Session(); // constructor to create a new session object
        ~Session(); // destructor to clean up memory used by the session object

        double getLength();            // getter function to return the length of the session
        QTimer* getTimer();
        double getCoherenceScore();    // getter function to return the coherence score
        double getAchievementScore();  // getter function to return the achievement score of the session
        int getCoherenceLevel();       // 1 is low, 2 is medium, 3 is high
        double getLowPercentage();     // getter function to return the percentage of low coherence levels
        double getmediumPercentage();  // getter function to return the percentage of medium coherence levels
        double getHighPercentage();    // getter function to return the percentage of high coherence levels
        QVector<QPointF>* getHRVData();

        void setLength(double length); // setter function to set the length of the session
        void setAchievementScore(double achievementScore); // setter function to set the achievement score of the session
        void setHRContact(bool);       // setter function to set whether HR contact is on

        QVector<double>* simulateHeartIntervals(double timeLimit);   //generate random heart beat intervals up to the limit
        void calCLPercentage();  // calculate percentage of time in different coherence levels. eg: lowPercentage = lowCount /(lowCount + mediumCount + highCount)
        void updateCoherenceScore();  // function to update the coherence score of the session
        void updateAchievementScore(); // function to update the achievement score of the session
        void updateCoherenceLevel(); //function to update the coherence level of the session
        void updateHRVData(QVector<QPointF>* newData);  // function to update the HRV data of the session
        bool isHRContactOn();  // to check if HR contact is on
        void beep();  // function to emit a beep signal

    public slots:
        void updateAll();
    private:
        double length;  // the length of the session
        QTimer* timer;
        double coherenceScore; // the coherence score of the session
        double achievementScore; // the achievement score of the session
        bool isHRContact; // whether HR contact is on
        int coherenceLevel; // the coherence level of the session (0-1 is low, 1-2 is medium, >=2 is high)
        int lowCount; // the count of low coherence levels
        int mediumCount; // the count of medium coherence levels
        int highCount; // the count of high coherence levels
        double lowPercentage; // the percentage of low coherence levels
        double mediumPercentage; // the percentage of medium coherence levels
        double highPercentage; // the percentage of high coherence levels
        QVector<QPointF>* hrvData; // the HRV data of the session

        double generateRandomDouble(double min, double max); //generate random data
        QVector<QPointF> *calPoints(QVector<double> **times);
};
#endif
