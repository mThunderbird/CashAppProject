#include "App.h"

#include <filesystem>

namespace fs = std::filesystem;

void App::start()
{
    m_state = APP_STATE::LOG_IN;
    m_isActive = true;
    initCommands();
    initParticipants();
    initAdminPassword();
    readAFile(m_syobshteniqDoMinkov, DATA_FOLDER + "suobshteniqDoMinkov.txt");

    printAFile(DATA_FOLDER + "intro.txt");
}

void App::update()
{
    switch (m_state)
    {
    case APP_STATE::LOG_IN:
        logIn();
        break;
    case APP_STATE::LOGGED_IN:
        loggedIn();
        break;
    case APP_STATE::MENU:
        menu();
        break;
    default:
        break;
    }
}

void App::finish()
{

}

bool App::isActive()
{
    return m_isActive;
}

void App::logIn()
{

    printCommands();
    cout << "Insert your command: ";
    cin >> m_cin;

    while (true)
    {
        cout << "\n";

        if (!isNumber(m_cin))
        {
            cout << "Command must be a number!\nPlease reenter: ";
            cin >> m_cin;
            continue;
        }
        if (!(stoi(m_cin) >= 1 && stoi(m_cin) <= m_commands[m_state].size()))
        {
            cout << "No such command!\nPlease reenter: ";
            cin >> m_cin;
            continue;
        }
        cout << "Executing command " << m_cin << "...\n" << "\n";
        break;
    }
    
    system("CLS");

    switch (stoi(m_cin))
    {
    case 1:
        ASDM();
        break;
    case 2:
        printAboutMyApp();
        break;
    case 3:
        printBriefTutorial();
        break;
    case 4:
        registerParticipant();
        break;
    case 5:
        logIntoAccount();
        break;
    case 6:
        forgotPassword();
        break;
    case 7:
        printMSGS();
        break;
    case 8:
        exit();
        return;
        break;
    default:
        break;
    }

    cout << "\nInsert anything to continue... ";
    cin >> m_cin;
    system("CLS");
}

void App::loggedIn()
{
    printCommands();
    cout << "Insert your command: ";
    cin >> m_cin;

    while (true)
    {
        cout << "\n";

        if (!isNumber(m_cin))
        {
            cout << "Command must be a number!\nPlease reenter: ";
            cin >> m_cin;
            continue;
        }
        if (!(stoi(m_cin) >= 1 && stoi(m_cin) <= m_commands[m_state].size()))
        {
            cout << "No such command!\nPlease reenter: ";
            cin >> m_cin;
            continue;
        }
        cout << "Executing command " << m_cin << "...\n" << "\n";
        break;
    }

    system("CLS");

    switch (stoi(m_cin))
    {
    case 1:
        PSDM();
        break;
    case 2:
        changeName();
        break;
    case 3:
        changePassword();
        break;
    case 4:
        applyForAdmin();
        break;
    case 5:
        getPersonalInfo();
        break;
    case 6:
        getAllParticipantsPublicInfoByName();
        break;
    case 7:
        getAllParticipantsPublicInfoByBalance();
        break;
    case 8:
        searchForParticipant();
        break;
    case 9:
        goToMenu();
        break;
    case 10:
        logOut();
        break;
    default:
        break;
    }

    cout << "\nInsert anything to continue... ";
    cin >> m_cin;
    system("CLS");
}

void App::menu()
{
}

