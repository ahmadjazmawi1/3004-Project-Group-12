#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::map<int, int> generateData();



private:
    Ui::MainWindow *ui;

private slots:
    void upButton();
    void downButton();
    void leftButton();
    void rightButton();
    void okButton();
    void backButton();
    void menuButton();
    void powerButton();
};
#endif // MAINWINDOW_H
