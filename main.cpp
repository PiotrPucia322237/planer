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
    if(0){
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
    }

    while(1){
        // show upcoming tasks
        std::cout << "Nadchodzace zadania:\n";
        time_t now;
        time(&now);
        int counter = 0;
        for(auto& task : tasks){
            if(!task.getIsCompleted() && task.getDueDate() >= now){
                time_t dueDate = task.getDueDate();
                tm datetimeTM = *localtime(&dueDate);
                std::cout << "* " << task.getName() << " - " 
                    << datetimeTM.tm_mday << '.' 
                    << (datetimeTM.tm_mon + 1) << '.' 
                    << (datetimeTM.tm_year + 1900) << " " 
                    << datetimeTM.tm_hour << ':' 
                    << datetimeTM.tm_min 
                    << "\n" << (task.workHoursLeft() < task.getExpectedTime()*1.2 ? "⚠️ " : "- ") << task.workHoursLeft() << " godz.\n";
                std::cout << "-------------------\n";
                if(++counter > 4)
                    break;
            }
        }

        // menu
        std::cout << "Wybierz opcje:\n1. Dodaj zadanie\n2. Wyswietl zadania\n3. Zmien status zadania\n4. Zmien ustawienia\n5. Zapisz i wyjdz\n";
        int choice;
        std::cin >> choice;
        if(choice == 1){
            std::string name;
            std::string description;
            std::string date;
            std::string time;
            time_t dueDate;
            double expectedTime;

            std::cout << "Podaj nazwe zadania: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Podaj opis zadania: ";
            std::getline(std::cin, description);
            std::cout << "Podaj termin wykonania (w formacie DD.MM.RRRR hh:mm): ";
            std::cin >> date >> time;
            std::tm dueDateTM = {};
            dueDateTM.tm_mday = std::stoi(date.substr(0,2));
            dueDateTM.tm_mon = std::stoi(date.substr(3,2)) - 1;
            dueDateTM.tm_year = std::stoi(date.substr(6,4)) - 1900;
            dueDateTM.tm_hour = std::stoi(time.substr(0,2));
            dueDateTM.tm_min = std::stoi(time.substr(3,2));
            dueDateTM.tm_sec = 0;
            dueDate = mktime(&dueDateTM);

            std::cout << "Podaj przewidywany czas wykonania (w godzinach): ";
            std::cin >> expectedTime;

            Task newTask(name, dueDate, expectedTime, description);
            tasks.push_back(newTask);
        }
        else if(choice == 2){
            std::cout << "Zadania: "<< '\n';
            for(auto& task : tasks){
                std::cout << task.getName() << '\n';
                std::cout << task.getDescription() << '\n';
                time_t dueDate = task.getDueDate();
                tm datetimeTM = *localtime(&dueDate);
                std::cout
                    << datetimeTM.tm_mday << '.' 
                    << (datetimeTM.tm_mon + 1) << '.' 
                    << (datetimeTM.tm_year + 1900) << " " 
                    << datetimeTM.tm_hour << ':' 
                    << datetimeTM.tm_min << '\n';
                std::cout << task.getExpectedTime() << " godz.\n";
                std::cout << "Status: " << (task.getIsCompleted() ? "ukonczone" : "nieukonczone") << "\n";
                std::cout << "-------------------\n";
            }
        }
        else if(choice == 3){
            std::cout << "Podaj nazwe zadania do zmiany statusu: ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            bool found = false;
            for(auto& task : tasks){
                if(task.getName() == name){
                    bool currentStatus = task.getIsCompleted();
                    task.setIsCompleted(!currentStatus);
                    std::cout << "Status zadania '" << name << "' zmieniony na " << (task.getIsCompleted() ? "ukonczone" : "nieukonczone") << ".\n";
                    found = true;
                    break;
                }
            }
            if(!found){
                std::cout << "Nie znaleziono zadania o nazwie '" << name << "'.\n";
            }
        }
        else if(choice == 4){
            Settings * settings = Settings::getInstance();
            int workHours;
            bool workWeekends;
            std::cout << "Podaj liczbe godzin pracy na dzien (0-24)(aktualnie " << settings->getWorkHours() << "): ";
            std::cin >> workHours;
            std::cout << "Czy pracujesz w weekendy? (1 - tak, 0 - nie)(aktualnie " << settings->getWorkWeekends() << "): ";
            std::cin >> workWeekends;
            settings->setSettings(workHours, workWeekends);
            Settings::saveSettings();
            std::cout << "Ustawienia zaktualizowane.\n";
        }
        else if(choice == 5){
            break;
        }
        else{
            std::cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
        }
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