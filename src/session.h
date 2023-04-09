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
        Session(int length, double coherenceScore, double achievementScore, bool isHRContact);
        ~Session();

        double getLength();
        void setLength(double length);
        QTimer* getTimer(); 
        double getCoherenceScore();  
        void setAchievementScore(double achievementScore);
        double getAchievementScore();  
        bool isHRContactOn();
        int getCoherenceLevel(); //1 is low, 2 is medium, 3 is high
        void updateCoherenceScore();
        void updateAchievementScore(double);
        void setHRContact(bool);
        void updateCoherenceLevel();
        void beep();
        QVector<double>* simulateHeartIntervals(double timeLimit);   //generate random heart beat intervals up to the limit
        void calCLPercentage();  //eg: lowPercentage = lowCount /(lowCount + mediumCount + highCount)
        double getLowPercentage();
        double getmediumPercentage();
        double getHighPercentage();
        void updateHRVData(QVector<QPointF>* newData);

    private:
        double length;    //how long a session lasts
        QTimer* timer;   //A QTimer object to keep track of the time
        double coherenceScore;
        double achievementScore;
        bool isHRContact; 
        int coherenceLevel; //0-1 score is low(0), 1-2 score is medium(1), >=2 is high(2)
        int lowCount;
        int mediumCount;
        int highCount;
        double lowPercentage;
        double mediumPercentage;
        double highPercentage;
        QVector<QPointF>* hrvData;

        double generateRandomDouble(double min, double max);
};
#endif
