#ifndef SETTING_H
#define SETTING_H

//modify the setting of challenge level, breath pacer and achieve reset functionality
class Setting {

public:
    //constructor
    Setting(int challengeLevel = 1, int bpInterval = 10);    

    //getters and setters
    int getChallengeLevel();
    int getBpInterval();
    void setChallengeLevel(int);
    void setBpInterval(int);
    
    //reset the configuration to the initial state
    void reset();

private:
    int challengeLevel;
    int bpInterval;
};

#endif
