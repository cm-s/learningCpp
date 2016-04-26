/*
 * adv_game (v1.0.1)
 * Adventuring game in which a player tarverses a retro-style board or grid, solving pizzles and avoiding enmeies
 * in order to get to the next level or win the game.
 *
 * CMS
 * Date created: 4-26-16, 10:41am
 */
#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <stdlib.h>
using namespace std;

class item
{
public:
    string id = "00";
    short int getKey() { return key; };
    void setKey(int value) { key = value; };
private:
    short int key;
};

class player
{
public:
    bool firstPlay = true;
    int x = 10;
    int y = 10;
    char skin = '&';
    int prev_x_coord;
    int prev_y_coord;
    double life = 500;
    int level = 1;
    item keeper1key;
    item keeper2Key;
    string gateSignature;
};

class lock
{
public:
    int key;
    int x, y;
    char skin = '@';
    string gateSignature;
    void detect(char current_grid[20][20], player& character) {
        if (x == character.x && y == character.y) {
            cout << "\nIt looks like you can insert a key." << endl;
            cout << "\nThe Number on the lock says: " << key << endl;
            character.x = character.prev_x_coord;
            character.y = character.prev_y_coord;
            character.gateSignature = gateSignature;
        };
    };
    void unlock(char current_grid[20][20], player& character) {
        if (character.gateSignature == "32") {
            if (key == character.keeper1key.getKey()) {
                current_grid[x][y] = '%';
                x = 0; y = 0;
            };
        } else if (character.gateSignature == "23") {
            if (key == character.keeper2Key.getKey()) {
                current_grid[x][y] = '%';
                x = 0; y = 0;
            };
        };
    };
};

/*Random functions*/

int flip(); int flip() { return rand() %2; };
int randomCell(); int randomCell() { return rand() % 19 + 3; };

void item_pickup(player& character, char current_grid[20][20], int grid_size, bool& gameOver);

void gen_struct(char current_grid[20][20],  int grid_size, const char templateStruct[5][5]);

void display_grid(char current_grid[20][20], int grid_size);

void character_dynamic_low_level(char current_grid[20][20], int grid_size, player &character, char move_direction, bool& gameOver);

void character_dynamic(char current_grid[20][20], int grid_size, player &character, char move_direction, bool& gameOver, lock gatekeeper1, lock gatekeeper2);

void levelConstruct(const char level[20][20], char current_grid[20][20]);

void make_space();

void action_input(player& character, char move_direction);

void action_input(char current_grid[20][20], player& character, lock& gatekeeper1, lock& gatekeeper2, char move_direction);

void gate_check(char current_grid[20][20], player& character, lock gatekeeper1, lock gatekeeper2);

void movement_handler(char current_grid[20][20], player& character, int grid_size, char& move_direction, bool& gameOver);

/*BEGIN MAIN*/

int main()
{
/*INITIALIZING BEGIN*/

//grid imports
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
const char initial_grid[20][20] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
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
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};
const char levelTwo[20][20] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '@', '=', '=', '@', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', 'G', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', 'X', ' ', ' ', ' ', '#', ' ', ' ', ' ', 'G', 'G', 'G', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
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
//non-grid variables
const int grid_size = 20;
char move_direction;
bool gameOver = false;
short int game_level = 1;

/*INITIALIZING END*/

gen_struct(current_grid, grid_size, cave);//generating structure
player character;//init player

cout << "\nUse the WASD keys to move your character.";
cout << "\nUse the C key to enter a command." << endl;
move_direction = 'w';
do {
    character.prev_x_coord = character.x;
    character.prev_y_coord = character.y;
    if (character.firstPlay == false) {
        make_space();
    };
    character.firstPlay = false;
    action_input(character, move_direction);
    movement_handler(current_grid, character, grid_size, move_direction, gameOver);
} while(gameOver == false);


    //setup level two
    move_direction = 's';
    gameOver = false;
    character.firstPlay = true;
    levelConstruct(levelTwo, current_grid);
    game_level = 2; character.level = 2;

    lock gatekeeper1; gatekeeper1.x = 11; gatekeeper1.y = 16;
    gatekeeper1.key = 323; gatekeeper1.gateSignature = "32";
    lock gatekeeper2; gatekeeper2.x = 11; gatekeeper2.y = 13;
    gatekeeper2.key = 232; gatekeeper2.gateSignature = "23";
    current_grid[gatekeeper1.x][gatekeeper1.y] = gatekeeper1.skin;
    current_grid[gatekeeper2.x][gatekeeper2.y] = gatekeeper2.skin;

    do {
        character.prev_x_coord = character.x;
        character.prev_y_coord = character.y;
        make_space();
        if (character.firstPlay == true) {
            cout << endl; cout << "Level Two" << endl;
        };
        character.firstPlay = false;
        action_input(current_grid, character, gatekeeper1, gatekeeper2, move_direction);
        gate_check(current_grid, character, gatekeeper1, gatekeeper2);
        movement_handler(current_grid, character, grid_size, move_direction, gameOver);
        //above function ends with stack smashing as of versions under 1.0.1. Newest errors below.
        /* *** Error in `./a.out': double free or corruption (out): 0x00007ffc30ce8c90 *** Aborted (core dumped) */
        /* *** Error in `./a.out': munmap_chunk(): invalid pointer: 0x00007ffdd6f71920 *** Aborted (core dumped) */
    } while(gameOver == false);
    //cleaning up for level three
    delete &gatekeeper1; delete &gatekeeper2;
        //level three code will go here


