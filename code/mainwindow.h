#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "menu.h"
#include <QMainWindow>
#include <QListWidget>
#include <QTimer>
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




private:
    Ui::MainWindow *ui;
    Menu* masterMenu;
    Menu* mainMenu;
    QListWidget *activeQListWidget;
    QStringList breathPList;
    QStringList settingList;
    QStringList challengeList;
    int currChallenge=1;
    int currPacer=1;
    bool powerStatus;
    int BatteryLevel;
    QTimer *simTime;






private slots:
    void upButton();
    void downButton();
    void leftButton();
    void rightButton();
    void okButton();
    void backButton();
    void menuButton();
    void powerButton();
    void ChargeBattery();
    void useBattery();
};
#endif // MAINWINDOW_H
