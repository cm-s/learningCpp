#include <fstream>
#include <iostream>
using namespace std;

int main ()
{
   ofstream outfile;
   outfile.open("file.dat", ios::out | ios::in);

   return 0;
}
