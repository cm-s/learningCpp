#include <iostream>
#include <string>
#include <cstring>
using namespace std;

char convert_gene(char main_input);

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
                is_valid = false;
                break;
            case 'C':
                is_valid = false;
                break;
            case 'U':
                is_valid = false;
                break;
            case 'G':
                is_valid = false;
                break;
            case 'T':
                is_valid = false;
                break;
            default:
                cout << "Err: This input is not valid.";
                is_valid = false;
                break;
        };
    };

return 0;
} //blocks here and up run
/*
char convert_gene(char main_input) {
    gene_size = sizeof()

    for (size_t itm = 0; itm < strlen(main_input); itm++) {
        switch (main_input[itm]) {
            case 'g':
                main_input[itm] = 'c';
                break;
            case 'c':
                main_input[itm] = 'G';
                break;
            case 'T':
                main_input[itm] = 'A';
                break;
            case 'A':
                main_input[itm] = 'U';
                break;
        };
    };

    return main_input;
}
*/
