#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::addItem(Item item)
{
    m_catalogue.push_back(item);
}

bool Menu::removeItem(string name)
{
    for (int i = 0; i < m_catalogue.size(); i++)
    {
        if (m_catalogue[i].name == name)
        {
            m_catalogue.erase(m_catalogue.begin() + i);
            return true;
        }
    }
    return false;
}

void Menu::coutFullInfoCatalogue()
{
    for (int i = 0; i < m_catalogue.size(); i++)
    {
        cout << i << ". " << m_catalogue[i].name << "\n" << m_catalogue[i].description << "\n" << m_catalogue[i].price << "\n";
    }
}

void Menu::coutReducedInfoCatalogue()
{
    for (int i = 0; i < m_catalogue.size(); i++)
    {
        cout << i << ". " << m_catalogue[i].name << " - " << m_catalogue[i].price << "\n";
    }
}
