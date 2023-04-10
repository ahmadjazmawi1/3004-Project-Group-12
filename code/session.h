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

/*
 * class purpose: The session class stores all the data related to a session
 *
 * Data Members
 *  int currIndex:          index used to iterate throught the coherence score values. index only changes after every call to populateMetrics function. reset to 0 when we need to reset the coherence score values
    double achievement:     stores the achievement score
    std::map<int, int> lowCoherenceData; stores HRV data for low coherence case

    std::map<int, int> highCoherenceData; stores HRV data for high coherence case
    QVector<double> lowCoherences:  stores coherence score values for low coherence case
    QVector<double> highCoherences: stores coherence score values for high coherence case
    int cohIdx:             stores the number of seconds the session has been running for. Used in the graph as the x axis
    QVector<map<int, int>> hrvData: stores 2 maps of HRV data, one for low coherence case and one for high coherence. I did this because if I were to use the individual maps, I'd need if statements every time I want to decide which map to use based on what type I want to generate. Instead I add the 2 maps to an array and choose the map at the randomly generated index
    int hiOrLo:             randomly generated index used to indicate which HRV data map will be graphed. 0 if low, 1 if high
    QVector<QVector<double>> coherences2d: stores 2 vectors of coherence scores, one for low coherence case, the other for high coherence
    QVector<double> x:      used as the x axis for the graph
    QVector<double> y:      used as the y axis for the graph
    int arrIdx:             used to indicate the key in the map to be inserted into x
    int hh:                 stores the hours the device has been running for, used for length label
    int mm:                 stores number of minutes the device has been running for, used for length label
    int ss:                 stores the number of seconds the device has been running for, used for length label
    double avgCoherence:    stores the average coherence score for use in the summary view
    int numCoh:             stores the number of coherence scores that have been graphed, to calculate average coherence
    QVector<int> timeInCoherenceLevel:  stores the length of time in each coherence level. index 0 is for level 1, index 1 is for level 2, and so on
    int challengeLevel;

    QDateTime startTime:    the time the session started
 *
 *
 * class functions:
    Session():                      constructor to initialize all Data members
    double getAchievement():        returns the achievement score
    void setChallengeLevel(int):    sets the challenge level
    QDateTime getTime():            returns the time the session started




*/

class Session
{
public:
    Session();
    double getAchievement();
    void setChallengeLevel(int);
    QDateTime getTime();

    double currCoherence;
    int currIndex;
    double achievement;
    std::map<int, int> lowCoherenceData;
    std::map<int, int> highCoherenceData;
    QVector<double> lowCoherences = {0.509, 0.587, 1.3, 0.599, 0.594, 0.3, 0.596, 0.605, 0.680, 0.612, 0.559, 0.622};
    QVector<double> highCoherences = {0.4, 1.5, 2.9, 10.2, 11.1, 9.8, 8.8, 9.0, 9.2, 9.5, 9.8, 9.6};
    int cohIdx;
    QVector<map<int, int>> hrvData;
    int hiOrLo;
    QVector<QVector<double>> coherences2d;
    QVector<double> x;
    QVector<double> y;
    int arrIdx;
    int hh;
    int mm;
    int ss;
    double avgCoherence;
    int numCoh;

private:


    QVector<int> timeInCoherenceLevel;
    int challengeLevel;

    QDateTime startTime;


};

#endif // SESSION_H
