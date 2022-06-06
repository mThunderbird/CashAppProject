#pragma once

#include "Menu.h"

struct purchasedItem
{
    Item item;
    string purchaseDate;
};

class Participant
{
public:

    Participant();
    ~Participant();

    void createParticipant(string name, string password);
    void setParticipant(string name, string password, bool isAdmin, float balance);
    void becomeAdmin();
    void purchaseItem(Item item, string date);
    void pay(float amount);

    void coutAllInfo();     // name, pass, permissions, balance, purchaseHistory
    void coutPublicInfo();  //name, balance

    string getPassword();
    bool isAdmin();

private:

    string m_name;
    string m_password;
    bool m_isAdmin;

    float m_balance;

    vector<purchasedItem> m_purchaseHistory;
};
