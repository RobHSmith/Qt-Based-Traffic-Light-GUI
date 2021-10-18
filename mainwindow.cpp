#include <QTimer>
#include <iostream>
#include "mainwindow.h"
#include "D:\Graduate\Code Development\build-Combined_UI_v6-Desktop_Qt_6_1_2_MinGW_64_bit-Debug\ui_mainwindow.h"

#define NUMTLIGHT 6 //number of traffic lights
#define SENSVIEW 200 //distance sensor can see (m)

std::vector<int> ptime = {5,6,8,4,4,8}; //global initialization for phase timing - updateCountdown cannot accept inputs, so this is needed

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Formatting
    int countfont = 30;
    int labelfont = 20;
    int titlefont = 25;

    MainWindow::fontsize(ui->countdown,countfont);
    MainWindow::fontsize(ui->countdown_2,countfont);
    MainWindow::fontsize(ui->countdown_3,countfont);
    MainWindow::fontsize(ui->countdown_4,countfont);
    MainWindow::fontsize(ui->countdown_5,countfont);
    MainWindow::fontsize(ui->countdown_6,countfont);

    MainWindow::fontsize(ui->label_1_1,labelfont);
    MainWindow::fontsize(ui->label_1_2,labelfont);
    MainWindow::fontsize(ui->label_2_1,labelfont);
    MainWindow::fontsize(ui->label_2_2,labelfont);
    MainWindow::fontsize(ui->label_3_1,labelfont);
    MainWindow::fontsize(ui->label_3_2,labelfont);
    MainWindow::fontsize(ui->label_4_1,labelfont);
    MainWindow::fontsize(ui->label_4_2,labelfont);
    MainWindow::fontsize(ui->label_5_1,labelfont);
    MainWindow::fontsize(ui->label_5_2,labelfont);
    MainWindow::fontsize(ui->label_6_1,labelfont);
    MainWindow::fontsize(ui->label_6_2,labelfont);

    MainWindow::fontsize(ui->d2light,countfont);
    MainWindow::fontsize(ui->d2light_2,countfont);
    MainWindow::fontsize(ui->d2light_3,countfont);
    MainWindow::fontsize(ui->d2light_4,countfont);
    MainWindow::fontsize(ui->d2light_5,countfont);
    MainWindow::fontsize(ui->d2light_6,countfont);

    MainWindow::fontsize(ui->title1,titlefont);
    MainWindow::fontsize(ui->title2,titlefont);
    MainWindow::fontsize(ui->title3,titlefont);
    MainWindow::fontsize(ui->title4,titlefont);
    MainWindow::fontsize(ui->title5,titlefont);
    MainWindow::fontsize(ui->title6,titlefont);

    //declare number of traffic lights in scope
    int num = NUMTLIGHT;

    //initialize vector of pointers
    for(int m = 0;m < num;m++){
        p_shared.push_back(nullptr);
    }

    for(int i = 0;i < num;i++){
        //Connect Pointer to TrafficLight
        p_shared[i] = std::make_shared<TrafficLight>(nullptr,i);

        //Initialize Time
        time[i].setHMS(0,0,1);
    }

    //Only works if tl_widgets set to TrafficLight class - no solution for only extracting tl_widgets
    //QList<QFrame*> complist1 = ui->centralwidget->findChildren<QFrame*>(QString(),Qt::FindDirectChildrenOnly);

    //QList<QWidget*> complist2 = ui->centralwidget->findChildren<QWidget*>(QString(),Qt::FindDirectChildrenOnly);

    //QVector<QFrame*> compvec1 = complist1.toVector();
    //QVector<QWidget*> compvec2 = complist2.toVector();

    //Initialize countdown displays
    ui->countdown->setText(time[0].toString("m:ss"));
    ui->countdown_2->setText(time[1].toString("m:ss"));
    ui->countdown_3->setText(time[2].toString("m:ss"));
    ui->countdown_4->setText(time[3].toString("m:ss"));
    ui->countdown_5->setText(time[4].toString("m:ss"));
    ui->countdown_6->setText(time[5].toString("m:ss"));

    //Initialize distance countdown displays
    ui->d2light->setNum(p_shared[0]->dist);
    ui->d2light_2->setNum(p_shared[1]->dist);
    ui->d2light_3->setNum(p_shared[2]->dist);
    ui->d2light_4->setNum(p_shared[3]->dist);
    ui->d2light_5->setNum(p_shared[4]->dist);
    ui->d2light_6->setNum(p_shared[5]->dist);

    //Connect Phase Timers
    QTimer *ctimer = new QTimer(this);
    connect(ctimer,&QTimer::timeout,this,&MainWindow::updateCountdown);
    ctimer -> start(1000);

    //Connect Distance Timers
    QTimer *dtimer = new QTimer(this);
    connect(dtimer,&QTimer::timeout,this,&MainWindow::updateDistance);
    dtimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//function to update displayed time until traffic light phase change
