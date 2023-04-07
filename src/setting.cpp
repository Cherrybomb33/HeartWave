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

void Setting::setBpInterval(int bpInterval) {
    this->bpInterval = bpInterval;
}

//reset the configuration to the initial state
void Setting::reset(){
	setChallengeLevel(1);
	setBpInterval(10);
}
