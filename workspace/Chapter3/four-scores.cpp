/*
 * four-scores.cpp
 * Calculates the mean* of four user inputted scores.
 *
 * Author: Charles Stevens
 * Date created: 2/26/16
 */

#include <iostream>
#include <string>

using namespace std;

/**
 Asks if the user for consent to continue or to exit.
 
 @return the boolean that will be stored in the value of continue variable.
 */
bool inputMod();

/**
 * Computes the mean of a given value.
 * 
 * @param input list to be considered for computation.
 * @return the mean of input value.
 */
int compMean(int input[4]);

int main() 
{
    //the variable representing wether or not the user wishes to continue.
    //Set to true by default for sake of not requesting for consent to contine during initial run.
    bool cont  = true;
    //Variable representing the four values the user has input. Can only be be four values long.
    int oScores[4];
    
    //Condition holding true so long as the user has given consent to continue.
    while (cont == true) {
        //gather four scores using a for loop, store values in the oScores[] array
        cout << "Input four scores:";
        for(int it = 0; it < 4; it++)
            cin >> oScores[it];
        
        //Creates intager variable named mean, stores the returned value from the funciton compMean.
        int mean = compMean(oScores);
        
        //Outputs mean.
        cout << "The mean of your four scores is " << mean << ".";  
        
        //Stores returned value from inputMod in  cont.
        cont = inputMod();
    }
    
return 0;
}

bool inputMod() {
    //Placeholder for user input.
    char yn;
    cout << " Would you like to contine? (y/n)";
    cin >> yn;
    
    //If consent recieved as "y" return true. Otherwise return false.
    if (yn == 'y')
        return true;
    else
        return false;
    
}

int compMean(int input[4]) {
    //Placeholder for integer value for arithmetic computations
    int temp = 0;
    
    //Adds each value from array and stores in the temp variable.
    for (int range = 0; range < 5; range++)
        temp += input[range];
    
    //Returns values divided by their length.
    return temp / 4;
}