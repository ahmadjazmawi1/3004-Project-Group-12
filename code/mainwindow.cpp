#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
#include <iostream>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    masterMenu = new Menu("MAIN MENU", {"START NEW SESSION","HISTORY", "RESET"}, nullptr);
    activeQListWidget = ui->mainListWidget;
    activeQListWidget->addItems(masterMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);

    this->graphTimer = new QTimer(this);

    this->metricsTimer = new QTimer(this);

    initMenus(masterMenu);
    ui->Graphwidget->setVisible(false);
    ui->coherenceLabel->setVisible(false);
    ui->lengthLabel->setVisible(false);
    ui->achievementLabel->setVisible(false);
    ui->DELETE->setVisible(false);
    powerStatus=false;
    ui->screenDisplay->setStyleSheet("background-color: black");
    ui->mainListWidget->setVisible(powerStatus);
    ui->batteryLevel->setVisible(powerStatus);
    ui->mainMenu->setVisible(powerStatus);
    ui->breathPacer->setVisible(false);
    ui->inLabel->setVisible(false);
    ui->outLabel->setVisible(false);
    ui->HR_contact->setVisible(false);
    simTime = new QTimer(this);;
    breathPTimer = new QTimer(this);
    ui->bPSetting->setCurrentIndex(9);
    //this->secondHR=true;
    connect(ui->upButton, SIGNAL (released()), this, SLOT (upButton()));
    connect(ui->downButton, SIGNAL (released()), this, SLOT (downButton()));
    connect(ui->leftButton, SIGNAL (released()), this, SLOT (leftButton()));
    connect(ui->rightButton, SIGNAL (released()), this, SLOT (rightButton()));
    connect(ui->okButton, SIGNAL (released()), this, SLOT (okButton()));
    connect(ui->backButton, SIGNAL (released()), this, SLOT (backButton()));
    connect(ui->menuButton, SIGNAL (released()), this, SLOT (backButton()));
    connect(ui->powerButton, SIGNAL (released()), this, SLOT (powerButton()));
    connect(ui->chargeButton, SIGNAL (released()), this, SLOT (ChargeBattery()));
    connect(ui->bPSetting, SIGNAL(activated(int)), this, SLOT(changeBreathPacer(int)));
    connect(ui->CHSetting, SIGNAL(activated(int)), this, SLOT(changeCL(int)));
    connect(ui->HR_contact, SIGNAL (released()), this, SLOT (contactHR()));


    BatteryLevel = 60;

}

void MainWindow::makeGraph(Session* s){

    if(this->inSummary == false){   //only insert values into x and y if we are not in summary view (i.e. we're in new session)

        if(s->arrIdx==s->hrvData.at(s->hiOrLo).size()){ //check if we need to repeat HRV data from beginning
                    s->arrIdx=0;    //reset arrIdx to 0 because we need to access elements from the beginning (if not we'd get index out of bounds)
                }
        s->x.push_back(s->cohIdx);  //add the cohIdx (current second) to x
        s->y.push_back(s->hrvData.at(s->hiOrLo).at(s->arrIdx)); //add the heart rate in high coherence HRV map with key arrIdx into y


        s->arrIdx++;    //incrementing the key in the map to insert into y
        s->cohIdx++;    //incrementing cohIdx because it ran for a second
    }



    // create graph and assign data to it:
    ui->Graphwidget->addGraph();
    ui->Graphwidget->graph(0)->setData(s->x, s->y);

    // give the axes some labels:
    ui->Graphwidget->xAxis->setLabel("Time(Seconds)");
    ui->Graphwidget->yAxis->setLabel("Heart Rate");
    // set axes ranges, so we see all data:
    ui->Graphwidget->xAxis->setRange(0, s->cohIdx-1);
    ui->Graphwidget->yAxis->setRange(40, 100);

    ui->Graphwidget->replot();
}

