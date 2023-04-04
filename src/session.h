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

        int getTime();
        QTimer* getTimer(); 
        double getCoherenceScore();  
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
        vector<double>* simulateHeartIntervals(int size);   //generate random heart beat intervals
        void updateHRVGraph();

    private:
        double length;    //how long a session lasts
        QTimer* timer;   //A QTimer object to keep track of the time
        double coherenceScore;
        double achievementScore;
        int challengeLevel; 
        int bpInterval;   
        bool isHRContact; 
        QString coherenceLevel;

        double generateRandomDouble(double min, double max);
};
#endif
