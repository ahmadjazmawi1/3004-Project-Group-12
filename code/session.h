#ifndef SESSION_H
#define SESSION_H
#include <iostream>
#include <map>
using namespace std;
#include <QString>
#include <QStringList>
#include <QVector>
#include <QDateTime>
#include <QElapsedTimer>
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
    //index used to iterate throught the values. index only changes after every call to populateMetrics function
    int currIndex;
    double achievement;
    std::map<int, int> lowCoherenceData;    //stores HRV data for low case

    std::map<int, int> highCoherenceData;   //stores HRV data for high case
    QVector<double> lowCoherences = {0.509, 0.587, 1.3, 0.599, 0.594, 0.3, 0.596, 0.605, 0.680, 0.612, 0.559, 0.622};       //stores coherence values for low case
    QVector<double> highCoherences = {0.4, 1.5, 2.9, 10.2, 11.1, 9.8, 8.8, 9.0, 9.2, 9.5, 9.8, 9.6};      //stores coherence values for high case
    int cohIdx;     //coherence index, to keep track of whether or not to loop through the values again
    QVector<map<int, int>> hrvData;         /*stores 2 maps, one for low coherence and one for high coherence.
    //I did this because if I were to use the individual maps, I'd need if statements every time I want to
    //decide which map to use based on what type I want to generate. Instead I add the 2 maps to an array and choose the
    map at the randomly generated index*/
    int hiOrLo;     //keeps track of whether we should use high or low coherence HRV data. 0 if low, 1 if high
    QVector<QVector<double>> coherences2d;    //stores 2 vectors of coherences, one for low and one for high
    QVector<double> x;
    QVector<double> y;
    int arrIdx;
    QTime elTimer;              //elapsed time
    int hh;
    int mm;
    int ss;


private:

    double totalCoherence;
    double length;
    int avgCoherence;
    QVector<int> timeInCoherenceLevel;    //stores the length of time in each coherence level. index 0 is for level 1, index 1 is for level 2, and so on
    int challengeLevel;
    QString coherenceLevel;
    QDateTime startTime;


};

#endif // SESSION_H