void MainWindow::newSess(Session* s){
    //enabling widgets on new session screen
    ui->Graphwidget->setVisible(true);
    ui->coherenceLabel->setVisible(true);
    ui->avgCoherence->setVisible(false);
    ui->percentageHigh->setVisible(false);
    ui->percentageMed->setVisible(false);
    ui->percentageLow->setVisible(false);
    ui->lengthLabel->setVisible(true);
    ui->achievementLabel->setVisible(true);
    ui->breathPacer->setVisible(true);
    ui->inLabel->setVisible(true);
    ui->outLabel->setVisible(true);

    //initializing labels
    QString co = "Coherence\n"+QString::asprintf("%0.2f", s->currCoherence);
    ui->coherenceLabel->setText(co);
    QString le = "Length\n"+QString::asprintf("%2d:%2d:%2d", this->session->hh, this->session->mm, this->session->ss);
    ui->lengthLabel->setText(le);
    QString ach = "Achievement\n"+QString::asprintf("%0.2f", s->getAchievement());
    ui->achievementLabel->setText(ach);


    //setting up timers
    this->graphTimer = new QTimer(this);
    this->graphTimer->start(1000);
    connect(this->graphTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));


    this->metricsTimer = new QTimer(this);
    this->metricsTimer->start(6000);
    connect(this->metricsTimer, SIGNAL(timeout()), this, SLOT(handlePopulateMetrics()));

    ui->breathPacer->setValue(ui->breathPacer->minimum());
    breathPTimer->start(1000);
    connect(breathPTimer, SIGNAL (timeout()), this, SLOT (moveBreathPacer()));
}

void MainWindow::deleteSession(Session* s){
    backButton();
    //go back, and delete the session from the array
    allSessions.removeOne(s);
    this->histList.removeOne(s->getTime().toString("h:mm:ss ap"));
}
void MainWindow::handleDelete(){
    deleteSession(this->session);
}
//only have this function because timeout signal doesnt take parameters, and this is the only way to get around that limitation
void MainWindow::handleTimeout(){


    QString le = "Length\n"+QString::asprintf("%2d:%2d:%2d", this->session->hh, this->session->mm, this->session->ss);
    ui->lengthLabel->setText(le);
    this->session->ss++;
    if(this->session->ss > 59){
        this->session->mm++;
        this->session->ss=0;
    }
    if(this->session->mm > 59){
        this->session->hh++;
        this->session->mm=0;
    }

    makeGraph(this->session);
}

void MainWindow::handlePopulateMetrics(){
    populateMetrics(this->session);
}

void MainWindow::showSummary(Session* s){
    this->secondHR=false;
    this->graphTimer->stop();
    ui->breathPacer->setValue(ui->breathPacer->minimum());
    this->breathPTimer->stop();
    this->inSummary = true;

    //make widgets/labels visible
    ui->Graphwidget->setVisible(true);
    ui->coherenceLabel->setVisible(false);
    ui->avgCoherence->setVisible(true);
    ui->percentageHigh->setVisible(true);
    ui->percentageMed->setVisible(true);
    ui->percentageLow->setVisible(true);
    ui->lengthLabel->setVisible(true);
    ui->achievementLabel->setVisible(true);

    //initialize label text
    QString avg = "Avg Coherence\n" + QString::asprintf("  %0.3f", s->achievement/s->numCoh);
    ui->avgCoherence->setText(avg);

    QString le = "Length\n"+QString::asprintf("%2d:%2d:%2d", this->session->hh, this->session->mm, this->session->ss-1);
    ui->lengthLabel->setText(le);

    QString ach = "Achievement\n"+QString::asprintf("%0.1f", s->getAchievement());
    ui->achievementLabel->setText(ach);

    QString high = "High\n" + QString::asprintf("  %0.1f", (s->highPercentage/s->secondsCounter)*100) + "%";
    ui->percentageHigh->setText(high);

    QString med = "Med\n" + QString::asprintf("  %0.1f", (s->medPercentage/s->secondsCounter)*100) + "%";
    ui->percentageMed->setText(med);

    QString low = "Low\n" + QString::asprintf("  %0.1f", (s->lowPercentage/s->secondsCounter)*100) + "%";
    ui->percentageLow->setText(low);





    //make the graph, but this time dont add new values to x and y axis
    makeGraph(s);
}

