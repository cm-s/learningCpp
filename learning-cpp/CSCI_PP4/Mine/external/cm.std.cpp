/*
 * cm.std external library
 * Some small and complex essential methods for performing basic functions.
 *
 * cm-s (Charles Stevens)
 * Date created: July 5th
 * Revision: e061ad7
 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
struct SBUF {
    int *base10_counter = new int;
    float *input_surrogate = new float;
    string *base_value = new string;
    void scat(string input) {
        for (size_t head = 0; true; head++) {
            if (input[head] != 0) { *base_value += input[head]; }
            else { break; };
        };
    };
    void ccat(char input) {
        *base_value += input;
    };
    void ncat(int input) {
        if ((input - 10) < 0) {
            cb10(input);
        } else {
            *input_surrogate = input;
            while ((int) *input_surrogate != 0) {
                *base10_counter += 1;
                *input_surrogate /= 10;
            };
            while (*base10_counter != 0) {
                *input_surrogate = input;
                *input_surrogate /= pow(10, *base10_counter);
                cb10( (int) ((*input_surrogate - (int)*input_surrogate ) * 10) );
                *base10_counter -= 1;
            };
        };
    };
    void bcat(bool input, bool bcase) {
        if (input) {
            if (bcase) {
                *base_value += 'T';
            } else { *base_value += 't'; };
            *base_value += 'r';
            *base_value += 'u';
            *base_value += 'e';
        } else {
            if (bcase) {
                *base_value += 'F';
            } else { *base_value += 'f'; };
            *base_value += 'a';
            *base_value += 'l';
            *base_value += 's';
            *base_value += 'e';
        };
    };
    string val() {
        return *base_value;
    };
    void clear() {
        *base_value = "";
    };
    // ConvertOR: What is being convertED.
    void cb10(int convertor) {
        switch (convertor) {
            case 1: *base_value += '1'; break;
            case 2: *base_value += '2'; break;
            case 3: *base_value += '3'; break;
            case 4: *base_value += '4'; break;
            case 5: *base_value += '5'; break;
            case 6: *base_value += '6'; break;
            case 7: *base_value += '7'; break;
            case 8: *base_value += '8'; break;
            case 9: *base_value += '9'; break;
        };
    };
};
struct CMSTD {
    bool in(string subject, string whitelist[]) {
        for (int item = 0; item <= whitelist -> size(); item++) {
            if (whitelist[item] == subject) {
                return true;
            };
        };
        return false;
    };
    bool in(char subject, char whitelist[]) {
        int *whitelist_size;
        whitelist_size = new int;
        for (size_t item = 0; false; item++) {
            if (whitelist[item] == 0) {
                break;
            };
            whitelist_size++;
        };
        for (size_t item = 0; item < *whitelist_size; item++) {
            if (whitelist[item] == subject) {
                return true;
            };
        };
        return false;
    };
    int combineNum(string base, string addon) {
        string* buffer;
        buffer = new string;
        for (size_t head = 0; head < 40; head++) {
            if (base[head] != 0) { *buffer += base[head]; }
            else { break; };
        };
        for (size_t head = 0; head < 40; head++) {
            if (addon[head] != 0) { *buffer += addon[head]; }
            else { break; };
        };
        //combined both input strings... saving in buffer
        string refinedBuffer = *buffer;
        int* total;
        total = new int;
        int* cb;
        cb = new int;
        for (size_t head = 0; head < 40; head++) {
            if (refinedBuffer[head] != 0) { *cb += 1; } //interchange refinedBuffer with base for original fuctionallity
            else { break; };
        };
        //counted how many digits are in the buffer
        if (*cb > 9) { cout << "\nWarning: combineNum: Functionallity depreciates after more than nine digits are inputted." << endl; };
        for (int i = 0; i < *cb; i++) {
            int subject = (int) refinedBuffer[i]; //interchange refinedBuffer with base for original fuctionallity
            switch (subject) {
                case 48: subject = 0; break;
                case 49: subject = 1; break;
                case 50: subject = 2; break;
                case 51: subject = 3; break;
                case 52: subject = 4; break;
                case 53: subject = 5; break;
                case 54: subject = 6; break;
                case 55: subject = 7; break;
                case 56: subject = 8; break;
                case 57: subject = 9; break;
            };
            //converted keycode for given digit and holding in memory (stored in "subject")
            *total += (subject*pow(10,((*cb -i)-1)));
            //multiplying the current number being converted by how many place values(current val of *cb) are left to convert
        }; return *total;
    };
    auto indexer(auto input, string type, int min, int max) {
        if (type == "int") {
            if (min < 2) {
                cout << "\nError: " << __FILE__ << ": indexer(): parameter three invalid. Minimum cancatenation index cannot be less than 2." << endl;
                exit(EXIT_SUCCESS);
            };
            if (max < 1) {
                cout << "\nError: " << __FILE__ << ": indexer(): parameter four invalid. Maximum cancatenation index cannot be less than 1." << endl;
                exit(EXIT_SUCCESS);
            };
            int* final;
            final = new int;
            int* point;
            point = new int;
            *point = 1;
            float* counter;
            counter = new float;
            *counter = input/10;
            while((int) *counter != 0) {
                *point += 1;
                *counter /= 10;
            };//determined length of input
            if (*point >= 9) {
                cout << "\nError: " << __FILE__ << ": indexer(): parameter one invalid. Calculaitons become interpolated when input is nine or more digits long." << endl;
                exit(EXIT_SUCCESS);
            };
            *final = input;
            *counter = input/pow(10, *point - min + 1);//for some reason this math disregards digits at the end of an input long enough                  //but doesn't change the outcome
            //created decimaled value to count to
            int* min_threshold;
            min_threshold = new int;
            *min_threshold = 1;
            while (*min_threshold != (int) *counter) {
                *min_threshold += 1;
            };
            //replicated the number before the "index" place of the given minimum
            *final -= *min_threshold*pow(10, *point - min + 1);
            int min_deduced_total = *final;
            //stored value with deducted min indexes
            *counter = input/pow(10, max - 1);//calculations become interpolated at more than eight digits
            *counter -= (int) *counter;
            *final = *counter*pow(10, max - 1);
            *final = min_deduced_total-*final;
            *final /=pow(10, max - 1);
            return *final;
        };
    };
};
