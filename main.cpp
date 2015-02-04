#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <locale>
#include "ipList.h"

using namespace std;

ipList * list = NULL;
ipList ** ipArr = NULL;
unsigned int IPcount = 0;


void addToList(string IP, dateTime * dt);
void mainMenu();
void convertToArray();

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
    
    if(argc == 2)
    {
        fileName = fileName + "." +string(argv[1]);
    }
    
    ifstream myfile(fileName.c_str());
    int lineCount = 0;
    unsigned int srcPos = 0;
    unsigned int srcEnd = 0;
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
        cout << "Entries: " << lineCount << endl << endl;

        ipList * curList =  list;
        while(curList != NULL)
        {
            cout << curList->IP << ": " << curList->count << endl;
            cout << "\t" << "First: " << curList->first->date << " " 
                << curList->first->time << endl;
            cout << "\t" << "Last: " << curList->last->date << " " 
                << curList->last->time << endl << endl;
            
            curList = curList->next;
        }
        convertToArray();
        mainMenu();
    }
    else //if(myfile.isopen())
    {
        cout << "Unable to open file.\n";
    }

    return 0;
}

void mainMenu()
{
    string sel;
    locale loc;
    while (sel != "q" && sel != "Q")
    {
        cout << "Make a selection. >";
        cin >> sel;
    }
}

void convertToArray()
{
    ipArr = new ipList*[IPcount];
    ipList * curList = list;
    for(unsigned int x = 0; x < IPcount; x++)
    {
        ipArr[x] = curList;
        curList = curList->next;
    }
    
    
}

void addToList(string IP, dateTime * dt)
{
    ipList * curList = list;
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
            list = newItem;
        }
        else
        {
            lastItem->next = newItem;
        }

    }
}

