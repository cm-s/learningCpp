/*
 * adv_game (alpha)
 * Adventuring game in which a player tarverses a retro-style board or grid, solving pizzles and avoiding enmeies
 * in order to get to the next level and ultimately win the game.
 *
 * CMS
 * Date originally created: 4-26-16, 10:41am
 */
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include "external/objs.h"
#include "external/console_reader.h"
using namespace std;

class MainFrameElement
{
public:
    const char cave[5][5] = {
        {'#','#','#','#','#'},
        {'#','^',' ',' ','#'},
        {'#','#','#',' ','#'},
        {'#','^',' ',' ','#'},
        {'#','#','#','_','#'},
    };
    const char boulder[5][5] = {
        {' ','#','#','#',' '},
        {'#','#','#','#','#'},
        {'#','#','^','W','W'},
        {'#','#','^','#','#'},
        {' ','#','#','#',' '},
    };
    char levelTwo[20][20] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '?', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '@', '#', ' ', ' ', ' ', '#'},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'T', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '@', '#', '#', '#', '#', ' '},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' '},
        {' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', 'X', ' ', '#', '#', ' ', ' ', ' ', ' ', '+', '+', '+', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '},
    };
    char levelThree[20][20] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', '?', '#', '^', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '/', 'H', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', 'X', '#'},
        {'#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '*', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    char levelFour[20][20] = {
        {'#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#'},
        {'#', '[', ' ', ']', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'X', ' ', '#', '+', '+', '#', ' ', ' ', 'E', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '_', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '@', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '/', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '8', '=', '='},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ', 'H', '#', ' ', ' ', ' ', ' ', '8', '=', '='},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '8', '=', '='},
        {'#', '#', '#', '#', '#', '#', '#', 'B', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' '},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '-', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '?', ' ', ' ', '[', ' ', ']', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#'},
        {' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' '},
    };
    char current_grid[20][20] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'X', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };
    char invisibles[1] = { {'?'} };
    CMSTD cmstd;
    void makeSpace() {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    };
    /**
     * display_grid
     *
     * Generic method that will print all elements of a grid specified in the first parameter.
     *
     * @param the grid that will be printed. Always the current_grid.
     *
     */
    void display_grid(char current_grid[20][20]) {
        for (size_t row =0; row <= (19); row++) {
            for (size_t col =0; col <= (19); col++) {
                if (current_grid[row][col] == '?') {
                    cout << "  ";
                } else {
                    cout << current_grid[row][col] << ' ';
                };
            };
            cout << endl;
        };
    };
    /**
     * generate
     *
     * A multidimensional loop, sequentially writing all data from a given structure
     * onto the current_grid.
     *
     * @param current_grid include, by which the data will be written.
     * @param model of the structure that will be written to the current_grid.
     * @param the seed, delimiting how much space will be skipped when the data write process begins.
     * @param size of the model, describing where the write process needs to end.
     *
     */
    void generate(char current_grid[20][20], const auto model, short int seed, short int size) {
        // Run a two dimensional loop, skipping all elements from the starting point (seed) of the srtucture
        // generation.
        for (size_t col = 0; col <= size; col++) {
            for (size_t row = 0; row < size; row++) { current_grid[col + seed][row + seed] = model[col][row]; };
        };
    };
};

/**
 * genRand
 *
 * Simple static function returning a random number that lies between two parameters.
 *
 * @param first number that will be the highest possible value.
 * @param second number that will be the lowest possible value.
 * @return the random number that has been generated.
 */
static int genRand(short int param1, short int param2) {
    srand(time(NULL));
    return rand() % param1 + param2;
};
/**
 * message_post_process
 *
 * Trivial function that will print a supplied message.
 * This function exists in order to properly display messages that are issued at different intervals during
 * game execution.
 *
 * @param msgCode being the variable holding the message to be printed.
 *
 */
static void message_post_process(string &msgCode) {
    cout << msgCode << endl;
    msgCode = "";
};

int main()
{
MainFrameElement MainFrame;
PLAYER character(10,10,'&');
NULL_ENTITY nullent;

// Setup level one
cout << "\nNarrator: Use the WASD keys to move your character. Press enter after each action.";
cout << "\nNarrator: Use the C key to enter a command." << endl;
ENEMY monster(3,3,'M');

// Generate the 'cave' structure on the first level with a fifty percent chance
if (genRand(2, 0)) {
    MainFrame.generate(MainFrame.current_grid, MainFrame.cave, genRand(12, 3), 5);
} else {
    MainFrame.generate(MainFrame.current_grid, MainFrame.boulder, genRand(12, 3), 5);
};

do {
    MainFrame.display_grid(MainFrame.current_grid);
    character.move();
    monster.autoMove(MainFrame.current_grid, character);
    MainFrame.makeSpace();
    character.object_reaction(MainFrame.current_grid, monster);
    message_post_process(character.msgCode);
    cout << "Degug: GameLevel:" << character.gameLevel << endl;
} while(character.gameLevel <= 1);

// Cleanup and setup level two.
do {
    MainFrame.display_grid(MainFrame.levelTwo);
    character.move();
    MainFrame.makeSpace();
    character.object_reaction(MainFrame.levelTwo, nullent);
    message_post_process(character.msgCode);
} while(character.gameLevel == 2);

// Cleanup and setup level three.
BOX box1(2, 5, 'H');
BOX box2(3, 8, 'H');
do {
    MainFrame.display_grid(MainFrame.levelThree);
    character.move();
    MainFrame.makeSpace();
    box1.checkif_pushed(MainFrame.levelThree, character);
    box2.checkif_pushed(MainFrame.levelThree, character);
    character.object_reaction(MainFrame.levelThree, nullent);
    message_post_process(character.msgCode);
} while(character.gameLevel == 3);

// Cleanup and setup level four
do {
    MainFrame.display_grid(MainFrame.levelFour);
    character.move();
    MainFrame.makeSpace();
    character.object_reaction(MainFrame.levelFour, nullent);
    message_post_process(character.msgCode);
} while(character.gameLevel == 4);

MainFrame.makeSpace();
cout << "Narrator: Congradulations. You beat the game." << endl;

return 0;

}
