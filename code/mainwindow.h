#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "menu.h"
#include "session.h"
#include <QMainWindow>
#include <QListWidget>
#include <QVector>
#include <QTimer>
/*
 * class purpose: The mainwindow class will start the simulation process and ends it will hold all the slots and will call on the session and provides that updates functionality to keep user alerted of what is going on also holds ui implantation like battery functionality
 *
 * Data Members
 * Menu* masterMenu;
    Menu* mainMenu;
    QListWidget *activeQListWidget; keeps track of the currently selected widget in the list
    QStringList breathPList;
    QStringList settingList;
    QStringList challengeList;
    QStringList histList;   //stores the dates for sessions, to be used in the history screen to show the dates of sessions
    int currChallenge=1;
    int currPacer=10; speed of the pacer based on what is elected by the user
    bool powerStatus: used to check power status
    bool isSession=false: this will allow use to stop and start a new session based on what the previous functionality set the this variable as we have on HR button so of pressed tice the session is set to fall meaning we no longer have HR contact
    Session *session: session used to create a new session start the graph
    QVector<Session*> allSessions;  Stores the session objects that were created for use in history
    bool inSummary=false;
    QTimer *graphTimer:  graphs the data every second
    QTimer *dataTimer :generates 1 data value every second

    int BatteryLevel: battery level
    QTimer *simTime: simulator time
    QTimer *breathPTimer: breath pacer time


 *
 *
 * class functions:
 *  MainWindow(QWidget *parent = nullptr): constructor to initialize all pout Data members and widgets needed to drive the simulator
    ~MainWindow(); destructor
    std::map<int, int> generateData();
    void initMenus(Menu*): is the main master menu holds all the other child menus in them this where we initialize all other child menus functionality
    void updateMenu(const QString, const QStringList); This function is used mainly to update our menus based on what the user dose
    void BatLevel(double batLevel): this hold the functionality for the battery depressing and charging and change the variable that holds the battery variable
    void populateMetrics(Session* s); This populates/calculates the coherence and achievement values. Making sure to call the right functions for LED lights as well.

   private:

    void upButton();    enables movement to the menu option above
    void downButton();  enables movement to the menu option below
    void leftButton();
    void rightButton();
    void okButton(): enables the movements from one main menu to the child menus
    void backButton(): allow us to go back to the menu mainly after entering new session after the session paused ONlY
    void powerButton(): turn the machine on and off
    void makeGraph(Session*): makes the graph
    void showSummary(Session*): shows the summary
    void handleTimeout();  handler for the makeGraph function since the timeout SLOT doesnt take parameters
    void ChargeBattery(): charges battery to 100%
    void useBattery(): uses timer that decreases the battery at a stable interval
    void newSess(Session*): starts a new session strarts the graph timer breath pacer timer
    void ledRed(): shows coherence level
    void ledBlue(); shows coherence level
    void ledGreen();shows coherence level
    void ledOff();initially off this will change when a shows coherence level is hit
    void moveBreathPacer(); moves the breath pacer based on the time selected by the user
    void deleteSession(Session*); deletes the session
    void handleDelete(); handler for the deleteSession function since the released SLOT doesnt take parameters
    void changeBreathPacer(int); connected to the breath pacer dropdown, stores the new value selected
    void contactHR(): starts the session when HR contact is found

*/
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::map<int, int> generateData();
    void initMenus(Menu*);
    void updateMenu(const QString, const QStringList);
    void BatLevel(double batLevel);
    void populateMetrics(Session* s);

private:
    Ui::MainWindow *ui;
    Menu* masterMenu;
    Menu* mainMenu;
    QListWidget *activeQListWidget;

    QStringList histList;
    int currChallenge=1;
    int currPacer=10;
    bool powerStatus;
    bool isSession=false;
    Session *session;
    QVector<Session*> allSessions;
    bool inSummary=false;
    QTimer *graphTimer;         //graphs the data every second
    QTimer *dataTimer;          //generates 1 data value every second
    QTimer *metricsTimer;

    int BatteryLevel;
    QTimer *simTime;
    QTimer *breathPTimer;
    bool secondHR;




private slots:
    void upButton();
    void downButton();
    void leftButton();
    void rightButton();
    void okButton();
    void backButton();
    void powerButton();
    void makeGraph(Session*);
    void showSummary(Session*);
    void handleTimeout();
    void ChargeBattery();
    void useBattery();
    void newSess(Session*);
    void ledRed();
    void ledBlue();
    void ledGreen();
    void ledOff();
    void moveBreathPacer();
    void deleteSession(Session*);
    void handleDelete();
    void handlePopulateMetrics();
    void changeBreathPacer(int);
    void contactHR();
};
#endif // MAINWINDOW_H
