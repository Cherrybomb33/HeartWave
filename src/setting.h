#ifndef SETTING_H
#define SETTING_H

//modify the setting of challenge level, breath pacer and achieve reset functionality
class Setting {

public:
    Setting(int challengeLevel, int breathPacer);    //constructor

    //getters and setters
    int getChallengeLevel();
    int getBreathPacer();
    void setChallengeLevel(int);
    void setBreathPacer(int);

private:
    int challengeLevel;
    int breathPacer;

};

#endif
