#pragma once

#include "Menu.h"
#include "Participant.h"


enum class APP_STATE
{
    NONE = 0,

    LOG_IN = 1,
    LOGGED_IN = 2,
    MENU = 3,

    END = 4
};

class App
{

public:

    void start();
    void update();
    void finish();

    bool isActive();

private:

    APP_STATE m_state;

    map<APP_STATE, vector<string>>m_commands;

    vector<string> m_syobshteniqDoMinkov;
    
    map<string, Participant> m_participants;    // name to participant object

    Menu m_menu;    // contains catalogue

    string m_adminPass;

    string m_cin;
    time_t m_time;
    string m_currentAccount;

    bool m_isActive;

    void logIn();
    void loggedIn();
    void menu();

    void initCommands();
    void initAdminPassword();
    void initMenu();
    void initParticipants();


    void writeInFile(string path, vector<string>& content);

    void printAFile(string path);
    void readAFile(vector<string>& output, string path);
    void printCommands();

#pragma region LOG_IN COMMANDS
    void ASDM();
    void printAboutMyApp();
    void printBriefTutorial();
    void registerParticipant();
    void logIntoAccount();
    void forgotPassword();
    void printMSGS();
    void exit();
#pragma endregion

#pragma region LOGGED_IN COMMANDS

    void PSDM();
    void changeName();
    void changePassword();
    void applyForAdmin();
    void getPersonalInfo();
    void getAllParticipantsPublicInfoByName();
    void getAllParticipantsPublicInfoByBalance();
    void searchForParticipant();
    void goToMenu();
    void logOut();

#pragma endregion


    bool isNumber(string checkable);
};