return 0;
};

/*END OF MAIN*/

void display_grid(char current_grid[20][20], int grid_size) {
    for (size_t row =0; row <= (grid_size -1); row++) {
        for (size_t col =0; col <= (grid_size -1); col++) {
            cout << current_grid[row][col] << ' ';
        };
        cout << endl;
    };
};

void gen_struct(char current_grid[20][20], int grid_size, const char templateStruct[5][5]/*use templateStruct class for dynamic size*/) {
    int rnum = randomCell();
    //looping though the template and setting values to corresponding grid cells (plus random)
    for (size_t col = 0; col < 5; col++) {
        for (size_t row = 0; row < 5; row++) {
            current_grid[rnum +col][rnum +row] = templateStruct[col][row];
        };
    };
};

void item_pickup(player& character, char current_grid[20][20], int grid_size, bool& gameOver) {
    int printk;
    switch(current_grid[character.x][character.y]) {
        case '^':
            if (flip() == 0 && character.keeper1key.id != "32") {
                character.keeper1key.setKey(323);
                character.keeper1key.id = "32";
                printk = 323;
            } else {
                character.keeper2Key.setKey(232);
                character.keeper2Key.id = "23";
                printk = 232;
            };
            cout << "\nYou found a key. The number " << printk << " is on it." << endl;
            break;
        case 'X':
            cout << "\nYou've won the game!" << endl;
            gameOver = true;
            break;
    };
};

void levelConstruct(const char level[20][20], char current_grid[20][20]) {
    for (size_t col = 0; col <= 20; col++) {
        for (size_t row = 0; row < 20; row++) {
            current_grid[col][row] = level[col][row];
        };
    };
};

void make_space() {
    for (size_t space = 0; space <= 15; space++) {
        cout << endl;
    };
};

void action_input(char current_grid[20][20], player& character, lock& gatekeeper1, lock& gatekeeper2, char move_direction) {
    string command;
    switch (toupper(move_direction)) {
        case 'W':
            character.x -= 1;
            break;
        case 'A':
            character.y -= 1;
            break;
        case 'S':
            character.x += 1;
            break;
        case 'D':
            character.y += 1;
            break;
        case 'C':
            cout << endl; cout << endl; cout << endl;
            cout << "\nEnter an action: " << endl;
            cin >> command;
            if (command == "unlock") {
                if (character.gateSignature == "32") {
                    gatekeeper1.unlock(current_grid, character);
                } else if (character.gateSignature == "23") {
                    gatekeeper2.unlock(current_grid, character);
                };
            } else {
                cout << "\nThat is not a command." << endl;
            };
            break;
        default:
            cout << "\nThat is not a move." << endl;
            break;
    };
};

void action_input(player& character, char move_direction) {
    switch (toupper(move_direction)) {
        case 'W':
            character.x -= 1;
            break;
        case 'A':
            character.y -= 1;
            break;
        case 'S':
            character.x += 1;
            break;
        case 'D':
            character.y += 1;
            break;
        default:
            cout << "\nThat is not a move.";
            break;
    };
};

void gate_check(char current_grid[20][20], player& character, lock gatekeeper1, lock gatekeeper2) {
    if (current_grid[character.x][character.y] == '@') {//maybe repalce the "if()" with a single function later
        if ((character.x == gatekeeper1.x) && (character.y == gatekeeper1.y)) {
            gatekeeper1.detect(current_grid, character);
        } else {
            gatekeeper2.detect(current_grid, character);
        };
    };
};

void movement_handler(char current_grid[20][20], player& character, int grid_size, char& move_direction, bool& gameOver) {
    if (current_grid[character.x][character.y] == '#') {
        cout << "\nYou cannot move here." << endl;
        character.x = character.prev_x_coord;//settings player to previous coords (before moved into a wall)
        character.y = character.prev_y_coord;
        display_grid(current_grid, grid_size);
        cin >> move_direction;
    } else {
        item_pickup(character, current_grid, grid_size, gameOver);
        current_grid[character.x][character.y] = character.skin;
        //printing grid again
        display_grid(current_grid, grid_size);
        //replacing last cell that the character was in
        current_grid[character.x][character.y] = ' ';
        cin >> move_direction;
    };
};
