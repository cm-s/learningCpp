/*
 * game_coupons
 * Tells the user how much candy and gumballs they would have won given how many coupons they have.
 *
 * Charles Stevens
 * Date created: undetermined
 */
#include <iostream>
using namespace std;

int main()
{
    //variables representing the number of coupons, number of coupons remaining, candy
    //that is possible to be earned and gumballs possible to be earned.
    int couponsWon, remaining, candy, gumballs;

    //requesting the user to input the number of coupons they have won.
    cout << "How many coupons have you won?";
    cin >> couponsWon;

    //calculating the candy possible to be won.
    candy = couponsWon / 10;
    //storing the remaining coupons in the respective variable.
    remaining = couponsWon % 10;
    //calculating the gumballs possible to be won from the remaining coupons.
    gumballs = remaining / 3;

    //logging the amount of candy and gumballs that can be recieved to the console.
    cout << "You won " << candy << " Chocolate bars and " << gumballs  << " gumballs!";

    return 0;
}
