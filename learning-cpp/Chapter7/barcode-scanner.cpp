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
#include <inttypes.h>

using namespace std;

/*
 * zipCode
 * Class containing values for binary and encoded values to be returned in main.
 * Class also contains functions for the cross conversion of the values previously stated.
 */
class zipCode//I wonder how to properly document classes...
{
public:
    string binary;
    int numcode;

    /**
     * Encodes twenty seven digit binary list or "barcode".
     *
     * @param input barcode to be encoded.
     */
    void binEncode(string input, zipCode code);
    /**
     * Decodes five digit code.
     *
     * @param input code to be decoded.
     */
    void numDecode(string input, zipCode code);
};

int main()
{
zipCode code;
//varaible holding value for the user's input.
string input;
//requesting input from the user. Storing in input.
cout << "Input a barcode or a five digit number.";
cin >> input;
//Filtering input to it's respective aspect type in zipCode.
if (input.length() == 27) {
    code.binary = input;
    code.binEncode(input, code);
} else {
    int input_assigner;
    for (size_t l = 0; l < 27; l++) {
        input_assigner += (int) input[l];
    };
    code.numcode = input_assigner;
    code.numDecode(input, code);
};
return 0;
};

void binEncode(string input, zipCode code) {
    //creating variable to represent the size of the input.
    int size = sizeof(input)/sizeof(input[0]);
    //list representing seperated individual bits.
    char plist[27];
    //at first, this is the list representing seperated groups of processed binary values.
    //at the end of the for loop, at the end of this scope, this list represents all processed values.
    int bitlst[5];
    //variable representing output of final encoded barcode.
    int finOut[5];

    //loop seperating input binary list into an array. Storing seperated values in plist.
    for (size_t it = 0; it < size; it++)
        plist[it] += input[it];

    //removing the digits "1" on either side of plist.
    delete &plist[0];
    delete &plist[26];

    int size_p = sizeof(plist)/sizeof(plist[0]);
    //splitting remaining list into groups of five. Appening groups to bitlst.
    for (size_t dig = size_p; dig >= 0; dig -5) {
        for (int i = (dig -5); i <= dig; i++)
            bitlst[i] = (int) plist[i];
    };

    //looping through groups in bitlst.
    for (size_t itemCount = 0; itemCount < 5; itemCount++) {

        //looping through individual digits in the given group. Processing them according to place value.
        for (size_t d = 0; d < itemCount; d++) {
            switch(d) {
				case 0:
					bitlst[d] *= 7;
					break;
				case 1:
				    bitlst[d] *= 4;
				    break;
				case 2:
				    bitlst[d] *= 2;
				    break;
				case 3:
				    bitlst[d] *= 1;
				    break;
				case 4:
				    bitlst[d] *= 0;
                    break;
			};

        //looping through individual digits in the newly processed group.
        //sequentially adding each digit to the next one in the sequence.
        //storing newly added values in finOut.
        for (size_t d = 0; d < itemCount; d++)
            finOut[d] = bitlst[d];

        /*//rewriting each group in bitlst with the single digit processed value sums.
        bitlst = finOut;*///don't think I need this line.

        //concenating all processed values in bitlst and storing in numcode aspect of zipCode.
        int input_assigner;
        for (size_t dg = 0; dg < 5; dg++) {
            input_assigner += (int) bitlst[dg];
        };
        code.numcode = input_assigner;
        };
    };

};

void numDecode(string input, zipCode code) {
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

    cout << "1" << byteList << "1";
    /*string input_assigner[27];
    input_assigner[0] = '1';
    input_assigner.append((string) byteList);
    input_assigner[26] = '1';
    code.binary = input_assigner;*/
};
