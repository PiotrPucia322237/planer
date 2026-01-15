#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <ctime>
class Task{
    private: 
        std::string name;
        std::string description;
        time_t dueDate;
        double expectedTime;
        bool isCompleted = 0;

    public:
        Task(std::string, time_t, double, std::string = "", bool = 0);
        ~Task();

        std::string getName();
        std::string getDescription();
        time_t getDueDate();
        double getExpectedTime();
        bool getIsCompleted();
        
        void setName(std::string);
        void setDescription(std::string);
        void setDueDate(time_t);
        void setExpectedTime(double);
        void setIsCompleted(bool);

        void printTask();
        double workHoursLeft();
};
#endif