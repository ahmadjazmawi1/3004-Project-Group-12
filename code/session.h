#ifndef SESSION_H
#define SESSION_H
#include <iostream>
#include <map>
using namespace std;
#include <QString>
#include <QStringList>
#include <QVector>
#include <QDateTime>
class Session
{
public:
    Session();
    //getters
    double getCurrCoherence();
    double getTotalCoherence();
    double getLength();
    double getAchievement();
    double getAvgCoherence();

    //calculators
    void calculateCoherence();
    void calculateAchievement();
    void calculateChallengeL();
    std::map<int, int> generateData();
    std::map<int, int> data;
    QDateTime getTime();
    double currCoherence;






private:

    double totalCoherence;
    double length;
    double achievement;
    int avgCoherence;
    QVector<int> timeInCoherenceLevel;    //stores the length of time in each coherence level. index 0 is for level 1, index 1 is for level 2, and so on
    int challengeLevel;
    QString coherenceLevel;
    QDateTime startTime;


};

#endif // SESSION_H
