#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <vector>
#include <random>
#include <time.h>


using namespace std;
//Session object to hold information about a new session of measurement
class Session: public QObject {

    Q_OBJECT

    public: 
        Session(int length, double coherenceScore, double achievementScore, int challengeLevel, int bpInterval, bool isHRContact);
        ~Session();

        double getLength();
        void setLength(double length);
        QTimer* getTimer(); 
        double getCoherenceScore();  
        void setAchievementScore(double achievementScore);
        double getAchievementScore();  
        int getChallengeLevel();
        int getBPInterval();    //how to implement breath pacer?
        bool isHRContactOn();
        QString getCoherenceLevel();
        void updateCoherenceScore(double);
        void updateAchievementScore(double);
        void setHRContact(bool);
        void updateCoherenceLevel(QString level);
        double calculator(vector<double>*); //???
        void beep();
        QVector<double>* simulateHeartIntervals(double timeLimit);   //generate random heart beat intervals up to the limit
        void updateHRVGraph();
        void calCLPercentage();
        double getLowPercentage();
        void updateHRVData(QVector<QPointF>* newData);

    private:
        double length;    //how long a session lasts
        QTimer* timer;   //A QTimer object to keep track of the time
        double coherenceScore;
        double achievementScore;
//        int challengeLevel;
//        int bpInterval;
        bool isHRContact; 
        int coherenceLevel; //0 is low, 1 is medium, 2 is high
        int lowCount;
        int mediumCount;
        int hightCount;
        double lowPercentage;
        QVector<QPointF>* hrvData;

        double generateRandomDouble(double min, double max);
};
#endif
