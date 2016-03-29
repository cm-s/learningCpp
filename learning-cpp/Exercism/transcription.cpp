#include <iostream>
#include <string>
#include <cstring>
using namespace std;

char convert_gene(char user_input);

int main()
{
    //discovering input gene
    bool is_valid;
    string user_input;
    char gene_creation[0] = {};

    cout << "Enter your gene string.";
    cout << "\nThis string can only be comprised of capital letters A, C, U, G or T.";
    cin >> user_input;

    for (size_t it = 0; it < user_input.length(); it++) {
        strcat(gene_creation, "0");
    };

    do {
        for (int wd = 0; wd == user_input.length(); wd++) {
            if (isalnum(user_input[wd]) == true) {
                is_valid = false;
            };

            switch (user_input[wd]) {//breaking for good practice
                case 'A':
                    continue;
                    break;
                case 'c':
                    continue;
                    break;
                case 'U':
                    continue;
                    break;
                case 'G':
                    continue;
                    break;
                case 'T':
                    continue;
                    break;
                default:
                    cout << "Err: This input is not valid.";
                    is_valid = false;
                    break;
            };
        };
    } while(is_valid != true);

    /*This tidbit shows output revealing that is_valid isn't set right
    somewhere in the program and does not function as designed.*/
    return is_valid;//delete

return 0;
} //blocks here and up run but do not return the desired values
/*one occuring output of this code is "*** stack smashing detected ***".
this could possibly be due to the gene_creation array size being preset to
zero and "leaglly" having multiple values concatinated onto it.*/

/*this code has never been tested in harmony with the code above*/
char convert_gene(char user_input) {
    char converted_gene = user_input;

    for (int itm = 0; itm == strlen(user_input); itm++) {

        switch (converted_gene) {
            case 'G':
                strcpy(converted_gene[itm], 'C');
                break;
            case 'C':
                strcpy(converted_gene[itm], 'G');
                break;
            case 'T':
                strcpy(converted_gene[itm], 'A');
                break;
            case 'A':
                strcpy(converted_gene[itm], 'U');
                break;
        };
    };

    return converted_gene;
}
