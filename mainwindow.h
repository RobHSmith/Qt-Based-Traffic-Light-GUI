#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <vector>

#include "TrafficLight.h"
#include "D:\Graduate\Code Development\build-Combined_UI_v5-Desktop_Qt_6_1_2_MinGW_64_bit-Debug\ui_mainwindow.h" //If using Rob Smith's laptop

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    std::vector<std::shared_ptr<TrafficLight>> p_shared;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<QTime> time{6}; //seconds
    const int startdist = 50; //must be in <distance_unit>, constant - used for resetting "dist"
    int dist = 50; //must be in <distance_unit>, decreases as car approaches intersection
    int speed = 5; //must be in <distance_unit>/s

    void updateCountdown();

    void updateDistance();

    void fontsize(QLabel *sellabel, int size);

    int updatePhase();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
