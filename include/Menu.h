#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <conio.h>
#include <ctime>
#include <fstream>

using namespace std;

static string DATA_FOLDER = "C:\\Users\\drago\\Documents\\NiTe\\CashAppProject\\config\\";
static string MENU_FOLDER = DATA_FOLDER + "\\menu\\";
static string PARTICIPANT_FOLDER = DATA_FOLDER + "\\participant\\";

constexpr char endSymbol = 35;
constexpr int maximumDescriptionLength = 40;

struct Item
{
    string name;
    string description;

    float price;

    void operator=(Item a)
    {
        name = a.name;
        description = a.description;
        price = a.price;
    }

};

class Menu
{
public:


    Menu();
    ~Menu();

    void addItem(Item item);
    bool removeItem(string name);

    void coutFullInfoCatalogue();
    void coutReducedInfoCatalogue();

    // TO-DO
    void coutCatalogueByPrice();
    void coutCatalogueByName();

private:

    vector<Item> m_catalogue;

};
