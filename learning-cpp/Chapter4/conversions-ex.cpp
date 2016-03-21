/*
 * conversions-ex
 * Example Program
 * Displays the converted values from either pounds and ounces to kilograms and grams or kilograms
 * and grams to pounds and ounces depending on wether or not the user consents to continue.
 *
 * C. Pacheco
 * Date created: 3/15/16
 * Unresolved Bugs: calcLB (change data type)
 */
 
#include <string>
#include <iostream>
using namespace std;
/**
 * queries the user for input.
 *
 * @param two variables by which user input will be stored.
 * @return variable with user input stored within.
 */
void inMod(int& unit, float& val1, float& val2);
/**
 * calculates kilogram and gram conversions.
 *
 * @param placeholders representing the input of pounds and ounces.
 * @return converted values for pounds and ounces.
 */
void calcKG(float lbs, float oz);
/**
 * calculates pound and ounce conversions.
 *
 * @param placeholders representing the input of kilograms and grams.
 */
void calcLB(float kg, float grams);
/**
 * module to prompt for user input.
 *
 * @param variable to store the user's input in.
 */
bool prompt(char userResponse);

int main()
{
    float val1;
    float val2;
    int unit;
    char userResponse = 'y';
    do {
        inMod(unit, val1, val2);
        if (unit == 1) { 
            calcKG(val1, val2);
        } else {calcLB(val1, val2);}
    } while(prompt(userResponse));

return 0;
}

bool prompt(char userResponse) {
    while(true){
        cout << "Would you like to continue? y/N";
        cin >> userResponse;
            switch(tolower(userResponse)){
                case 'y':
                    return true;
                    break;
                case 'n':
                    return false;
                    break;
                default:
                    cout << "Please enter y/n: ";
                    break;
            }
    }
}

void inMod(int& unit, float& val1, float& val2) {
    cout << "What unit types would you like to convert?";
    cout << "\nType 1 for pounds and ounces to kilograms and grams.";
    cout << "\nOr type 2 for kilograms and grams to pounds and ounces.";
    cin >> unit;
    switch(unit) {
        case 1:
            cout << "Enter your weight values in Lbs and oz";
            cout << "\nLbs: ";
            cin >> val1;
            cout << "\nOz: ";
            cin >> val2;
            break;
        case 2:
            cout << "Enter your weight values in kg and grams";
            cout << "\nKg: ";
            cin >> val1;
            cout << "\nGrams: ";
            cin >> val2;
            break;
    }
}

void calcKG(float lbs, float oz) {
    float grams;
    float kg;
    oz += (lbs * 16);
    grams = (oz * 28.3495);
    kg = grams / 1000;
    grams = int(grams) % 1000;
    cout << kg << " kilograms and " << grams << " grams.";
}

void calcLB(float grams, float kg) {
    float oz;
    float lbs;
    grams += (kg * 1000);
    oz = (grams * 0.035274);
    lbs = oz/16;
    oz = int(oz) % 16;
    cout << int(lbs) << " pounds and " << oz << "ounces.";
}