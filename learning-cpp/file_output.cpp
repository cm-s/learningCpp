#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main ()
{
    string lastName, firstName;

    //creating file in write mode(outfile mode) and input mode? I don't think so.
    ofstream valfile;
    valfile.open("valfile.dat");

    cout << "Enter the first and last name:";
    cin >> firstName;
    cin >> lastName;

    //storing vars value's in file.dat...Does this need to be seperate?
    valfile << firstName << endl;
    valfile << lastName << endl;

    ifstream outfile ("valfile.dat");
    string counter;
    while (getline(outfile,counter)) {
        cout << counter;
    };

    outfile.close();

    return 0;
}
