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
    this->lowCoherenceData = {{0, 60}, {1, 75}, {2, 76}, {3, 90}, {4, 70}, {5, 72}, {6, 60}, {7, 80},
                              {8, 81}, {9, 85}, {10, 70}, {11, 70}, {12, 80}, {13, 75}, {14, 100},
                              {15, 60}, {16, 80}, {17, 70}, {18, 75}, {19, 80}, {20, 81}, {21, 85},
                              {22, 89}, {23, 80}, {24, 85}, {25, 70}, {26, 63}, {27, 75}, {28, 80},
                              {29, 88}, {30, 95}, {31, 65}, {32, 66}, {33, 67}, {34, 68}, {35, 72},
                              {36, 73}, {37, 74}, {38, 80}, {39, 83}, {40, 84}, {41, 85}, {42, 90},
                              {43, 91}, {44, 89}, {45, 88}, {46, 87}, {47, 86}, {48, 88}, {49, 90},
                              {50, 91}, {51, 92}, {52, 92}, {53, 91}, {54, 91}, {55, 88}, {56, 88},
                              {57, 85}, {58, 82}, {59, 75}, {60, 72}, {61, 73}, {62, 74}, {63, 80},
                              {64, 81}};
    this->highCoherenceData = {{0, 70}, {1, 90}, {2, 80}, {3, 70}, {4, 60}, {5, 50}, {6, 70}, {7, 90},
                               {8, 100}, {9, 90}, {10, 70}, {11, 65}, {12, 55}, {13, 50}, {14, 70},
                               {15, 90}, {16, 80}, {17, 70}, {18, 60}, {19, 50}, {20, 70}, {21, 90},
                               {22, 100}, {23, 90}, {24, 65}, {25, 65}, {26, 55}, {27, 50}, {28, 45},
                               {29, 50}, {30, 55}, {31, 65}, {32, 65}, {33, 90}, {34, 100}, {35, 90},
                               {36, 70}, {37, 50}, {38, 70}, {39, 90}, {40, 80}, {41, 70}, {42, 60},
                               {43, 50}, {44, 70}, {45, 90}, {46, 100}, {47, 90}, {48, 70}, {49, 65},
                               {50, 55}, {51, 50}, {52, 70}, {53, 70}, {54, 90}, {55, 80}, {56, 70},
                               {57, 60}, {58, 50}, {59, 70}, {60, 90}, {61, 100}, {62, 90}, {63, 70},
                               {64, 65}};
    //What I am trying to do:
    //create a vector that contains maps. we should have an attribute that keeps track of which map we're accessing by the index
    this->hrvData.append(this->lowCoherenceData);
    this->hrvData.append(this->highCoherenceData);
    this->cohIdx=0;
    this->hiOrLo=0;
    this->coherences2d.append(this->lowCoherences);
    this->coherences2d.append(this->highCoherences);

}

std::map<int, int> Session::generateData(){
    srand((unsigned) time(NULL));
    this->data[data.size()] = 40 + (rand() % 61);
    return this->data;

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
