#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <locale>
#include <stdlib.h>
#include "CMenu.h"
#include "ipList.h"

using namespace std;

ipList * mainList = NULL;
ipList ** ipArr = NULL;
unsigned int IPcount = 0;
bool interactiveMode = false;
bool testMode = false;
bool verboseMode = false;

void addToList(string IP, dateTime * dt);
void mainMenu();
void selectedItemMenu(unsigned int selected);
void convertToArray();
void printArray(unsigned int start, unsigned int end);

template <typename T>
  string NumberToString ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }

int main(int argc, char ** argv)
{
    string line;
    string toShow;
    string fileName = "/var/log/iptables.log";
    
    if(argc > 1)
    {
        for(int paramCount = 1; paramCount < argc; paramCount++)
        {
            string sArgV = string(argv[paramCount]);
            if(sArgV == "-t")
            {
                fileName = "./testdata";
                testMode = true;
            }
            /*else
            {
                fileName = fileName + "." +sArgV;
            }*/
            
            if(sArgV == "-i")
            {
                interactiveMode = true;
            }
            
            if(sArgV == "-p")
            {
                if (testMode)
                {
                    cout << "Error: -t and -p are mutually exclusive." << endl;
                    exit(1);
                }
                fileName = fileName + ".1";
            }
            
            if(sArgV == "-v")
            {
                verboseMode = true;
            }
        }
    }
    
    ifstream myfile(fileName.c_str());
    int lineCount = 0;
    size_t srcPos = 0;
    size_t srcEnd = 0;
    if(myfile.is_open())
    {
        while(getline(myfile, line))
        {
            toShow = line;
            srcPos = line.find("SRC=");
            if(srcPos != string::npos)
            {
                srcEnd = line.find(' ', srcPos);
                if (srcEnd != string::npos)
                {
                    //Offset by 4 to get rid of SRC=
                    toShow = line.substr(srcPos + 4, srcEnd-srcPos - 4);
                    dateTime * dt = new dateTime;
                    dt->date = "N/A";
                    dt->time = "N/A";

                    dt->date = line.substr(0, 6);
                    dt->time = line.substr(7, 8);
                    addToList(toShow, dt);
                }
            }

            //cout << toShow << '\n';
            lineCount++;
        }

        myfile.close();
        cout << endl << lineCount << " access attempts." << endl << endl;

        convertToArray();
        if(interactiveMode)
        {
            mainMenu();
        }
        else if (verboseMode)
        {
            printArray(0, IPcount);
            cout << endl;
        }
    }
    else //if(myfile.isopen())
    {
        cout << "Unable to open file.\n";
    }

    return 0;
}

void selectedItemMenu(unsigned int selected)
{
    string sel;
    CMenu * menu = new CMenu;
    menu->AddItem("1", "WHOIS query");
    menu->AddSeparator();
    menu->AddItem("b", "Back to Main Menu");
    
    while(sel != "b")
    {
        cout << "Selected IP: " << ipArr[selected]->IP << endl
            << "\t" << "Total Entries: " << ipArr[selected]->count << endl
            << "\t" << "First: " << ipArr[selected]->first->date << " " 
            << ipArr[selected]->first->time << endl
            << "\t" << "Last: " << ipArr[selected]->last->date << " " 
            << ipArr[selected]->last->time << endl
            << endl; 
/*            
        cout << "1 - WHOIS query" << endl
            << endl;
            
        cout << "b - Back to Main Menu" << endl << endl;
        
        cout << "Make a selection. >";
        cin >> sel;*/
        
        sel = menu->Show();
        
        if(sel == "1")
        {
            system(string("whois " + ipArr[selected]->IP + " | less").c_str());
        }
    }

    delete menu;
}

void mainMenu()
{
    string sel;
    unsigned int page = 0;
    locale loc;
    ipArr = new ipList*[IPcount];
    for(unsigned int x = 0; x < IPcount; x++)
    {
        ipArr[x] = mainList;
        mainList = mainList->next;
    }

    while (sel != "q" && sel != "Q")
    {
        printArray((page * 10), (page * 10) + 10);
        cout << endl;
        if( (IPcount > 10) && ((page * 10) + 10 < IPcount) )
        {
            cout << "n - Next page" << endl;
        }
        
        if(page > 0)
        {
            cout << "p - Previous page" << endl;
        }
        cout << "q - Quit" << endl << endl;
        cout << "Make a selection. >";
        cin >> sel;
        
        if(sel == "p" && page > 0)
        {
            page--;
        }
        else if(sel == "n" && ((page * 10) + 10 < IPcount) )
        {
            page++;
        }
        else if(sel == "q")
        {
            break;
        }
        else
        {
            stringstream convert(sel);
            unsigned int selected = 0;
            convert >> selected;
            selected = (page * 10) + selected;
            if (! (selected >= IPcount))
            {
                selectedItemMenu(selected);
            }
            else
            {
                cout << "Invalid selection." << endl;
            }
        }
    }
}

void printArray(unsigned int start, unsigned int end)
{
    for(unsigned int x = start; x < end && x < IPcount; x++)
    {
        cout << (x - start) << " - " << ipArr[x]->IP << ": " << ipArr[x]->count //<< endl
            << "\t" << "First: " << ipArr[x]->first->date << " " << ipArr[x]->first->time //<< endl
            << "\t" << "Last: " << ipArr[x]->last->date << " " << ipArr[x]->last->time //<< endl
            << endl;

    }
}

void convertToArray()
{
    ipArr = new ipList*[IPcount];
    ipList * curList = mainList;
    for(unsigned int x = 0; x < IPcount; x++)
    {
        ipArr[x] = curList;
        curList = curList->next;
    }
}

void addToList(string IP, dateTime * dt)
{
    ipList * curList = mainList;
    ipList * lastItem = NULL;

    while(curList != NULL)
    {
        if(curList->IP == IP)
        {
            curList->count++;
            if(curList->first != curList ->last) delete curList->last;
            curList->last = dt;
            break;
        }

        lastItem = curList;
        curList = curList->next;
    }

    if(curList == NULL)
    {
        IPcount++;
        ipList * newItem = new ipList;
        newItem->IP = IP;
        newItem->count = 1;
        newItem->next = NULL;
        newItem->first = dt;
        newItem->last = dt;

        if(lastItem==NULL)
        {
            mainList = newItem;
        }
        else
        {
            lastItem->next = newItem;
        }

    }
}

