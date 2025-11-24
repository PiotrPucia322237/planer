#include <iostream>
#include <ctime>

int main(){
    // time_t - numeric representation of a given date and time
    time_t currDateTime; 
    time(&currDateTime); // get the current datetime, and save it to this memory
    // currDateTime = time(NULL); // also works but it's like using i++ in a for loop
    
    tm someDateTime;
    someDateTime.tm_hour = 21;
    someDateTime.tm_min = 37;
    someDateTime.tm_year = 2005 - 1900;
    someDateTime.tm_mon = 3;
    someDateTime.tm_mday = 2;
    // RIP John Paul II

    time_t sadBoyTime = mktime(&someDateTime);

    
    std::cout << sadBoyTime << " >> " << ctime(&sadBoyTime) << '\n';


    // Let's check how many years have passed since the date

    std::cout << currDateTime << " - " << sadBoyTime << " = ";
    time_t dateDiff = currDateTime - sadBoyTime;
    std::cout << dateDiff << '\n';
    std::cout << "Trying to get the year difference by division: " << dateDiff/60/60/24/365 << '\n';

    tm dateDiffStructure = *localtime(&dateDiff); // time_t -> tm
    const int outputArrSize = 50;
    char output[outputArrSize];
    std::cout << dateDiffStructure.tm_year << '\n'; // correct if you subtract 70


    std::cout << dateDiff << '\n' << difftime(currDateTime, sadBoyTime) << '\n';
    std::cout << dateDiff/60/60/24/365 << "\n" << difftime(currDateTime, sadBoyTime)/60/60/24/365 << '\n';



    return 0;
}