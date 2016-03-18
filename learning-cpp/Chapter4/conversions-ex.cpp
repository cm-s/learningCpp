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
void inMod(int& unit, int& val1, int& val2);
/**
 * calculates kilogram and gram conversions.
 *
 * @param placeholders representing the input of pounds and ounces.
 * @return converted values for pounds and ounces.
 */
void calcKG(int lbs, int oz);
/**
 * calculates pound and ounce conversions.
 *
 * @param placeholders representing the input of kilograms and grams.
 */
void calcLB(int kg, int grams);
/**
 * module to prompt for user input.
 *
 * @param variable to store the user's input in.
 */
void prompt(char& userResponse);

int main()
{
    //declaring values for place of user input.
    int val1;
    int val2;
    int unit;
    //variable representing user response.
    char userResponse = 'y';
    do {
        inMod(unit, val1, val2);
        if (unit == 1) { 
            calcKG(val1, val2);
        } else {calcLB(val1, val2);}
        prompt(userResponse);
    } while(userResponse != 'n' || userResponse != 'N');

return 0;
}

void prompt(char& userResponse) {
    cout << "Would you like to continue? y/N";
    cin >> userResponse;
};

void inMod(int& unit, int& val1, int& val2) {
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

void calcKG(int lbs, int oz) {
    //temporary value to represent grams.
    int grams;
    int kg;
    //deconpress lbs into oz.
    oz += (lbs *16);
    //converting ounes into grams
    grams = (oz *28.3495);
    kg = grams/1000;
    grams = grams %1000;
    //outputting conversions to the console
    cout << kg << " kilograms and " << grams << " grams.";
};

void calcLB(int grams, int kg) {
    //temporary value to represent oz.
    int oz;
    int lbs;
    //deconpressed kg into grams.
    grams += (kg * 1000);
    //converting grams into ounces.
    oz = (grams * 0.035274);
    
    lbs = oz/16;
    oz = oz%16;
 
    cout << lbs << " pounds and " << oz << "ounces.";
};