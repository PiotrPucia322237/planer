#include "Task.h"
#include "Settings.h"
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[]){
    Settings::getInstance(); // ensure instance is created

    std::vector<Task> tasks{};

    if(argc > 1){
        std::string tasksFileName;
        tasksFileName = argv[1];
        std::fstream tasksFile(tasksFileName, std::ios::in);
        if(tasksFile.good()){
            std::string name;
            
            while(std::getline(tasksFile, name)){
                std::string description;
                time_t dueDate;
                double expectedTime;
                bool isCompleted;

                std::getline(tasksFile, description);
                tasksFile >> dueDate;
                tasksFile >> expectedTime;
                tasksFile >> isCompleted;
                std::getline(tasksFile, description); // flush newline after reading isCompleted

                Task newTask(name, dueDate, expectedTime, description, isCompleted);
                tasks.push_back(newTask);
            }
            tasksFile.close();
        }
    }

    time_t now;
    time(&now);

    tm dueDateTm = *localtime(&now);
    ++dueDateTm.tm_mday;
    time_t dueDate = mktime(&dueDateTm);
    Task myTask("Task 1", dueDate, 5.5, "Task 1 description.");
    tasks.push_back(myTask);

    dueDateTm.tm_mday = 18;
    dueDateTm.tm_mon = 2;
    dueDateTm.tm_hour = 4;
    dueDateTm.tm_min = 30;
    dueDateTm.tm_sec = 0;
    time_t anotherDueDate = mktime(&dueDateTm);
    Task anotherTask("Task 2", anotherDueDate, 0.01, "Task 2 description.");

    std::cout << "Work hours left until 18.03 4:30:00: " << anotherTask.workHoursLeft() << '\n';
    tasks.push_back(anotherTask);
    
    std::cout << "Tasks: "<< '\n';
    for(auto& task : tasks){
        std::cout << "- " << task.getName() << '\n';
    }

    if(argc > 1){
        std::string tasksFileName;
        tasksFileName = argv[1];
        std::fstream tasksFile(tasksFileName, std::ios::out);
        if(tasksFile.good()){
            for(auto& task : tasks){
                tasksFile << task.getName() << '\n';
                tasksFile << task.getDescription() << '\n';
                tasksFile << task.getDueDate() << '\n';
                tasksFile << task.getExpectedTime() << '\n';
                tasksFile << task.getIsCompleted() << '\n';
            }
            tasksFile.close();
        }
    }




    return 0;
}