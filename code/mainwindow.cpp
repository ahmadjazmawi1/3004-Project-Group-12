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
    masterMenu = new Menu("MAIN MENU", {"START NEW SESSION","SETTINGS","HISTORY"}, nullptr);
    activeQListWidget = ui->mainListWidget;
    activeQListWidget->addItems(masterMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);

    this->graphTimer = new QTimer(this);
    this->dataTimer  = new QTimer(this);
    Session* s = new Session();
    sleep(5);
    Session* se = new Session();
    this->allSessions.append(s);
    cout<<allSessions.size();
    this->allSessions.append(se);
    //makeGraph();
    initMenus(masterMenu);
    ui->Graphwidget->setVisible(false);
    ui->coherenceLabel->setVisible(false);
    ui->lengthLabel->setVisible(false);
    ui->achievementLabel->setVisible(false);

    powerStatus=false;
    ui->screenDisplay->setStyleSheet("background-color: black");
    ui->mainListWidget->setVisible(powerStatus);
    ui->batteryLevel->setVisible(powerStatus);
    ui->mainMenu->setVisible(powerStatus);
    simTime = new QTimer(this);;

    connect(ui->upButton, SIGNAL (released()), this, SLOT (upButton()));
    connect(ui->downButton, SIGNAL (released()), this, SLOT (downButton()));
    connect(ui->leftButton, SIGNAL (released()), this, SLOT (leftButton()));
    connect(ui->rightButton, SIGNAL (released()), this, SLOT (rightButton()));
    connect(ui->okButton, SIGNAL (released()), this, SLOT (okButton()));
    connect(ui->backButton, SIGNAL (released()), this, SLOT (backButton()));
    connect(ui->menuButton, SIGNAL (released()), this, SLOT (menuButton()));
    connect(ui->powerButton, SIGNAL (released()), this, SLOT (powerButton()));
    connect(ui->chargeButton, SIGNAL (released()), this, SLOT (ChargeBattery()));
    BatteryLevel = 60;

}

void MainWindow::makeGraph(Session* s){
    QVector<double> x(100000), y(100000); // initialize with entries 0..100
    s->generateData();
    std::map<int, int> data = s->data;
    int i = 0;
    for(auto& p : data){
        x[i] = p.first;
        y[i] = p.second;
        cout<<"["<<x[i]<<", "<<y[i]<<"]"<<endl;
        i++;

    }



        // create graph and assign data to it:
    ui->Graphwidget->addGraph();
    ui->Graphwidget->graph(0)->setData(x, y);
    cout<<ui->Graphwidget->graph(0)->data();
        // give the axes some labels:
    ui->Graphwidget->xAxis->setLabel("Time(Seconds)");
    ui->Graphwidget->yAxis->setLabel("Heart Rate");
        // set axes ranges, so we see all data:
    ui->Graphwidget->xAxis->setRange(0, this->session->data.size());
    ui->Graphwidget->yAxis->setRange(0, 100);
    ui->Graphwidget->replot();

}

