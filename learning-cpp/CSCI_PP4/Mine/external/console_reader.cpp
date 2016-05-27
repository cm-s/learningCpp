
#include "console_reader.h"

void InputReader::input_constructor(string input_type) {
    if (input_type == "string") {
        string_handle(input_type_string, NULL);
    } else if (input_type == "int") {
        intager_handle(input_type_int);
    } else if (input_type == "bool") {
        boolean_handle(input_type_bool);
    } else if (input_type == "char") {
        character_handle(input_type_char);
    } else {
        cout << "\nError: ConsoleReader: Invalid input type in parameter field" << endl;
    };
};

void InputReader::input_constructor(string input_type, string options) {
    if (input_type == "string") {
        accepted_mchar_inputs = new string[sizeof(options)];
        int* count;
        count = new int;
        for (size_t item = 0; item < options.size(); item++) {
            if (options[item] == ' ') { *count += 1; }
            else { accepted_mchar_inputs[*count][item] = options[item]; };//error happens here... deleting is increasingly impossible
        };
        string_handle(input_type, accepted_mchar_inputs);
    } else if (input_type == "int") {
        for (size_t item = 0; item < options.size(); item++) {
            /* code */
        };
    }  else if (input_type == "char") {
        for (size_t item = 0; item < options.size(); item++) {
            /* code */
        };
    } else {
        cout << "\nError: ConsoleReader: Invalid input type for first parameter" << endl;
    };
};

void InputReader::string_handle(string& input_type_string, string* accepted_mchar_inputs) {
    cin >> input_type_string;
    if (input_type_string.size() <= 1) {
        bool* is_char;
        is_char = new bool;
        *is_char = true;
        while (*is_char == 1) {
            cout << "\nPlease enter a word, a string containing more than one character or a sentence." << endl;
            cin >> input_type_string;
            if (input_type_string.size() > 1) { *is_char = false; };
        };
    } else {
        bool* containsDigit;
        containsDigit = new bool;
        *containsDigit = false;
        do {
            for (size_t index = 0; index <= sizeof(input_type_string); index++) {
                if (isdigit(input_type_string[index]) != false) { *containsDigit = true; break; }
                else { *containsDigit = false; };
            };
            if (*containsDigit == 1) {
                cout << "\nPlease do not include any numbers in your input" << endl;
                cin >> input_type_string;
            };
        } while (*containsDigit == 1);
    };
    if (accepted_mchar_inputs != NULL) {
        short int* chances;
        chances = new short int;
        *chances = accepted_mchar_inputs -> size();
        for (size_t index = 0; index < accepted_mchar_inputs -> size(); index++) {
            if (input_type_string != accepted_mchar_inputs[index]) { *chances -= 1; };
            if (*chances == 0) {
                cout << "\nPlease enter";
                for (size_t item = 0; item < accepted_mchar_inputs -> size(); item++) {
                    if ((item % accepted_mchar_inputs -> size()) == 1) { cout << "or " << accepted_mchar_inputs[item] << '.'; };
                    cout << accepted_mchar_inputs[item] << ", ";
                };
                break;
            };
        };
    };
    returningString = input_type_string;
};

void InputReader::intager_handle(string& input_type_int) {
    cin >> input_type_int;
    bool* has_achar;
    has_achar = new bool;
    *has_achar = false;
    do {
        for (size_t d = 0; d < input_type_int.size(); d++) {
            if (isalpha(input_type_int[d])) { *has_achar = true; break; }
            else { *has_achar = false; };
        };
        if (*has_achar == 1) {
            cout << "\nPlease enter one number only, without any letters in it" << endl;
            cin >> input_type_int;
        };
    } while (*has_achar == 1);
    returningIntager = stoi(input_type_int);
};

void InputReader::boolean_handle(string& input_type_bool) {
    cin >> input_type_bool;
    bool* valid;
    valid = new bool;
    *valid = false;
    do {
        if (input_type_bool.size() > 1) { cout << "\nPlease enter \"y\" or \"n\"" << endl; };
        if (tolower(input_type_bool[0]) == 'y') { *valid = true; break; } else { cin >> input_type_bool; };
    } while(*valid == 0);
    //inputting returng value later
};

void InputReader::character_handle(string& input_type_char) {
    cin >> input_type_char;
    bool* is_valid;
    is_valid = new bool;
    *is_valid = true;
    do {
        if (isalnum(input_type_char[0])) {
            cout << "\nPlease enter a single character, not a number" << endl;
            *is_valid = false;
            cin >> input_type_char;
        };
        if (input_type_char.size() > 1) {
            cout << "\nPlease enter a single character" << endl;
            *is_valid = false;
            cin >> input_type_char;
        } else if (*is_valid == 1) { break; };
    } while(*is_valid == 0);
    returningCharacter = input_type_char[0];
};