void MainWindow::updateCountdown(){
    //declare number of lights in scope
    unsigned long long num = NUMTLIGHT;

    //declare sensor view distance in scope
    int sensview = SENSVIEW;

    //create vector "num" long to hold strings to be displayed
    std::vector<QString> tstr{num};

    //update time and corresponding string
    for(unsigned long long j = 0;j < num;j++){
        time[j] = time[j].addSecs(-1);
        tstr[j] = time[j].toString("m:ss");
    }

    //set display to reflect remaining phase time and remove countdown if distance is 0 or beyond sensor range
    if(p_shared[0]->dist != 0 && p_shared[0]->dist < sensview){
        ui->countdown->setText(tstr[0]);
    }else{
        ui->countdown->setText(nullptr);
    }
    if(p_shared[1]->dist != 0 && p_shared[1]->dist < sensview){
        ui->countdown_2->setText(tstr[1]);
    }else{
        ui->countdown_2->setText(nullptr);
    }
    if(p_shared[2]->dist != 0 && p_shared[2]->dist < sensview){
        ui->countdown_3->setText(tstr[2]);
    }else{
        ui->countdown_3->setText(nullptr);
    }
    if(p_shared[3]->dist != 0 && p_shared[3]->dist < sensview){
        ui->countdown_4->setText(tstr[3]);
    }else{
        ui->countdown_4->setText(nullptr);
    }
    if(p_shared[4]->dist != 0 && p_shared[4]->dist < sensview){
        ui->countdown_5->setText(tstr[4]);
    }else{
        ui->countdown_5->setText(nullptr);
    }
    if(p_shared[5]->dist != 0 && p_shared[5]->dist < sensview){
        ui->countdown_6->setText(tstr[5]);
    }else if(p_shared[5]->dist == 0){
        close();
    }else{
        ui->countdown_6->setText(nullptr);
    }

    //switch to next phase
    for(unsigned long long k = 0;k < num;k++){
        if(tstr[k] == "0:00"){
            //update timings
            p_shared[k]->timing = p_shared[k]->read_ini("D:/Graduate/Code Development/Combined_UI_v3/timing.ini");
            p_shared[k]->rlight = p_shared[k]->timing.at(3).second.at(k); //set the total cycle time for the light (s)
            p_shared[k]->glight = p_shared[k]->timing.at(1).second.at(k); //set the end of the green phase (s)
            p_shared[k]->ylight = p_shared[k]->timing.at(2).second.at(k); //set the end of the yellow phase (s)

            //switch color of tl_widget
            if(!p_shared[k]){
                std::cerr << "ASSIGN POINTER\n";
            }else if(ptime[k] == p_shared[k]->glight){ //green light time
                ptime[k] = p_shared[k]->ylight;
                switch(k){
                    case 0:
                        ui->tl_widget->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 1:
                        ui->tl_widget_2->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 2:
                        ui->tl_widget_3->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 3:
                        ui->tl_widget_4->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 4:
                        ui->tl_widget_5->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 5:
                        ui->tl_widget_6->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(255, 255, 255)");
                    break;
                }
            }else if(ptime[k] == p_shared[k]->ylight){ //yellow light time
                ptime[k] = p_shared[k]->rlight;
                switch(k){
                    case 0:
                        ui->tl_widget->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255)");
                    break;
                    case 1:
                        ui->tl_widget_2->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255)");
                    break;
                    case 2:
                        ui->tl_widget_3->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255)");
                    break;
                    case 3:
                        ui->tl_widget_4->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255)");
                    break;
                    case 4:
                        ui->tl_widget_5->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255)");
                    break;
                    case 5:
                        ui->tl_widget_6->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255)");
                    break;
                }
            }else if(ptime[k] == p_shared[k]->rlight){ //red light time
                ptime[k] = p_shared[k]->glight;
                switch(k){
                    case 0:
                        ui->tl_widget->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 1:
                        ui->tl_widget_2->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 2:
                        ui->tl_widget_3->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 3:
                        ui->tl_widget_4->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 4:
                        ui->tl_widget_5->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(255, 255, 255)");
                    break;
                    case 5:
                        ui->tl_widget_6->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(255, 255, 255)");
                    break;
                }
            }else{
                std::cerr << "BROKEN SYSTEM\n";
            }

            //reset timer to next phase's timing
            time[k].setHMS(0,0,ptime[k]);
        }
    }
}

