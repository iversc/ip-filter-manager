#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ipList.h"

using namespace std;

ipList * list = NULL;
void addToList(string IP);

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
                    addToList(toShow);
                }
            }

            //cout << toShow << '\n';
            lineCount++;
        }

        myfile.close();
        cout << "Entries: " << lineCount << endl;

        ipList * curList =  list;
        while(curList != NULL)
        {
            cout << curList->IP << ": " << curList->count << endl;
            curList = curList->next;
        }
    }
    else //if(myfile.isopen())
    {
        cout << "Unable to open file.\n";
    }

    return 0;
}

void addToList(string IP)
{
    ipList * curList = list;
    ipList * lastItem = NULL;
    
    while(curList != NULL)
    {
        if(curList->IP == IP)
        {
            curList->count++;
            break;
        }
        
        lastItem = curList;
        curList = curList->next;
    }
    
    if(curList == NULL)
    {
        ipList * newItem = new ipList;
        newItem->IP = IP;
        newItem->count = 1;
        newItem->next = NULL;
        
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