void MainWindow::newSess(Session* s){
    ui->Graphwidget->setVisible(true);
    ui->coherenceLabel->setVisible(true);
    QString co = "Coherence\n"+QString::asprintf("%0.2f", s->currCoherence);
    ui->coherenceLabel->setText(co);
    QString le = "Length\n"+QString::asprintf("%0.2f", s->getLength());
    ui->lengthLabel->setVisible(true);
    ui->lengthLabel->setText(le);

    ui->achievementLabel->setVisible(true);
    QString ach = "Achievement\n"+QString::asprintf("%0.2f", s->getAchievement());
    ui->achievementLabel->setText(ach);

    connect(this->graphTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    this->graphTimer->start(1000);
}

//only have this function because timeout signal doesnt take parameters, and this is the only way to get around that limitation
void MainWindow::handleTimeout(){
    makeGraph(this->session);
}
void MainWindow::showSummary(Session* s){
    this->graphTimer->stop();
    this->inSummary = true;
    ui->Graphwidget->clearGraphs();
    ui->Graphwidget->removeGraph(0);

    //ui->Graphwidget->graph(0)->data()->clear();
    //ui->Graphwidget->rep;
    //ui->Graphwidget->setVisible(true);

//    ui->Graphwidget->setVisible(true);
//    ui->coherenceLabel->setVisible(true);
//    QString co = "Coherence\n"+QString::asprintf("%0.2f", s->currCoherence);
//    ui->coherenceLabel->setText(co);
//    QString le = "Length\n"+QString::asprintf("%0.2f", s->getLength());
//    ui->lengthLabel->setVisible(true);
//    ui->lengthLabel->setText(le);

//    ui->achievementLabel->setVisible(true);
//    QString ach = "Achievement\n"+QString::asprintf("%0.2f", s->getAchievement());
//    ui->achievementLabel->setText(ach);

//    //connect(this->graphTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
//    //this->graphTimer->start(1000);
    makeGraph(this->session);
//    this->inSummary = true;

}

void MainWindow::initMenus(Menu *m){
    this->settingList.append("CHALLENGE LEVEL");
    this->settingList.append("BREATH PACER SETTINGS");

    Menu* settings = new Menu("SETTINGS", this->settingList, m);

    Menu* newSession = new Menu("START NEW SESSION", this->settingList, m);
    m->addChildMenu(newSession);
    m->addChildMenu(settings);
    settings->addChildMenu(new Menu("CHALLENGE LEVEL", {}, settings));
    settings->addChildMenu(new Menu("BREATH PACER SETTINGS", {}, settings));

    //***************SETTINGS**************
    for(int i=1;i<5;i++){
        this->challengeList.append(QString::number(i));
    }
    Menu* challengeLevel = new Menu("CHALLENGE LEVEL", this->challengeList, settings);
    settings->addChildMenu(challengeLevel);
    for(int i=1;i<5;i++){
        challengeLevel->addChildMenu(new Menu(QString::number(i), {}, challengeLevel));
    }


    for(int i=1;i<31;i++){
        this->breathPList.append(QString::number(i));
    }
    Menu* breathPacer = new Menu("BREATH PACER", this->breathPList, settings);
    settings->addChildMenu(breathPacer);
    for(int i=1;i<31;i++){
        breathPacer->addChildMenu((new Menu(QString::number(i), {}, breathPacer)));
    }


    //*******************HISTORY**********************
    QStringList historyList;
    //cout<<allSessions.size();
    for(int i=0;i<this->allSessions.size();i++){
        historyList.append(this->allSessions.at(i)->getTime().toString("h:mm:ss ap"));
        //cout<<this->allSessions[i]->getTime().toString("h:mm:ss ap").toStdString();
    }
    Menu* history = new Menu("HISTORY", historyList, m);
    m->addChildMenu(history);
    for(int i=0;i<this->allSessions.size();i++){
        //cout<<"IN LOOP"<<endl;
        history->addChildMenu(new Menu(this->allSessions.at(i)->getTime().toString("h:mm ap"), {}, history));
    }


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::upButton(){
    qInfo("Up button pressed");
    int nextIndex = activeQListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = activeQListWidget->count() - 1;
    }

    activeQListWidget->setCurrentRow(nextIndex);

}

void MainWindow::downButton(){
    qInfo("down button pressed");
    int nextIndex = activeQListWidget->currentRow() + 1;

    if (nextIndex > activeQListWidget->count() - 1) {
        nextIndex = 0;
    }

    activeQListWidget->setCurrentRow(nextIndex);

}

void MainWindow::leftButton(){
    qInfo("left button pressed");

}

void MainWindow::rightButton(){
    qInfo("right button pressed");

}

void MainWindow::okButton(){
    qInfo("ok button pressed");
    int index = activeQListWidget->currentRow();
    cout<<"INDEX: "<<index<<endl;
    if(this->isSession == true){
        cout<<"STOPPING THE SESSION"<<endl;
        //stop the session, i.e., save it to the database and show summary screen
        this->allSessions.append(this->session);
        isSession=false;
        MainWindow::updateMenu(this->session->getTime().toString(), {});
        ui->Graphwidget->clearGraphs();
        //ui->Graphwidget->setVisible(false);
        //ui->Graphwidget->setVisible(true);
        showSummary(this->session);
        return;
    }

    if (index < 0) return;
    QString n = masterMenu->getName();
    //cout<<"N: "<<n.toStdString()<<endl;
    //prevent crash if OK is pressed in challenge level
    if (masterMenu->getName() == "CHALLENGE LEVEL") {
        this->currChallenge = index;
        return;
    }
    else if(index==0 && masterMenu->getName() == "MAIN MENU"){
        activeQListWidget->setCurrentRow(0);
        cout<<"LETS GOOOOOOOOOOOOO"<<endl;
        this->session = new Session();
        MainWindow::updateMenu(this->session->getTime().toString(), {});
        newSess(this->session);
        this->isSession = true;
        return;
    }
    else if(this->isSession == true){
        cout<<"STOPPING THE SESSION"<<endl;
        //stop the session, i.e., save it to the database and show summary screen
        this->allSessions.append(this->session);
        isSession=false;
        MainWindow::updateMenu(allSessions.at(index)->getTime().toString(), {});
        showSummary(allSessions.at(index));
        return;
    }
    else if(masterMenu->getName() == "HISTORY"){
        masterMenu = masterMenu->get(index);
        this->session = allSessions.at(index);
        MainWindow::updateMenu(allSessions.at(index)->getTime().toString(), {});
        this->isSession = true;
        showSummary(allSessions.at(index));
        return;
    }

    else if(masterMenu->getName() == "BREATH PACER SETTINGS"){
        this->currPacer = index;
        return;
    }
    //cout<<"INDEX: "<<index<<endl;
//    else if(masterMenu->getName() == allSessions.at(index)->getTime().toString()){
//        return;
//    }


    else if(masterMenu->get(index)->getName() == "CHALLENGE LEVEL"){
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu("CHALLENGE LEVEL", this->challengeList);
    }

    else if(masterMenu->get(index)->getName() =="BREATH PACER SETTINGS"){
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu("BREATH PACER SETTINGS", this->breathPList);
    }
    //if menu is a parent and clicking on it should display more menus
    else if (masterMenu->get(index)->getMenuItems().length() > 0) {
        cout<<"index before: "<<index<<endl;
        cout<<"BEFORE: "<<masterMenu->getName().toStdString()<<endl;;
        for(int i=0;i<3;i++){
            cout<<masterMenu->get(i)->getName().toStdString();
        }
        masterMenu = masterMenu->get(index);

        cout<<"AFTER: "<<masterMenu->getName().toStdString()<<endl;
        MainWindow::updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
}

void MainWindow::backButton(){
    qInfo("back button pressed");
    cout<<this->inSummary<<endl;
    if(this->inSummary==true){
        cout<<masterMenu->getName().toStdString();
        ui->Graphwidget->setVisible(false);
        ui->coherenceLabel->setVisible(false);
        ui->lengthLabel->setVisible(false);
        ui->achievementLabel->setVisible(false);
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
    if (masterMenu->getName() == "MAIN MENU") {
        activeQListWidget->setCurrentRow(0);
    }
    else {
        masterMenu = masterMenu->getParent();
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }


}

void MainWindow::menuButton(){
    qInfo("menu button pressed");

}

void MainWindow::powerButton(){
    qInfo("power button pressed");

        if(powerStatus==false){
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
