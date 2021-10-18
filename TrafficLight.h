#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QWidget>

class TrafficLight : public QWidget{

public:

    TrafficLight(QWidget *parent = nullptr,int i = 0);
    ~TrafficLight();

    std::vector<std::pair<std::string, std::vector<double>>> read_ini(std::string filename);

    std::vector<std::pair<std::string, std::vector<double>>> timing;

    int glight = 6000;
    int ylight = 2000;
    int rlight = 5000;

    int lnum = 0;
    int dist = 50; //m
    int speed = 5; //m/s


};

#endif //TRAFFICLIGHT_H
