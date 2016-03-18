/*
 * phone-numbers
 * This program prompts the user for a phone number, outputs phone number, and then
 * asks the user if they would like to change the phone number. If yes, the program will
 * call a function to change the phone number. Otherwise the program will end. The purpose
 * of this program is to practice using pass by reference parameters.
 *
 * Charles Stevens
 * Date created: 3/4/16
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * changeNumeber
 *
 * @param user's phone number.
 */
 void changeNumber(int& phoneNumber);
 
int main ()
{
    int originalNum = 0;
	cout << "What is your phone number?";
	cin >> originalNum;
	
    cout << originalNum << "\n Would you like to change this number?";
    string response;
    cin >> response;
    
    if (response == "yes") {
        changeNumber(originalNum);
    }
    
    cout << originalNum;
	
return 0;
}

void changeNumber(int& phoneNumber) {
    cout << "What is your new number?";
    cin >> phoneNumber;
    cout << phoneNumber << endl;
}