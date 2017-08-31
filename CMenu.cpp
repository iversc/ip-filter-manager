#include <iostream>
#include <string>
#include "CMenu.h"

using namespace std;

CMenu::CMenu()
{
    
}

CMenu::~CMenu()
{

}

int CMenu::AddItem(string key, string display)
{
    if (key.length() > 1  || key.length() < 1) return 1;
    
    CMenuItem * newItem = new CMenuItem;
    newItem->key = key;
    newItem->display = display;
    menuList.push_back(newItem);
    return 0;
}

void CMenu::AddSeparator()
{
    CMenuItem * newItem = new CMenuItem;
    newItem->key = "SEP";
    newItem->display = "SEP";
    menuList.push_back(newItem);
}

string CMenu::Show()
{
    string sel;
    
    for(list<CMenuItem*>::iterator i = menuList.begin(); i != menuList.end(); ++i)
    {
        if((*i)->key == "SEP")
        {
            cout << endl;
        }
        else
        {
            cout << (*i)->key << " - " << (*i)->display << endl;
        }
    }
    
    cout << endl;
    cout << "Make a selection. >";

    cin >> sel;
    return sel;
}