void App::initCommands()
{
    fstream stream;

    int numberOfCommands = 0;

    stream.open(DATA_FOLDER + "logInCommands.txt");
    stream >> numberOfCommands;
    m_commands[APP_STATE::LOG_IN].resize(numberOfCommands);
    
    for (int i = 0; i < numberOfCommands; i++)
    {
        stream>>m_commands[APP_STATE::LOG_IN][i];
    }
    stream.close();
    
    stream.open(DATA_FOLDER + "loggedInCommands.txt");
    stream >> numberOfCommands;
    m_commands[APP_STATE::LOGGED_IN].resize(numberOfCommands);
       
    for (int i = 0; i < numberOfCommands; i++)
    {
        stream>>m_commands[APP_STATE::LOGGED_IN][i];
    }
    stream.close();
    
    stream.open(DATA_FOLDER + "menuCommands.txt");
    stream >> numberOfCommands;
    m_commands[APP_STATE::MENU].resize(numberOfCommands);
       
    for (int i = 0; i < numberOfCommands; i++)
    {
        stream>>m_commands[APP_STATE::MENU][i];
    }
    stream.close();
}

void App::initAdminPassword()
{
    fstream stream;
    stream.open(DATA_FOLDER + "adminPassword.txt");

    stream >> m_adminPass >> m_adminPass;

    stream.close();
}

void App::initMenu()
{
    string path = MENU_FOLDER;
    for (const auto& entry : fs::directory_iterator(path))
    {
        fstream stream;
        stream.open(entry.path());
    
        Item item;
        string temp;
    
        stream >> temp >> temp;
        item.name = temp;

        stream >> temp;
        if (temp == "Description: ")
        {
            char a;
            do
            {
                stream >> temp;
                item.description += temp;
                a = item.description.back();

            } while(a != endSymbol || item.description.size() > maximumDescriptionLength);
            
            stream >> temp;
        }
        else
        {
            stream >> temp;
        }

        stream >> temp;
        item.price = stof(temp);

        m_menu.addItem(item);
        stream.close();
    }
}

void App::initParticipants()
{
    string path = PARTICIPANT_FOLDER;
    for (const auto& entry : fs::directory_iterator(path))
    {
        fstream stream;
        string name;
        string password;
        bool isAdmin;
        int balance;

        stream.open(entry.path());

        stream >> name >> name;
        stream >> password >> password;
        stream >> isAdmin >> isAdmin;
        stream >> balance >> balance;

        stream.close();

        Participant tempParticipant;
        tempParticipant.setParticipant(name, password, isAdmin, balance);
        m_participants.insert(make_pair(name, tempParticipant));
    }
}

void App::writeInFile(string path, vector<string>& content)
{
    fstream stream;
    string file;
    string temp;

    stream.open(path);

    for (int i = 0; i < content.size(); i++)
    {
        stream << content[i] << "\n";
    }

    stream.close();
}

void App::printAFile(string path)
{
    fstream stream;
    string file;
    string temp;

    stream.open(path);

    while (getline(stream, temp))
    {
        file += temp;
        file.push_back('\n');
    }

    stream.close();

    cout << file << endl;
}

void App::readAFile(vector<string>& output, string path)
{
    fstream stream;
    string file;
    string temp;

    stream.open(path);

    while (getline(stream, temp))
    {
        output.push_back(temp);
    }

    stream.close();
}

void App::printCommands()
{

    cout << "Please insert the number of the command you want to be executed.\n" << "Note that invalid commands will not do anything!\n\n";

    for (int i = 0; i < m_commands[m_state].size(); i++)
    {
        cout << m_commands[m_state][i] << "\n";
    }
    cout << "\n";
}

void App::ASDM()
{
    cout << "Enter your message to Mister Minkov.\nNote that it is anonymous since you aren't logged in!\nTo end your message enter '#'!\nOtherwise it will be submitted automatically after 40 symbols!\n\nMessage: ";
 
    string temp;
    getline(cin, temp, '#');


    temp = "=============================================================================\nMessage: " + temp;

    temp += "\nAuthor: Anonymous\nDate: ";

    m_time = time(NULL);
    char* tm = new char;
    ctime_s(tm,40,&m_time);

    temp += tm;
    temp += "============================================================================";

    vector<string> tempFile;
    readAFile(tempFile, DATA_FOLDER + "suobshteniqDoMinkov.txt");

    tempFile.push_back(temp);
    writeInFile(DATA_FOLDER + "suobshteniqDoMinkov.txt", tempFile);

}

