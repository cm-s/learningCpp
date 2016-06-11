#include <string>
#include <iostream>
#include <cmath>
using namespace std;
auto copyIn(string base, string addon, string type);
auto copyIn(string base, string addon, string type)
{
if (type == "string") {
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

    return *buffer;
} /*else if (type == "int") {
    int* cb;
    cb = new int;
    int* ch;
    ch = new int;
    for (size_t head = 0; head < 40; head++) {
        if (base[head] != 0) { *cb += 1; }
        else { break; };
    };
    for (size_t head = 0; head < 40; head++) {
        if (addon[head] != 0) { *ch += 1; }
        else { break; };
    };
    for (size_t i = 0; i < *cb; i++) {
        num1 = (base[i]*pow(10,*cb))
    };

    int* combined;
    combined = new int;
    (10 * (*ch))
}*/ else {
    return false; };
};

int main() {
    cout << copyIn("Data one", " and data two", "string");

    return 0;
};
