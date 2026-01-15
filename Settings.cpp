#include "Settings.h"
#include <fstream>
Settings * Settings::instance = nullptr;

Settings::Settings(){
    std::fstream file("settings.babam", std::ios::in);
    if (!file.good()) { // if there's no file
        file.close();
        file.open("settings.babam", std::ios::out); // fill the file with default settings
        file << "8\n"; // default workHours
        file << "0\n"; // default workWeekends
        file.close();
        file.open("settings.babam", std::ios::in);
    }
    int _workHours;
    bool _workWeekends;
    file >> _workHours;
    file >> _workWeekends;
    file.close();
    workHours = _workHours;
    workWeekends = _workWeekends;
}
Settings::~Settings(){}

int Settings::getWorkHours(){
    return workHours;
}
bool Settings::getWorkWeekends(){
    return workWeekends;
}

void Settings::setWorkHours(int hours){
    workHours = hours;
}
void Settings::setWorkWeekends(bool weekends){
    workWeekends = weekends;
}

void Settings::setSettings(int hours, bool weekends){
    workHours = hours;
    workWeekends = weekends;
}

Settings * Settings::getInstance(){
    if(instance == nullptr){
        instance = new Settings();
    }
    return instance;
}

void Settings::saveSettings(){
    Settings::getInstance(); // ensure instance is created
    std::fstream file("settings.babam", std::ios::out);
    if(file.good()){
        file << instance->workHours << '\n';
        file << instance->workWeekends << '\n';
        file.close();
    }
}
