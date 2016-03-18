/*
 * salary
 * Calculates a payraise of 7.6 percent given a salary.
 *
 * Charles Stevens
 * Date created: undetermined
 */
#include <iostream>
using namespace std;
/**
 * Calculates and returns the payraise of 7.6 percent.
 *
 * @param salary to be used in the calculation.
 */
void calculateRaise(float initSalary);

int main()
{
    //variable representing the initial salary.
    double initSalary;
    //requesting the user to input their initial salary.
    cout << "What is your salary?";
    cin >> initSalary;

    calculateRaise(initSalary);

    return 0;
};

void calculateRaise(float initSalary)
{
    //variables representing the increase in pay in relation to the salary,
    //total increaase of pay and monthly pay increase.
    double payIncrease, total, monthly;
    //constant representing the value by wich to increase the pay.
    const double payRaise = 0.076;
    //calculating how much the pay will increase.
    payIncrease = initSalary * payRaise;
    //calculating the total increase of pay.
    total = payIncrease + initSalary;
    //dividing the total by the months in a year.
    monthly = total / 12;
    //returning values with respective phraises.
    cout << "You started with $" << initSalary << "! ";
    cout << "Now you have a new yearly salary of $" << total << "! ";
    cout << "With a monthly salary of $" << monthly << "!";
};
