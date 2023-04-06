#include "setting.h"

//constructor
Setting::Setting(int challengeLevel, int bpInterval): challengeLevel(challengeLevel), bpInterval(bpInterval){

}

//getters and setter
int Setting::getChallengeLevel() {
    return challengeLevel;
}

int Setting::getBpInterval() {
    return bpInterval;
}

void Setting::setChallengeLevel(int challengeLevel) {
    this->challengeLevel = challengeLevel;
}

void Setting::setBreathPacer(int bpInterval) {
    this->bpInterval = bpInterval;
}
