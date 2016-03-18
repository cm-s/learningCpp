/*
 * free-fall
 * Shows the user how far an object would have fallen in a given period of time.
 *
 * Charles Stevens
 * Date created: undetermined
 */
#include <cmath>
#include <iostream>
using namespace std;

int main()
{
    //variable representing the time a give item will fall.
    float fallTime;
    //variable representing the distance an object will fall.
    float distance;

    //requesting the desired time the user wants the object to fall.
    cout << "Enter your time.";
    cin >> fallTime;

    //calculation for the distance an object would have fallen in the given time.
    distance = .5 * 32 * pow(fallTime, 2);
    //printing the distance for the user
    cout << "An object falling for that time would have fallen " << distance << " feet!";

    return 0;
}
