#include "session.h"
#include <iostream>
using namespace std;
Session::Session()
{
    this->data = generateData();
    this->startTime = QDateTime::currentDateTime();
    this->currCoherence = 0.0;
    this->length = 00.00;
    this->achievement = 0.0;
    this->challengeLevel = 1;

}

std::map<int, int> Session::generateData(){
    srand((unsigned) time(NULL));
    this->data[data.size()] = 40 + (rand() % 61);
    return this->data;
//    srand((unsigned) time(NULL));
//      std::map<int, int> map;
//      for(int i=1;i<65;++i){
//        map[i] = 40 +(rand() % 61);
//      }
//      return map;
}

QDateTime Session::getTime(){
    return this->startTime;
}

double Session::getCurrCoherence(){
    return this->currCoherence;
}

double Session::getAchievement(){
    return this->achievement;
}

double Session::getLength(){
    return this->length;
}
int Session::getChallengeLevel(){
    return this->challengeLevel;
}

void Session::setChallengeLevel(int c){
    this->challengeLevel = c;
}