void App::printAboutMyApp()
{
    printAFile(DATA_FOLDER + "aboutTheApp.txt");
}

void App::printBriefTutorial()
{
    printAFile(DATA_FOLDER + "briefTutorial.txt");
}

void App::registerParticipant()
{
    string name;
    string password1;
    string password2;

    cout << "========================= Register: =======================\n\n";
    cout << "Enter your username. To exit enter 'exit': ";

    while (true)
    {
        cin >> name;
        if (name == "exit") return;

        if (m_participants.find(name) != m_participants.end())
        {
            cout << "Username taken! Try a new one. To exit enter 'exit'\nPlease reenter: ";
            continue;
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter your password. To exit enter 'exit': ";
        cin >> password1;
        if (password1 == "exit") return;
        cout << "Reenter your password: ";
        cin >> password2;
        if (password1 != password2)
        {
            cout << "Passwords don't match!\n";
            continue;
        }
        else
        {
            break;
        }
    }

    Participant temp;
    temp.createParticipant(name, password1);
    temp.setParticipant(name,password1,0,0.0f);
    m_participants.insert(make_pair(name,temp));
}

void App::logIntoAccount()
{
    string name;
    string password;

    cout << "========================= Log in :=======================\n\n";

    while (true)
    {
        cout << "Enter your username. To exit enter 'exit': ";
        cin >> name;
        if (name == "exit") return;
        if (m_participants.find(name) == m_participants.end())
        {
            cout << "No such user!\nPlease try again!\n\n";
            continue;
        }
        
        cout << "Enter your password: ";
        cin >> password;
        
        if (m_participants.at(name).getPassword() != password)
        {
            cout << "Incorrect password!\nPlease try again!\n\n";
            continue;
        }

        cout << "Succesfully logged in!\n";
        m_state = APP_STATE::LOGGED_IN;
        m_currentAccount = name;
        break;
    }
}

void App::forgotPassword()
{
}

void App::printMSGS()
{
    cout << "========================== Messages to Minkov ===============================\n\n";
    printAFile(DATA_FOLDER + "suobshteniqDoMinkov.txt");
}

void App::exit()
{
    m_isActive = false;
}

void App::PSDM()
{
    cout << "Coming soon!\n";
}

void App::changeName()
{
    cout << "Coming soon!\n";
}

void App::changePassword()
{
    cout << "Coming soon!\n";
}

void App::applyForAdmin()
{
    if (m_participants.at(m_currentAccount).isAdmin())
    {
        cout << "Account is already admin";
        return;
    }

    cout << "To become admin, you must enter the admin password! To exit enter 'exit'\n";
    
    while (true)
    {
        cout << "Enter admin pass: ";
        cin >> m_cin;
        if (m_cin == "exit") return;
        if (m_cin == m_adminPass)
        {
            m_participants.at(m_currentAccount).becomeAdmin();
            return;
        }
        else
        {
            cout << "Incorrect password!\nPlease try again!\n\n";
        }
    }
}

void App::getPersonalInfo()
{
    cout << "Coming soon!\n";
}

void App::getAllParticipantsPublicInfoByName()
{
    cout << "Coming soon!\n";
}

void App::getAllParticipantsPublicInfoByBalance()
{
    cout << "Coming soon!\n";
}

void App::searchForParticipant()
{
    cout << "Coming soon!\n";
}

void App::goToMenu()
{
    cout << "Coming soon!\n";
}

void App::logOut()
{
    m_state = APP_STATE::LOG_IN;
    m_currentAccount = "";
}

bool App::isNumber(string checkable)
{
    for (int i = 0; i < checkable.size(); i++)
    {
        if (!(checkable[i] >= '0' && checkable[i] <= '9'))
        {
            return false;
        }
    }
    return true;
}
