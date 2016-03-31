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

    cout << "Enter your gene string.";
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
    if (is_valid = true)
    {
    int gene_size = sizeof(user_input)/sizeof(user_input[0]);

    for (int itm = 0; itm <= gene_size; itm++) {
        switch (user_input[itm]) {
            case 'G':
                user_input[itm] = 'C';
                break;
            case 'C':
                user_input[itm] = 'G';
                break;
            case 'T':
                user_input[itm] = 'A';
                break;
            case 'A':
                user_input[itm] = 'U';
                break;
            };
        };
        cout << user_input;
    };
};