void MainWindow::initMenus(Menu *m){
    Menu* newSession = new Menu("START NEW SESSION", {}, m);    //newSession menu created with masterMenu as its parent
    m->addChildMenu(newSession);                                //adding newSession as a child of masterMenu


    QStringList historyList;
    for(int i=0;i<this->allSessions.size();i++){
        historyList.append(this->allSessions.at(i)->getTime().toString("h:mm:ss ap"));  //appending the dates for all sessions
    }
    Menu* history = new Menu("HISTORY", histList, m);   //creating history menu with masterMenu as parent
    m->addChildMenu(history);                           //adding history as child of masterMenu
    for(int i=0;i<this->allSessions.size();i++){
        history->addChildMenu(new Menu(this->allSessions.at(i)->getTime().toString("h:mm ap"), {}, history)); //creating date menus with history as the parent
    }
    Menu* reset = new Menu("RESET", {}, m);             //creating reset menu with masterMenu as parent
    m->addChildMenu(reset);                             //adding reset as child of masterMenu


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::upButton(){
    int nextIndex = activeQListWidget->currentRow() - 1;

    //the case where the user presses up while currently hovering over the first menu option, changes the current option to the last one
    if (nextIndex < 0) {
        nextIndex = activeQListWidget->count() - 1;
    }

    activeQListWidget->setCurrentRow(nextIndex);

}

void MainWindow::downButton(){
    int nextIndex = activeQListWidget->currentRow() + 1;

    //the case where the user presses down while currently hovering over the last menu option, changes the current option to the first one
    if (nextIndex > activeQListWidget->count() - 1) {
        nextIndex = 0;
    }

    activeQListWidget->setCurrentRow(nextIndex);

}

void MainWindow::leftButton(){


}

void MainWindow::rightButton(){

}

void MainWindow::changeCL(int c){
    this->session->setChallengeLevel(c);
}
void MainWindow::changeBreathPacer(int b){
    ui->breathPacer->setValue(ui->breathPacer->minimum());
    this->currPacer = b+1;
}

void MainWindow::okButton(){

    int index = activeQListWidget->currentRow();    //to keep track of which menu option is currently selected

    QString n = masterMenu->getName();
    //in case user presses ok in an empty screen
    if(index < 0)
        return;
    //reset option. clears the vector containing session objects and the vector containing session dates
    if(index == 2 && masterMenu->getName() == "MAIN MENU"){
        allSessions.clear();
        histList.clear();

    }

    //starting a new session
    else if(index==0 && masterMenu->getName() == "MAIN MENU"){
        ui->HR_contact->setVisible(true);
        this->session = new Session();
        this->secondHR=true;
        MainWindow::updateMenu(this->session->getTime().toString(), {});    //clears the menu options from the screen
        return;
    }

    //showing summary view when clicking on a date in history screen
    else if(masterMenu->getName() == "HISTORY"){        //checks if user clicked ok on a date by checking if parent menu is
                                                        //HISTORY. had to do this because history doesnt have child menus since
                                                        //history is generated when a session ends. at the beginning theres no
                                                        //history. Thus to avoid causing a seg fault, I check if parent is HSITORY
        this->session = allSessions.at(index);
        ui->DELETE->setVisible(true);
        connect(ui->DELETE, SIGNAL(released()), this, SLOT(handleDelete()));

        MainWindow::updateMenu(allSessions.at(index)->getTime().toString(), {});    //clears the menu options from th screen

        showSummary(allSessions.at(index)); //show the summary screen for the selected session
        return;
    }

    //showing session dates in HISTORY option
    else if(masterMenu->get(index)->getName() == "HISTORY"){    //checks if use clicked ok on history option by checking if
                                                                //child menu at index is HISTORY
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu(masterMenu->getName(), histList); //clears the menu options from th screen and adds session dates

    }

}

void MainWindow::contactHR(){

    //ends a session
    if(this->isSession == true){

        this->allSessions.append(this->session);    //add the session to the array of sessions (used for history)
        this->histList.append(this->session->getTime().toString("h:mm:ss ap")); //add the date of the session to the array of dates

        ledOff();
        this->metricsTimer->stop();
        this->isSession=false;      //set isSession to false, because the session is over

        showSummary(this->session);
        //ui->HR_contact->setVisible(false);  //uncomment if Voja says he likes it and its good with the specs
        return;
    }else{
        //HR contact found start session
        newSess(this->session);
        this->isSession = true; //set session to true
    }


}

void MainWindow::backButton(){
    //if we're in the summary screen, hide everything and add the master menu options back
    if(this->inSummary==true){
        ui->Graphwidget->setVisible(false);
        ui->coherenceLabel->setVisible(false);
        ui->lengthLabel->setVisible(false);
        ui->achievementLabel->setVisible(false);
        ui->breathPacer->setVisible(false);
        ui->inLabel->setVisible(false);
        ui->outLabel->setVisible(false);
        ui->avgCoherence->setVisible(false);
        ui->percentageHigh->setVisible(false);
        ui->percentageMed->setVisible(false);
        ui->percentageLow->setVisible(false);
        ui->DELETE->setVisible(false);
        ui->HR_contact->setVisible(false);
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());

        this->inSummary = false;
    }

    //to avoid crashing the device
    if (masterMenu->getName() == "MAIN MENU") {
        activeQListWidget->setCurrentRow(0);
    }
    //for returning from newSession to main menu
    else {
        masterMenu = masterMenu->getParent();
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());  //clear the screen and add main menu options
    }

}



