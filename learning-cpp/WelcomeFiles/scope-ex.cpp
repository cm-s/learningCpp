/*
 * Scope Example
 * C. Pacheco
 */

#include <string>
#include <iostream>
using namespace std;

int main ()
{
	int val1 = 1;
	bool tf = true;
	
	while (tf == true){
	    cout << val1 << endl;
	    int val2 = 2;
	    cout << val2 << endl;
	    while (tf == true){
	        cout << val2 << endl;
	        int val3 = 3;
	        cout << val3 << endl;
	        tf = false;
	    }
	    //cout << val3 << endl;
	}
	//cout << val2 << endl;
	cout << val1 << endl;
	return 0;

}

/*
-> 1
-> 2
-> 2
-> 3
-> 1
*/