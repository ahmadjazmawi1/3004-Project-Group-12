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
