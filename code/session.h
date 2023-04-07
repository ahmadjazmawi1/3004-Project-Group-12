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
    int getChallengeLevel();
    //calculators
    void calculateCoherence();
    void calculateAchievement();
    void calculateChallengeL();
    std::map<int, int> generateData();
    std::map<int, int> data;
    QDateTime getTime();
    void setChallengeLevel(int);
    double currCoherence;
    std::map<int, int> lowCoherenceData;    //stores HRV data for low case

    std::map<int, int> highCoherenceData;   //stores HRV data for high case
    QVector<double> lowCoherences = {0.509, 0.587, 0.547, 0.599, 0.594, 0.599, 0.596, 0.605, 0.680, 0.612, 0.559, 0.622};       //stores coherence values for low case
    QVector<double> highCoherences = {0.4, 1.5, 2.9, 10.2, 11.1, 9.8, 8.8, 9.0, 9.2, 9.5, 9.8, 9.6};      //stores coherence values for high case
    int cohIdx;     //coherence index, to keep track of whether or not to loop through the values again
    QVector<map<int, int>> hrvData;
    int hiOrLo;
    QVector<QVector<double>> coherences2d;    //stores 2 vectors of coherences, one for low and one for high
    QVector<double> x;
    QVector<double> y;



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
