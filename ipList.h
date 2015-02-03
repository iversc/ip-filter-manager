#include <string>
using namespace std;

struct dateTime {
    string date;
    string time;
};

struct ipList {
    string IP;
    int count;
    dateTime * first;
    dateTime * last;
    ipList* next;
};

