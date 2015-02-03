#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ipList.h"

using namespace std;

template <typename T>
  string NumberToString ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }

int main()
{
    ipList * list = NULL;
    string line;
    string toShow;
    ifstream myfile("/var/log/iptables.log.1");
    int lineCount = 0;
    int srcPos = 0;
    int srcEnd = 0;
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
                    if(list == NULL)
                    {
                        list = new ipList;
                        list->IP = toShow;
                        list->count = 1;
                        list->next = NULL;
                    }
                    else
                    {
                        ipList * curList = list;
                        while(curList->IP != toShow)
                        {
                            if(curList->next == NULL)
                            {
                                ipList * newItem = new ipList;
                                newItem->IP = toShow;
                                newItem->count = 0;
                                newItem->next = NULL;
                                curList->next = newItem;
                                curList = newItem;
                            }
                            else
                            {
                                curList = curList->next;
                            }
                        }

                        curList->count++;
                    }
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
    else
    {
        cout << "Unable to open file.\n";
    }

    return 0;
}
