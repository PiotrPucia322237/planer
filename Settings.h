#ifndef SETTINGS_H
#define SETTINGS_H
class Settings {
    private:
        static Settings * instance;
        Settings(); // private constructor to ensure a Singleton; uses fstream to read settings
        // IMPORTANT: follow this given order when saving the settings
        int workHours{};
        bool workWeekends{};
        
    public:
        ~Settings();
        static Settings * getInstance();
        static void saveSettings();

        int getWorkHours();
        bool getWorkWeekends();
        void setWorkHours(int hours);
        void setWorkWeekends(bool weekends);

        void setSettings(int, bool);

        

};
#endif