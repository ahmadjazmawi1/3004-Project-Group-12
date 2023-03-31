#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    masterMenu = new Menu("MAIN MENU", {"SETTINGS","HISTORY"}, nullptr);
    activeQListWidget = ui->mainListWidget;
    activeQListWidget->addItems(masterMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);
    initMenus(masterMenu);
    ui->Graphwidget->setVisible(false);
    powerStatus=false;
    ui->screenDisplay->setStyleSheet("background-color: black");
    ui->mainListWidget->setVisible(powerStatus);
    ui->batteryLevel->setVisible(powerStatus);
    ui->mainMenu->setVisible(powerStatus);
    simTime = new QTimer(this);
    connect(ui->upButton, SIGNAL (released()), this, SLOT (upButton()));
    connect(ui->downButton, SIGNAL (released()), this, SLOT (downButton()));
    connect(ui->leftButton, SIGNAL (released()), this, SLOT (leftButton()));
    connect(ui->rightButton, SIGNAL (released()), this, SLOT (rightButton()));
    connect(ui->okButton, SIGNAL (released()), this, SLOT (okButton()));
    connect(ui->backButton, SIGNAL (released()), this, SLOT (backButton()));
    connect(ui->menuButton, SIGNAL (released()), this, SLOT (menuButton()));
    connect(ui->powerButton, SIGNAL (released()), this, SLOT (powerButton()));
    connect(ui->ChargeButton, SIGNAL (released()), this, SLOT (ChargeBattery()));
    if (powerStatus == true){

        connect(simTime, SIGNAL (timeout()), this, SLOT (useBattery()));
        simTime->start(10000);
    }


    QVector<double> x(65), y(65); // initialize with entries 0..100
    std::map<int, int> data = generateData();
    int i = 0;
    for(auto& p : data){
        x[i] = p.first;
        y[i] = p.second;
        i++;
    }


        // create graph and assign data to it:
    ui->Graphwidget->addGraph();
    ui->Graphwidget->graph(0)->setData(x, y);
        // give the axes some labels:
    ui->Graphwidget->xAxis->setLabel("Time(Seconds)");
    ui->Graphwidget->yAxis->setLabel("Heart Rate");
        // set axes ranges, so we see all data:
        ui->Graphwidget->xAxis->setRange(0, 65);
        ui->Graphwidget->yAxis->setRange(0, 100);
        ui->Graphwidget->replot();
}
void MainWindow::initMenus(Menu *m){

    QStringList historyList;
    this->settingList.append("CHALLENGE LEVEL");
    this->settingList.append("BREATH PACER SETTINGS");

    Menu* settings = new Menu("SETTINGS", this->settingList, m);
    m->addChildMenu(settings);
    settings->addChildMenu(new Menu("CHALLENGE LEVEL", {}, settings));
    settings->addChildMenu(new Menu("BREATH PACER SETTINGS", {}, settings));


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

    QString n = masterMenu->getName();

    //prevent crash if OK is pressed in challenge level
    if (masterMenu->getName() == "CHALLENGE LEVEL") {
        this->currChallenge = index;
        return;
    }
    else if(masterMenu->getName() == "BREATH PACER SETTINGS"){
        this->currPacer = index;
        return;
    }
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
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
}

void MainWindow::backButton(){
    qInfo("back button pressed");
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
        }else{
            powerStatus=false;
            ui->screenDisplay->setStyleSheet("background-color: black");
        }
        ui->batteryLevel->setVisible(powerStatus);
        ui->mainListWidget->setVisible(powerStatus);
        ui->mainMenu->setVisible(powerStatus);
}

std::map<int, int> MainWindow::generateData(){
    srand((unsigned) time(NULL));
      std::map<int, int> map;
      for(int i=1;i<65;++i){
        map[i] = 40 +(rand() % 61);
      }
      return map;
}
void MainWindow::ChargeBattery() {

    int batteryLevel = 100.0;
    BatLevel(batteryLevel);
}
void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems){
    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);
}
void MainWindow::useBattery() {

    double useOfLevel = BatteryLevel-0.10;

    BatLevel(useOfLevel);
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
