/*
 * barcode-scanner
 * Decodes a binary barcode or encodes a five digit intager input by the user
 *
 * Charles Stevens
 * Date created: 3/1/16
 */

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/*
 * zipCode
 * Class containing values for binary and encoded values to be returned in main.
 * Class also contains functions for the cross conversion of the values previously stated.
 */
class zipCode//I wonder how to properly document classes...
{
public:
    int binary;
    int numcode;
private:
    /**
     * Encodes twenty seven digit binary list or "barcode".
     *
     * @param input barcode to be encoded.
     */
    void binEncode(string input);
    /**
     * Decodes five digit code.
     *
     * @param input code to be decoded.
     */
    void numDecode(string input);
}

int main()
{
//varaible holding value for the user's input.
string input;
//requesting input from the user. Storing in input.
cout << "Input a barcode or a five digit number.";
cin >> input;
//Filtering input to it's respective aspect type in zipCode.
if (input.length() == 27)
    zipCode::binary = input;
else
    zipCode::numcode = input;

return 0;
}

void binEncode(string input) {
    //creating variable to represent the size of the input.
    int size = sizeof(input)/sizeof(input[0]);
    //list representing seperated individual bits.
    char plist[27];
    //at first, this is the list representing seperated groups of processed binary values.
    //at the end of the for loop, at the end of this scope, this list represents all processed values.
    int bitlst[5];
    //variable representing output of final encoded barcode.
    int finOut;

    //loop seperating input binary list into an array. Storing seperated values in plist.
    for (size_t it = 0; it < size; it++)
        plist += input[it];

    //removing the digits "1" on either side of plist.
    plist.erase(0);
    plist.erase(plist.length() -1);

    //splitting remaining list into groups of five. Appening groups to bitlst.
    for (size_t dig = plist.length(); dig >= 0; dig -5) {
        int temp[];
        for (int i = (dig -5); i < dig; i++)
            temp.append(pList(i));
        bitlst.append(temp.join())//Is the .join statement doing what I want... I don't think so
    };

    //looping through groups in bitlst.
    for (size_t item = 0; item < bitlst.length(); item++) {

        //looping through individual digits in the given group. Processing them according to place value.
        for (size_t d = 0; d < item; d++) {
            switch(d) {
				case 0:
					item[d] *= 7;
					break;
				case 1:
				    item[d] *= 4;
				    break;
				case 2:
				    item[d] *= 2;
				    break;
				case 3:
				    item[d] *= 1;
				    break;
				case 4:
				    item[d] *= 0;
                    break;
			};
        };

        //looping through individual digits in the newly processed group.
        //sequentially adding each digit to the next one in the sequence.
        //storing newly added values in finOut.
        for (size_t d = 0; d < item; d++)
            finOut += item[d +1];

        //rewriting each group in bitlst with the single digit processed value sums.
        item = finOut;

        //concenating all processed values in bitlst and storing in numcode aspect of zipCode.
        zipCode.numcode = bitlst.join();
    };

};

void numDecode(string input) {
	//placeholder for binary digit groups
	char byteList[25];
    //creating variable to represent the size of the input.
    int size = sizeof(input)/sizeof(input[0]);

    //looping through each character in input code. Adding to diglst.
    for (size_t p = 0; p < size; p++) {

		//adding binary translations to list depending on what value the digit has.
		//appending respective translation to byteList.
		switch(p) {
			case 9:
				strcat(byteList, "10100");
				break;
			case 8:
				strcat(byteList, "10010");
				break;
			case 7:
				strcat(byteList, "01110"); //10000 is an alternate value that is equal to seven
				break;
			case 6:
				strcat(byteList, "01100");
				break;
			case 5:
				strcat(byteList, "01010");
				break;
			case 4:
				strcat(byteList, "01000");
				break;
			case 3:
				strcat(byteList, "00110");
				break;
			case 2:
				strcat(byteList, "00100");
				break;
			case 1:
				strcat(byteList, "00010");
				break;
		};
    };
	//not sure if doing this is legal
	zipCode.binary = "1" << byteList.join() << "1";
};
