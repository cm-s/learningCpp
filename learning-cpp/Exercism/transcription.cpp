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

    cout << "Enter your gene string.";
    cout << "\nThis string can only be comprised of capital letters A, C, U, G or T.";
    cin >> user_input;

    /*you should need to store temporary values in a placeholder
    for legal operation on in the convert_gene function. This is
     only a problematic and theoretical solution.*/

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
    } while(is_valid != false);

return 0;
} //blocks here and up run

/*the "user_input" below can only be seen as an empty string/char, thus
breaking the code below. There is apparently no workaround(as expected).*/
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
