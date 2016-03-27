#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main ()
{
    string lastName, firstName;

    //creating file in write mode(outfile mode) and input mode?
    ofstream outfile;
    outfile.open("file.dat", ios::out | ios::in);

    cout << "Enter the first and last name:";
    cin >> firstName;
    cin >> lastName;

    //storing vars value's in file.dat...Does this need to be seperate?
    outfile << firstName << endl;
    outfile << lastName << endl;

   return 0;
}
