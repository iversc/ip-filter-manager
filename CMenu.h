#ifndef __CMENU_H__
#define __CMENU_H__

#include <string>
#include <list>

using namespace std;

struct CMenuItem
{
    string key;
    string display;
};

class CMenu
{
private:
    list<CMenuItem*> menuList;
    
public:
    CMenu();
    ~CMenu();
    int AddItem(string key, string display);
    void AddSeparator();
    string Show();
};

#endif
