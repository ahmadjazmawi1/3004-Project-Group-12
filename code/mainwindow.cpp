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

    connect(ui->upButton, SIGNAL (released()), this, SLOT (upButton()));
    connect(ui->downButton, SIGNAL (released()), this, SLOT (downButton()));
    connect(ui->leftButton, SIGNAL (released()), this, SLOT (leftButton()));
    connect(ui->rightButton, SIGNAL (released()), this, SLOT (rightButton()));
    connect(ui->okButton, SIGNAL (released()), this, SLOT (okButton()));
    connect(ui->backButton, SIGNAL (released()), this, SLOT (backButton()));
    connect(ui->menuButton, SIGNAL (released()), this, SLOT (menuButton()));
    connect(ui->powerButton, SIGNAL (released()), this, SLOT (powerButton()));

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


    //if menu is a parent and clicking on it should display more menus
    if (masterMenu->get(index)->getMenuItems().length() > 0) {
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
        cout<<"HAHAHAHA"<<endl;

    }

    else if(masterMenu->get(index)->getName() =="CHALLENGE LEVEL"){
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu("CHALLENGE LEVEL", this->challengeList);
    }

    else if(masterMenu->get(index)->getName() =="BREATH PACER SETTINGS"){
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu("BREATH PACER SETTINGS", this->breathPList);
    }





}

void MainWindow::backButton(){
    qInfo("back button pressed");

}

void MainWindow::menuButton(){
    qInfo("menu button pressed");

}

void MainWindow::powerButton(){
    qInfo("power button pressed");

}

std::map<int, int> MainWindow::generateData(){
    srand((unsigned) time(NULL));
      std::map<int, int> map;
      for(int i=1;i<65;++i){
        map[i] = 40 +(rand() % 61);
      }
      return map;
}

void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems){
    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);
}