//function to update displayed distance btw ego vehicle and intersection
void MainWindow::updateDistance(){
    //declare number of lights w/in scope
    int num = NUMTLIGHT;

    //declare sensor view w/in scope
    int sensview = SENSVIEW;

    //calculate distance left from vehicle to light based on speed (TO BE REMOVED WHEN POSSIBLE)
    for(int m = 0;m < num;m++){
        if(p_shared[m]->dist != 0){
            p_shared[m]->dist = p_shared[m]->dist - p_shared[m]->speed;
        }else{
            //if distance goes to 0, keep it there
            p_shared[m]->dist = 0;
        }
    }

    //import distance left from vehicle to light


    //set display to reflect remaining difference make blocks transparent if associated distance is 0 or beyond sensor range
    if(p_shared[0]->dist != 0 && p_shared[0]->dist < sensview){
        ui->d2light->setNum(p_shared[0]->dist);
        ui->title1->setText("Traffic Light 1");
        ui->label_1_1->setText("Time to Phase Change");
        ui->label_1_2->setText("Distance to Light");
        ui->tl_widget->show();
    }else{
        ui->title1->setText(nullptr);
        ui->d2light->setText(nullptr);
        ui->label_1_1->setText(nullptr);
        ui->label_1_2->setText(nullptr);
        ui->tl_widget->hide();
    }
    if(p_shared[1]->dist != 0 && p_shared[1]->dist < sensview){
        ui->d2light_2->setNum(p_shared[1]->dist);
        ui->title2->setText("Traffic Light 2");
        ui->label_2_1->setText("Time to Phase Change");
        ui->label_2_2->setText("Distance to Light");
        ui->tl_widget_2->show();
    }else{
        ui->title2->setText(nullptr);
        ui->d2light_2->setText(nullptr);
        ui->label_2_1->setText(nullptr);
        ui->label_2_2->setText(nullptr);
        ui->tl_widget_2->hide();
    }
    if(p_shared[2]->dist != 0 && p_shared[2]->dist < sensview){
        ui->d2light_3->setNum(p_shared[2]->dist);
        ui->title3->setText("Traffic Light 3");
        ui->label_3_1->setText("Time to Phase Change");
        ui->label_3_2->setText("Distance to Light");
        ui->tl_widget_3->show();
    }else{
        ui->title3->setText(nullptr);
        ui->d2light_3->setText(nullptr);
        ui->label_3_1->setText(nullptr);
        ui->label_3_2->setText(nullptr);
        ui->tl_widget_3->hide();
    }
    if(p_shared[3]->dist != 0 && p_shared[3]->dist < sensview){
        ui->d2light_4->setNum(p_shared[3]->dist);
        ui->title4->setText("Traffic Light 4");
        ui->label_4_1->setText("Time to Phase Change");
        ui->label_4_2->setText("Distance to Light");
        ui->tl_widget_4->show();
    }else{
        ui->title4->setText(nullptr);
        ui->d2light_4->setText(nullptr);
        ui->label_4_1->setText(nullptr);
        ui->label_4_2->setText(nullptr);
        ui->tl_widget_4->hide();
    }
    if(p_shared[4]->dist != 0 && p_shared[4]->dist < sensview){
        ui->d2light_5->setNum(p_shared[4]->dist);
        ui->title5->setText("Traffic Light 5");
        ui->label_5_1->setText("Time to Phase Change");
        ui->label_5_2->setText("Distance to Light");
        ui->tl_widget_5->show();
    }else{
        ui->title5->setText(nullptr);
        ui->d2light_5->setText(nullptr);
        ui->label_5_1->setText(nullptr);
        ui->label_5_2->setText(nullptr);
        ui->tl_widget_5->hide();
    }
    if(p_shared[5]->dist != 0 && p_shared[5]->dist < sensview){
        ui->d2light_6->setNum(p_shared[5]->dist);
        ui->title6->setText("Traffic Light 6");
        ui->label_6_1->setText("Time to Phase Change");
        ui->label_6_2->setText("Distance to Light");
        ui->tl_widget_6->show();
    }else{
        ui->title6->setText(nullptr);
        ui->d2light_6->setText(nullptr);
        ui->label_6_1->setText(nullptr);
        ui->label_6_2->setText(nullptr);
        ui->tl_widget_6->hide();
    }
}

//function to change the font size of a label widget on the UI
void MainWindow::fontsize(QLabel *sellabel, int size){
    QFont fontholder = sellabel->font();
    fontholder.setPointSize(size);
    sellabel->setFont(fontholder);
}
