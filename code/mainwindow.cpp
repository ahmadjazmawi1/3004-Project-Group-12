#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->upButton, SIGNAL (released()), this, SLOT (upButton()));
    connect(ui->downButton, SIGNAL (released()), this, SLOT (downButton()));
    connect(ui->leftButton, SIGNAL (released()), this, SLOT (leftButton()));
    connect(ui->rightButton, SIGNAL (released()), this, SLOT (rightButton()));
    connect(ui->okButton, SIGNAL (released()), this, SLOT (okButton()));
    connect(ui->backButton, SIGNAL (released()), this, SLOT (backButton()));
    connect(ui->menuButton, SIGNAL (released()), this, SLOT (menuButton()));
    connect(ui->powerButton, SIGNAL (released()), this, SLOT (powerButton()));

    // generate some data:
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




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::upButton(){
    qInfo("Up button pressed");

}

void MainWindow::downButton(){
    qInfo("down button pressed");

}

void MainWindow::leftButton(){
    qInfo("left button pressed");

}

void MainWindow::rightButton(){
    qInfo("right button pressed");

}

void MainWindow::okButton(){
    qInfo("ok button pressed");

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