void MainWindow::powerButton(){

        if(powerStatus==false && BatteryLevel > 0){
            powerStatus=true;
            ui->screenDisplay->setStyleSheet("background-color: white");

            simTime->start(10000);
            connect(simTime, SIGNAL (timeout()), this, SLOT (useBattery()));

        }else{
            powerStatus=false;
            ui->screenDisplay->setStyleSheet("background-color: black");
        }
        ui->batteryLevel->setVisible(powerStatus);
        ui->mainListWidget->setVisible(powerStatus);
        ui->mainMenu->setVisible(powerStatus);


}

void MainWindow::ChargeBattery() {

    int batteryLevel = 100.0;
    BatLevel(batteryLevel);
}
void MainWindow::useBattery() {
    if (BatteryLevel>0){
        BatteryLevel-=1.0;

        BatLevel(BatteryLevel);
    }else{
        qInfo("Critcial Battery Level reached system will shut down !!!!");
        qInfo("Please Re-Charge!!!");
        powerStatus=false;
        ui->screenDisplay->setStyleSheet("background-color: black");

        ui->batteryLevel->setVisible(powerStatus);
        ui->mainListWidget->setVisible(powerStatus);
        ui->mainMenu->setVisible(powerStatus);
    }

}
void MainWindow::BatLevel(double batLevel) {

    if (batLevel >= 0.0 && batLevel <= 100.0) {
        if (batLevel == 0.0 && powerStatus == true) {

            BatteryLevel=0;
        }else{
            BatteryLevel=batLevel;
        }


        int adjLevel = int(batLevel);
        ui->batteryLevel->setValue(adjLevel);

        QString greenBat = "QProgressBar { selection-background-color: rgb(78, 154, 6); background-color: rgb(0, 0, 0); }";
        QString yellowBat = "QProgressBar { selection-background-color: rgb(196, 160, 0); background-color: rgb(0, 0, 0); }";
        QString redBat = "QProgressBar { selection-background-color: rgb(164, 0, 0); background-color: rgb(0, 0, 0); }";

        if (adjLevel >= 50) {
            ui->batteryLevel->setStyleSheet(greenBat);
        }
        else if (adjLevel >= 20) {
            ui->batteryLevel->setStyleSheet(yellowBat);
        }
        else {
            ui->batteryLevel->setStyleSheet(redBat);
        }
    }

}
void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems){
    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);
}

//Led Indicator light functions:
void MainWindow::ledGreen(){
    ui->ledIndicator->setStyleSheet("background-color: green");
}

void MainWindow::ledBlue(){
    ui->ledIndicator->setStyleSheet("background-color: blue");
}

void MainWindow::ledRed(){
    ui->ledIndicator->setStyleSheet("background-color: red");
}

void MainWindow::ledOff(){
    ui->ledIndicator->setStyleSheet("background-color: rgb(211, 215, 207)");

}

void MainWindow::moveBreathPacer(){
    ui->breathPacer->setVisible(powerStatus);
    int pace = currPacer;
    float max = ui->breathPacer->value()+ (ui->breathPacer->maximum()/pace);
    if(ui->breathPacer->value()+1 > ui->breathPacer->maximum()){
        ui->breathPacer->setValue(ui->breathPacer->minimum());
    }
    else {
        ui->breathPacer->setValue((max));
    }

}

void MainWindow::populateMetrics(Session* s){
        s->secondsCounter+=1;

       if(s->currIndex==s->lowCoherences.size()-1){
           s->currIndex=0;
       }

       s->currIndex++;
       s->currCoherence=s->coherences2d[s->hiOrLo][s->currIndex];
       s->achievement+=s->coherences2d[s->hiOrLo][s->currIndex];
       s->numCoh++;
       QString co = "Coherence\n"+QString::asprintf("%0.3f", s->currCoherence);
       ui->coherenceLabel->setText(co);

       QString ach = "Achievement\n"+QString::asprintf("%0.3f", s->getAchievement());
       ui->achievementLabel->setText(ach);

       if(s->currCoherence<0.5){
           ledRed();
           cout << "BEEP! Low coherence reached" <<endl;
           s->lowPercentage+=1;
       }
       if(s->currCoherence>0.5 && s->currCoherence<1){
           ledBlue();
           cout << "BEEP! Medium coherence reached" <<endl;
            s->medPercentage+=1;
       }
       if(s->currCoherence>=1){
           ledGreen();
           cout << "BEEP! High coherence reached" <<endl;
            s->highPercentage+=1;
       }

}

