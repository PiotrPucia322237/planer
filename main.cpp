#include "Task.h"
#include "Settings.h"
#include <fstream>

int main(){

    Settings::saveSettings();

    time_t now;
    time(&now);

    tm dueDateTm = *localtime(&now);
    ++dueDateTm.tm_mday;
    time_t dueDate = mktime(&dueDateTm);
    Task myTask("Project progress", dueDate, 5.5, "Prepare anything for the next LAB");

    dueDateTm.tm_mday = 2;
    dueDateTm.tm_mon = 11;
    dueDateTm.tm_hour = 4;
    dueDateTm.tm_min = 30;
    dueDateTm.tm_sec = 0;
    time_t anotherDueDate = mktime(&dueDateTm);
    Task anotherTask("What", anotherDueDate, 0.01, "ever");

    std::cout << "Work hours left until 02.12 4:30:00: " << anotherTask.workHoursLeft() << '\n';



    return 0;
}