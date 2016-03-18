/*
 * unit-conversions
 * Displays the converted values from either pounds and ounces to kilograms and grams or kilograms
 * and grams to pounds and ounces depending on wether or not the user consents to continue.
 *
 * Charles Stevens
 * Date created: 3/9/16
 */
#include <string>
#include <cstring>
#include <iostream>
using namespace std
/**
 * queries the user for input.
 *
 * @param variable by which user input will be stored.
 * @return variable with user input stored within.
 */
int inMod(double inival[2]);
/**
 * calculates kilogram and gram conversions.
 *
 * @param placeholders representing the input of pounds and ounces.
 * @return converted values for pounds and ounces.
 */
int calcKG(double lbs, oz);
/**
 * calculates pound and ounce conversions.
 *
 * @param placeholders representing the input of kilograms and grams.
 */
int calcLB(double kg, grams);
/**
 * module to prompt for user input.
 *
 * @param variable to store the user's input in.
 */
void prompt();

//placeholder repersenting user choice.
char choice;

int main()
{
    //units subin variable should be declared here
    //variable representing user response.
    //did not declare subin values for indexes of inival
    string&/*should be of type char*/ ur = "y";
    
    do {
        inMod();
        if (choice == 1) { 
            calcKG(inival[0], inival[1]);
        } else {calcLB(inival[0], inival[1]);}//needs reconstruction
        prompt(string ur);
    } while(ur != "n" || ur != "N");

return 0;
};
void prompt(string ur) {
    cout << "Would you like to continue? y/N";
    cin >> /*userResponse*/ur;
};

int inMod(double inival[2]) {
    cout << "What unit types would you like to convert?";
    cout << "\nType 1 for pounds and ounces to kilograms and grams.";
    cout << "\nOr type 2 for kilograms and grams to pounds and ounces.";
    //unit subin should be injected into on this line
    switch(/*units*/tu) {
        case 1:
            cout << "Enter your weight values in Lbs and oz";
            cout << "\nLbs: ";
            cin >> inival[0];
            cout << "\nOz: ";
            cin >> inival[1];
            /*forgot to break*/
        case 2:
            cout << "Enter your weight values in kg and grams";
            cout << "\nKg: ";
            cin >> inival[0];
            cout << "\nGrams: ";
            cin >> endl >> inival[1];
            /*forgot to break*/
    };
    /*choice = tu;
    return inival[2];*///the purpose of this code has been defeated at this point
};

void calcKG(double lbs, double oz) {
    //temporary value to represent grams.
    double grams;
    //deconpress lbs into oz.
    oz += (lbs *16);
    //converting ounes into grams
    grams = (oz *28.3495);
    //converting grams to integural value.
    int intG = grams;
    //outputting conversions to the console
    cout << (intG /1000)/*this conversion should have been assigned to
    parameter value(kg)*/ << " kilograms and " << (intG %1000)/*and this one too(grams)*/ << "grams.";
};

int calcLB(double kg, double grams) {
    //temporary value to represent oz.
    double oz;
    //deconpressed kg into grams.
    grams += (kg *1000);
    //converting grams into ounces.
    oz = (grams *0.035274);
    //converting oz to integurial value.
    int intOz = oz;
    //logging conversions.
    cout << /*assign this to "lbs"*/(intOz %16) << " pounds and " << /*assign this
    to "oz"*/(intOz /16) << "ounces.";
};
