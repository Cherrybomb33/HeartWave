#ifndef SETTING_H
#define SETTING_H

//modify the setting of challenge level, breath pacer and achieve reset functionality
class Setting {

public:
    //constructor
    Setting(int challengeLevel = 0, int bpInterval = 10);    

    //getters and setters
    int getChallengeLevel();
    int getBpInterval();
    void setChallengeLevel(int);
    void setBpInterval(int);

private:
    int challengeLevel;
    int bpInterval;
};

#endif
