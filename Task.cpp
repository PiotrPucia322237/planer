#include "Task.h"
#include "Settings.h"
Task::Task(std::string _name, time_t _dueDate, double _expectedTime, std::string _description){
    name = _name;
    dueDate = _dueDate;
    expectedTime = _expectedTime;
    description = _description;
}
Task::~Task(){}

std::string Task::getName(){
    return name;
}
std::string Task::getDescription(){
    return description;
}
time_t Task::getDueDate(){
    return dueDate;
}
double Task::getExpectedTime(){
    return expectedTime;
}
bool Task::getIsCompleted(){
    return isCompleted;
}

void Task::setName(std::string _name){
    name = _name;
}
void Task::setDescription(std::string _description){
    description = _description;
}
void Task::setDueDate(time_t _dueDate){
    dueDate = _dueDate;
}
void Task::setExpectedTime(double _expectedTime){
    expectedTime = _expectedTime;
}
void Task::setIsCompleted(bool _isCompleted){
    isCompleted = _isCompleted;
}

// FUNctions :)

void Task::printTask(){
    std::clog << "{\n";
    std::clog << "T:  " << name << '\n';
    std::clog << "Dc: " << description << '\n';
    std::clog << "Dd: " << ctime(&dueDate);
    std::clog << "Et: " << expectedTime << '\n';
    std::clog << "C:  " << isCompleted << '\n';
    std::clog << "Hl: " << workHoursLeft() << '\n';
    std::clog << "}\n";

}

double Task::workHoursLeft(){
    double whl;
    time_t now;
    time(&now);

    Settings * settings = Settings::getInstance();
    double hl = difftime(dueDate, now)/3600.0;
    int weeksLeft = hl / 24 / 7;

    whl = weeksLeft * (settings->getWorkHours() * (settings->getWorkWeekends() ? 7 : 5));
    hl = hl - weeksLeft*24*7;

    int daysLeft = hl / 24;
    
    time_t temp = now + 60*60*24;
    tm helperDate = *localtime(&temp);
    tm dueDateTM = *localtime(&dueDate);
    helperDate.tm_hour = dueDateTM.tm_hour;
    helperDate.tm_min = dueDateTM.tm_min;
    helperDate.tm_sec = dueDateTM.tm_sec;
    
    while(difftime(mktime(&helperDate), now) < daysLeft*60*60*24){
        if(settings->getWorkWeekends() || (helperDate.tm_wday > 0 && helperDate.tm_wday < 6)){
            whl += settings->getWorkHours();
        }
        temp = mktime(&helperDate) + 60*60*24;
        helperDate = *localtime(&temp);
    }

    if(settings->getWorkWeekends() || (helperDate.tm_wday > 0 && helperDate.tm_wday < 6)){
        double hoursLeftOnLastDay = helperDate.tm_hour + helperDate.tm_min/60.0 + helperDate.tm_sec/60.0/60;
        whl += hoursLeftOnLastDay > 8 ? 8 : hoursLeftOnLastDay; 
    }

    tm nowTM = *localtime(&temp);
    if(settings->getWorkWeekends() || (nowTM.tm_wday > 0 && nowTM.tm_wday < 6)){
        double hoursLeftToday = (23 - nowTM.tm_hour) + (59-nowTM.tm_min)/60.0 + (59-nowTM.tm_sec)/60.0/60;
        whl += hoursLeftToday > 8 ? 8 : hoursLeftToday; 
    }

    return whl;
}