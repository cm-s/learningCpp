#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
* Discalimer!: This algorythm cannot function past imputs in excess of nine digits due to the max value an integer can hold
* This will be solved in the near future.
*/

auto indexer(auto input, string type, int min, int max) {
    if (type == "int") {
        if (min < 2) {
            cout << "\nError: " << __FILE__ << ": indexer(): parameter three invalid. Minimum concatenation index cannot be less than 2." << endl;
            exit(EXIT_SUCCESS);
        };
        if (max < 1) {
            cout << "\nError: " << __FILE__ << ": indexer(): parameter four invalid. Maximum concatenation index cannot be less than 1." << endl;
            exit(EXIT_SUCCESS);
        };
        int* final;
        final = new int;
        int* point;
        point = new int;
        *point = 1;
        float* counter;
        counter = new float;
        *counter = input/10;
        while((int) *counter != 0) {
            *point += 1;
            *counter /= 10;
        };//determined length of input
        if (*point >= 9) {
            cout << "\nError: " << __FILE__ << ": indexer(): parameter one invalid. Calculaitons become interpolated when input is nine or more digits long." << endl;
            exit(EXIT_SUCCESS);
        };
        *final = input;
        *counter = input/pow(10, *point - min + 1);//for some reason this math disregards digits at the end of an input long enough
        cout << __LINE__ << " Debug: counter value: " << *counter << endl;                  //but doesn't change the outcome
        //created decimaled value to count to
        int* min_threshold;
        min_threshold = new int;
        *min_threshold = 1;
        while (*min_threshold != (int) *counter) {
            *min_threshold += 1;
        };
        //replicated the number before the "index" place of the given minimum
        cout << __LINE__ << " Debug: min_threshold: " << *min_threshold << endl;
        *final -= *min_threshold*pow(10, *point - min + 1);
        int min_deduced_total = *final;
        cout << __LINE__ << " Debug: min_deduced_total: " << min_deduced_total << endl << endl;
        //stored value with deducted min indexes
        *counter = input/pow(10, max - 1);//calculations become interpolated at more than eight digits
        *counter -= (int) *counter;
        cout << __LINE__ << " Debug: counter value: " << *counter << endl;
        *final = *counter*pow(10, max - 1);
        *final = min_deduced_total-*final;
        cout << __LINE__ << " Debug: final value: " << *final << endl;
        *final /=pow(10, max - 1);
        cout << __LINE__ << " Debug: final: " << *final << endl;
        return *final;
    };
};

int main()
{
//syntax for this function is indexer(auto <input>, string <type>, int <min index>, int <max index>)
cout << indexer(51555192, "int", 2, 1);

return 0;
};
