#include <string>
#include <iostream>
using namespace std;

int input(char& unit, int& value1, int& value2);

bool prompt(char response);

void calculateKG(int lbs, double oz);

void calculateLBS(int kg, double grams);

int main()
{
    char unit;
    int value1, value2;
    char response = 'y';

    do {
        input(unit, value1, value2);
        if (unit == '1') {
            calculateKG(value1, value2);
        } else {calculateLBS(value1, value2);};
        
    } while(prompt(response));

    return 0;
}

int input(char& unit, int& value1, int& value2) {
    cout << "Would you like to convert Kg to Lbs or Lbs to Kg?";
    cout << "\nEnter the numebr 1 for Kg to Lbs or 2 for Lbs to Kg";
    cin >> unit;// >> endl;
    switch (unit) {
        case '1':
            cout << "\nEnter your Lbs: ";
            cin >> value1;
            cout << "\nEnter your Oz: ";
            cin >> value2;
            break;
        case '2':
            cout << "\nEnter your Kg: ";
            cin >> value1;
            cout << "\nEnter your Grams: ";
            cin >> value2;
            break;
    }
}

bool prompt(char response) {
    while (true) {
        cout << "\nDo you want to convert another weight?";
        cin >> response;
        switch (tolower(response)) {
            case 'y':
                return true;
                break;//practice
            case 'n':
                return false;
                break; //practice
            default:
                cout << "Try again";
                break;//practice
        };
    };
}

void calculateKG(int lbs, double oz) {
    float kg;
    float grams;

    oz += (lbs *16);
    grams = (oz *35.274);
    kg = (grams /1000);
    grams = (int(grams) %1000);

    cout << kg << " kg and " << grams << "grams." << endl;
}

//code for these calculations seems a little off

void calculateLBS(int kg, double grams) {
    float lbs;
    float oz;

    grams += (kg *1000);
    oz = (grams *0.035274);
    lbs = (oz /16);
    oz = (int(oz) %16);

    cout << lbs << " pounds and " << oz << " ounces." << endl;
}
