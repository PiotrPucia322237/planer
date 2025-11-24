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
        Task(std::string, time_t, double, std::string = "");
        ~Task();

        std::string getName();
        std::string getDescription();
        time_t getDueDate();
        double getExpectedTime();
        bool getIsCompleted();
        
        void setName(std::string name);
        void setDescription(std::string description);
        void setDueDate(time_t dueDate);
        void setExpectedTime(double expectedTime);
        void setIsCompleted(bool isCompleted);

        void printTask();
        double workHoursLeft();
};
#endif