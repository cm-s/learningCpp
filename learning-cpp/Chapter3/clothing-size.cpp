/*
 * clothing-size
 * Calculates and displays the waist, jacket and hat size given the user's height, weight and age.
 *
 * Charles Stevens
 * Date created: undetermined
 */
#include <iostream>

using namespace std;

//variable to represent height.
float height;
//variable to represent weight.
float weight;
//variable to represent age.
float age;

/**
 * hatSize
 *
 * @return value for calculated hat size.
 */
int hatSize();
/**
 * jacketSize
 *
 * @return the calculated value for the jacket size.
 */
int jacketSize();
/**
 * waist
 *
 * @return calculated value for the waist size.
 */
int waist();

int main()
{
    //requesting the user's input for height, weight and age.
    cout << "Enter your height:";
    cin >> height;
    cout << "Enter your weight:";
    cin >> weight;
    cout << "Enter your age:";
    cin >> age;

    //printing the values for the hat size, jacket size and waist size.
    cout << "Your hat size is " << hatSize() << ", your chest size is "
        << jacketSize() << " and your waist size is " << waist() << ".";

return 0;
};

int hatSize(){
    float retVal = (weight / height) * 2.9;
    return retVal;
};

int jacketSize() {
    //variable representing the adjustment size for the jacket.
    float adj;
    //converter for age step value. Aspect of adjustment calcualtion formula.
    float step;
    //placeholder for age step value.
    int cstep;

    if (age >= 40) {
        cstep = (age - 30) / 10;
        step = cstep;
    };
    //adding .8 to adjustment for each step up to the maximum step value.
    for (int a = 0; a < step; a++)
        adj += 0.8;

    //final calculation formula for jacket size.
    float retVal = (height * weight) / 288 + adj;
    return retVal;
};

int waist() {
    //representational value for adjustment of waist size.
    float adj;
    //placeholder for specific age related step value.
    float cstep;
    //value converter for step value.
    int step;

    if (age >= 30) {
        cstep = (age - 2) / 2;
        step = cstep;
    };
    //adding .1 to adjustment size up to the step maximum step value.
    for (int a = 0; a < step; a++)
        adj += 0.1;

    //final calculation formula for waist adjustment size.
    float retVal = (weight / 5.7) + adj;
    return retVal;
}
