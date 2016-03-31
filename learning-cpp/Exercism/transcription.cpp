/*
 * transcription
 * Converts a given DNA strand and returns it's compliment.
 *
 * Charles Stevens
 * Date created: 3/30/16
 */
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void convert_gene(string user_input, bool is_valid);

int main()
{
    //discovering input gene
    string user_input;
    bool is_valid;

    cout << "Enter your gene strand.";
    cout << "\nThis string can only be letters A, C, U, G or T." << endl;
    cin >> user_input;


    for (int wd = 0; wd < user_input.length(); wd++) {
        if (isalnum(user_input[wd]) == true) {
            is_valid = false;
        };

        switch (toupper(user_input[wd])) {
            case 'A':
                is_valid = true;
                break;
            case 'C':
                is_valid = true;
                break;
            case 'U':
                is_valid = true;
                break;
            case 'G':
                is_valid = true;
                break;
            case 'T':
                is_valid = true;
                break;
            default:
                cout << "Err: This input is not valid." << endl;
                is_valid = false;
                break;
        };
    };
    convert_gene(user_input, is_valid);

return 0;
}

void convert_gene(string user_input, bool is_valid) {
    string rnaCompliment;

    if (is_valid = true)
    {
    int gene_size = sizeof(user_input)/sizeof(user_input[0]);

    for (int itm = 0; itm <= gene_size; itm++) {
        //cout << "run";
        switch (toupper(user_input[itm])) {
            case 'G':
                rnaCompliment += 'C';
                break;
            case 'C':
                rnaCompliment += 'G';
                break;
            case 'T':
                rnaCompliment += 'A';
                break;
            case 'A':
                rnaCompliment += 'U';
                break;
            case 'U':
                rnaCompliment += 'T';
                break;
            };
        };
        cout << "The RNA compliment for your gene strand is " << rnaCompliment << "." << endl;
    };
};
