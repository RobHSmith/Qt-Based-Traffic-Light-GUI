#include <fstream>
#include <sstream>
#include "TrafficLight.h"

TrafficLight::TrafficLight(QWidget *parent,int i) : QWidget(parent){

    timing = read_ini("D:/Graduate/Code Development/Combined_UI_v3/timing.ini"); //If using Rob Smith's laptop

    //trafic light number settings
    lnum = timing.at(0).second.at(i);

    //time settings
    rlight = timing.at(3).second.at(i); //set the total cycle time for the light (s)
    glight = timing.at(1).second.at(i); //set the end of the green phase (s)
    ylight = timing.at(2).second.at(i); //set the end of the yellow phase (s)

    //position settings
    dist = timing.at(4).second.at(i); //set the position of the traffic light (m)
    startdist = timing.at(4).second.at(i); //set "reset" position of traffic light (m)
}

TrafficLight::~TrafficLight(){

}

std::vector<std::pair<std::string, std::vector<double>>> TrafficLight::read_ini(std::string filename){
    //Create storage
    std::vector<std::pair<std::string, std::vector<double>>> result;

    //Link file
    std::ifstream timing(filename);

    //Ensure file is open
    if(!timing.is_open()){throw std::runtime_error("Couldn't find file");}

    //Placeholders
    std::string line;
    std::string colname;
    int val;

    //Read column names
    if(timing.good()){
        //Extract first line
        std::getline(timing,line);

        //Break up first line into column names
        std::stringstream ss(line);
        while(std::getline(ss,colname,',')){
            result.push_back({colname,std::vector<double>{}});
        }
    }
    else{
        throw std::runtime_error("Improperly formatted data");
    }

    //Extract data
    while(std::getline(timing,line)){
        std::stringstream ss(line);
        int col = 0;
        while(ss >> val){
            //add data to output vector
            result.at(col).second.push_back(val);

            //ignore commas
            if(ss.peek() == ','){
                ss.ignore();
            }

            //Increment column index
            col++;
        }
    }

    //close file
    timing.close();
    return result;
}
