#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
                }
            }

            cout << toShow << '\n';
            lineCount++;
        }

        myfile.close();
        cout << "Entries: " << lineCount << endl;
    }
    else
    {
        cout << "Unable to open file.\n";
    }

    return 0;
}
