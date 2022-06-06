#include "Participant.h"

Participant::Participant()
{
}
Participant::~Participant()
{
}

void Participant::createParticipant(string name, string password)
{
    m_name = name;
    m_password = password;
    m_isAdmin = false;

    string path = PARTICIPANT_FOLDER + m_name +".txt";
    string temp;
    ofstream stream(path);
    
    temp = "Name: ";
    stream << temp << m_name;
    temp = "\nPassword: ";
    stream << temp << m_password;
    temp = "\nIsAdmin: ";
    stream << temp << m_isAdmin;
    temp = "\nBalance: ";
    stream << temp << m_balance;
    
    stream.close();

    cout << "Successfully registered!\n";

}

void Participant::setParticipant(string name, string password, bool isAdmin, float balance)
{
    m_name = name;
    m_password = password;
    m_isAdmin = isAdmin;
    m_balance = balance;
}

void Participant::becomeAdmin()
{
    m_isAdmin = true;
    printf("Congratulations %s!!! You have successfully been promoted to admin!\n", m_name.c_str());
}

void Participant::purchaseItem(Item item, string date)
{
    purchasedItem temp;
    temp.item = item;
    temp.purchaseDate = date;

    m_purchaseHistory.push_back(temp);

    m_balance -= item.price;
}

void Participant::pay(float amount)
{
    m_balance += amount;
}

void Participant::coutAllInfo()
{
    cout << "Name: " << m_name << "\n";
    cout << "Permissions: ";
    if (m_isAdmin) cout << "Admin\n";
    else cout << "Participant\n";
    cout << "Balance: " << m_balance << "\n";

    for (int i = m_purchaseHistory.size() - 1; i >= 0; i--)
    {
        cout << m_purchaseHistory[i].item.name << " " << m_purchaseHistory[i].purchaseDate << "\n";
    }
}

void Participant::coutPublicInfo()
{
    cout << "Name: " << m_name << "\n";
    cout << "Balance: " << m_balance << "\n";
}

string Participant::getPassword()
{
    return m_password;
}

bool Participant::isAdmin()
{
    return m_isAdmin;
}
