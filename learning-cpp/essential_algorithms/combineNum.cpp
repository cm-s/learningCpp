#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int combineNum(string base, string addon);
int combineNum(string base, string addon)
{
    string* buffer;
    buffer = new string;
    for (size_t head = 0; head < 40; head++) {
        if (base[head] != 0) { *buffer += base[head]; }
        else { break; };
    };
    for (size_t head = 0; head < 40; head++) {
        if (addon[head] != 0) { *buffer += addon[head]; }
        else { break; };
    };
    string refinedBuffer = *buffer;
    int* total;
    total = new int;
    int* cb;
    cb = new int;
    for (size_t head = 0; head < 40; head++) {
        if (refinedBuffer[head] != 0) { *cb += 1; } //interchange refinedBuffer with base for original fuctionallity
        else { break; };
    };
    if (*cb > 9) { cout << "\nWarning: combineNum: Functionallity depreciates after more than nine digits are inputted." << endl; };
    for (int i = 0; i < *cb; i++) {
        int subject = (int) refinedBuffer[i]; //interchange refinedBuffer with base for original fuctionallity
        switch (subject) {
            case 48: subject = 0; break;
            case 49: subject = 1; break;
            case 50: subject = 2; break;
            case 51: subject = 3; break;
            case 52: subject = 4; break;
            case 53: subject = 5; break;
            case 54: subject = 6; break;
            case 55: subject = 7; break;
            case 56: subject = 8; break;
            case 57: subject = 9; break;
        };
        *total += (subject*pow(10,((*cb -i)-1)));
    }; cout << *total << endl;
}

int main ()
{
    
combineNum("10016", "4");

return 0;
}
