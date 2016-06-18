#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class InputReader
{
public:
    string input_type;
    string input_type_string;
    string input_type_int;
    string input_type_bool;
    string input_type_char;
    string input_type_float;
    string input_type_double;
    /**
     * Most basic input constructor. Properly calls appropriate function depending on the type of input
     * in it's parameter field.
     * All parameters are set with raw data in the form of a string.
     *
     * @param the type of input to be processed.
     */
    void input_constructor(string input_type);
    /**
     * The more complex input constructor.Properly calls appropriate function depending on the type of input that is in it's
     * first parameter field with the use of setting child function to return specific values defined in the second parameter field.
     * All parameters are set with raw data in the form of a string.
     *
     * @param input type to be processed.
     * @param desired values for the user to input.
     */
    void input_constructor(string input_type, string options);
    /**
     * function for handling string-type input.
     *
     * @param designated variable for string input collected by the user.
     * @param raw array of acceptable inputs.
     */
    void string_handle(string& input_type_string, vector<char> accepted_inputs);
    /**
     * function for handling intager-type input.
     *
     * @param designated variable for storing intager input by the user.
     */
    void intager_handle(string& input_type_int);
    /**
     * function for handling boolean input.
     *
     * @param designated variable for storing boolean input from the user.
     */
    void boolean_handle(string& input_type_bool);
    /**
     * function for handling input from the user that is a single character only.
     *
     * @param designated variable for storing input from the user that consists of a simple intager.
     */
    void character_handle(string& input_type_char);

    string insert_string() { return returningString; };
    int insert_intager() { return returningIntager; };
    bool insert_boolean() { return returningBoolean; };
    char insert_character() { return returningCharacter; };
    float insert_floatPoint() { return returningFloatingPoint; };
    double inser_doubleInt() { return returningDoubleInt; };
private:
    string* accepted_mchar_inputs;
    char* accepted_char_inputs;

    string returningString;
    int returningIntager;
    bool returningBoolean;
    char returningCharacter;
    float returningFloatingPoint;
    double returningDoubleInt;
};
