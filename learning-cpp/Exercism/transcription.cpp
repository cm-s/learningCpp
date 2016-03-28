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
    cout << "\nThis string can only be comprised of capital letters A, C, U, G or T.";
    cin >> user_input;

    char gene;//try to "switch(case)" with this
    strcat(gene, user_input)

    do {
        for (int wd = 0; wd == strlen(gene); wd++) {
            if (isalnum(user_input[wd]) == true) {
                is_valid = false;
            };

            switch (user_input[wd]) {
                case "A":
                    continue;
                    break;
                case "C":
                    continue;
                    break;
                case "U":
                    continue;
                    break;
                case "G":
                    continue;
                    break;
                case "T":
                    continue;
                    break;
                default:
                    cout << "Err: This input is not valid.";
                    is_valid = false;
                    break;
            };
        };
    } while(is_valid != false);

return 0;
}

char convert_gene(char main_input) {
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
