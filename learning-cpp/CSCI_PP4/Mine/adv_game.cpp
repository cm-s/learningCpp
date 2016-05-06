/*
 * adv_game (v3.5.2)
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
#include "external/player_enemy.h"
using namespace std;

class lock
{
public:
    int key;
    int x, y;
    int extX, extY;
    char skin = '@';
    string gateSignature;
    bool unlocked = false;
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
        if (key == character.keeper1key.getKey()) {
            current_grid[x][y] = '%';
            unlocked = true;
            x = 0; y = 0;
        };
        if (key == character.keeper2Key.getKey()) {
            current_grid[x][y] = '%';
            unlocked = true;
            x = 0; y = 0;
        };
    };
};

class box
{
public:
    int x, y;
    char approach;
    void move() {
        if (approach == 'l') { y += 1; };
        if (approach == 'r') { y -= 1; };
        if (approach == 'd') { x -= 1; };
        if (approach == 'u') { x += 1; };
    };
};

/*Random functions*/
int flip(); int flip() { return rand() %2; };
int randomCell(); int randomCell() { srand(time(NULL));
                                     return rand() % 13 + 4; };

void item_pickup(player& character, char current_grid[20][20], bool& gameOver, int keyring[10][2], int keySet, bool do_rand);

void gen_struct(char current_grid[20][20], const char templateStruct[5][5]);

void display_grid(char current_grid[20][20], int grid_size);

void levelConstruct(const char level[20][20], char current_grid[20][20]);

void make_space();

void action_input(player& character, char move_direction);

void action_input(char current_grid[20][20], player& character, lock& gatekeeper1, lock& gatekeeper2, char move_direction);

void gate_check(char current_grid[20][20], player& character, lock gatekeeper1, lock gatekeeper2);

void step(char current_grid[20][20], player& character, int grid_size, char& move_direction);

void obj_reset(char current_grid[20][20], player& character, int grid_size, char& move_direction, char client);

bool detected_in(char current_grid[20][20], player character, int LTstart, int area);

void is_alive(player character, bool& gameOver);

void enemy_action(char current_grid[20][20], enemy& MonsterOne, player& character);

char justify_move(char current_grid[20][20], player subject);

char deduct_approach(player character, box subject);

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
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', 'X', ' ', ' ', ' ', '#', ' ', ' ', ' ', '+', '+', '+', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};
const char levelThree[20][20] = {           /*fist key here*/
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', '^', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '/', 'H', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', '#'},
    {'#', ' ', ' ', ' ', '#', '#', ' ', ' ', 'H', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
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
int keyring[10][2] = {
    {323, 232}, {890, 208},
    {157, 176}, {225, 755},
    {114, 495}, {611, 815},
    {212, 311}, {732, 326},
    {985, 860}, {615, 524}
};
/*INITIALIZING END*/

gen_struct(current_grid, cave);//generating structure
player character;//init player


cout << "\nUse the WASD keys to move your character.";
cout << "\nUse the C key to enter a command." << endl;
move_direction = 'w';
enemy MonsterOne;
do {
    character.prev_x_coord = character.x;
    character.prev_y_coord = character.y;
    if (character.firstPlay == false) {
        make_space();
    };
    character.firstPlay = false;
    action_input(character, move_direction);
    if (detected_in(current_grid, character, 10, 3) == true) {//this block needs to be a function
        if (MonsterOne.entry != true) {
            MonsterOne.x = 4; MonsterOne.y = 4;
            current_grid[MonsterOne.x][MonsterOne.y] = MonsterOne.skin;
            MonsterOne.entry = true;
        };
    };
    if (justify_move(current_grid, character) == 'M') {
        MonsterOne.looseLife(current_grid, character);
        cout << "\nYou've hit the enemy!" << endl;
        obj_reset(current_grid, character, grid_size, move_direction, 'M');
    };
    enemy_action(current_grid, MonsterOne, character);
    is_alive(character, gameOver);
    if (justify_move(current_grid, character) == '#') {
        obj_reset(current_grid, character, grid_size, move_direction, '#');
    } else {
        item_pickup(character, current_grid, gameOver, keyring, 0, true);
        step(current_grid, character, grid_size, move_direction);
    };
} while(gameOver == false);

    //setup level two
    move_direction = 's';
    gameOver = false;
    character.firstPlay = true;
    levelConstruct(levelTwo, current_grid);
    game_level = 2;

    lock gatekeeper1; gatekeeper1.x = 11; gatekeeper1.y = 16; gatekeeper1.extX = 11; gatekeeper1.extY = 15;
    gatekeeper1.key = keyring[0][0]; gatekeeper1.gateSignature = std::to_string(keyring[0][0]).erase(0, 1);
    lock gatekeeper2; gatekeeper2.x = 11; gatekeeper2.y = 13; gatekeeper2.extX = 11; gatekeeper2.extY = 14;
    gatekeeper2.key = keyring[0][1]; gatekeeper2.gateSignature = std::to_string(keyring[0][1]).erase(0, 1);
    current_grid[gatekeeper1.x][gatekeeper1.y] = gatekeeper1.skin;
    current_grid[gatekeeper2.x][gatekeeper2.y] = gatekeeper2.skin;

    do {
        character.prev_x_coord = character.x;
        character.prev_y_coord = character.y;
        make_space();
        if (character.firstPlay == true) { cout << "\nLevel Two" << endl; };
        character.firstPlay = false;
        action_input(current_grid, character, gatekeeper1, gatekeeper2, move_direction);
        gate_check(current_grid, character, gatekeeper1, gatekeeper2);
        if (justify_move(current_grid, character) == '#') {
            obj_reset(current_grid, character, grid_size, move_direction, '#');
        } else if (justify_move(current_grid, character) == '=') {
            obj_reset(current_grid, character, grid_size, move_direction, '=');
        } else {
            item_pickup(character, current_grid, gameOver, keyring, 1, true);
            step(current_grid, character, grid_size, move_direction);
        };
    } while(gameOver == false);
        //cleaning up for level three

        move_direction = 'w';
        gameOver = false;
        character.firstPlay = true;
        levelConstruct(levelThree, current_grid);
        game_level = 3;

        gatekeeper1.x = 9; gatekeeper1.y = 4;
        gatekeeper1.key = keyring[1][0]; gatekeeper1.gateSignature = std::to_string(keyring[1][0]).erase(0, 1);
        current_grid[gatekeeper1.x][gatekeeper1.y] = gatekeeper1.skin;

        box box1; box1.x = 2; box1.y = 5; current_grid[box1.x][box1.y] = 'H';
        box box2; box2.x = 3; box2.y = 8; current_grid[box2.x][box2.y] = 'H';

        do {
            character.prev_x_coord = character.x;
            character.prev_y_coord = character.y;
            make_space();
            if (character.firstPlay == true) { cout << "\nLevel three" << endl; };
            character.firstPlay = false;
            action_input(current_grid, character, gatekeeper1, gatekeeper2, move_direction);
            gate_check(current_grid, character, gatekeeper1, gatekeeper2);
            if (justify_move(current_grid, character) == '/') {
                character.gateSignature = "dr";
                character.gateSignature += (char) character.x;
                character.gateSignature += (char) character.y;
                obj_reset(current_grid, character, grid_size, move_direction, '/');
            };
            if (justify_move(current_grid, character) == 'H') {
                if (character.x == box1.x) {
                    box1.approach = deduct_approach(character, box1);
                    box1.move();
                    current_grid[box1.x][box1.y] = 'H';//you aren't erasing the previous 'H'
                };
                if (character.x == box2.x) {
                    box2.approach = deduct_approach(character, box2);
                    box2.move();
                    current_grid[box2.x][box2.y] = 'H';
                };
            };
            if (justify_move(current_grid, character) == '#') {
                obj_reset(current_grid, character, grid_size, move_direction, '#');
            } else {
                item_pickup(character, current_grid, gameOver, keyring, 1, false);
                step(current_grid, character, grid_size, move_direction);
            };
        } while(gameOver == false);

        std::exit(EXIT_FAILURE);

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

void gen_struct(char current_grid[20][20], const char templateStruct[5][5]) {
    int posNum = randomCell();
    if (posNum > 13) {
        int minus = posNum % 13;
        posNum -= minus;
    };
    //looping though the template and setting values to corresponding grid cells (plus random)
    for (size_t col = 0; col < 5; col++) {
        for (size_t row = 0; row < 5; row++) {
            current_grid[posNum +col][posNum +row] = templateStruct[col][row];
        };
    };
};

void item_pickup(player& character, char current_grid[20][20], bool& gameOver, int keyring[10][2], int keySet, bool do_rand) {
    int printk;
    switch(current_grid[character.x][character.y]) {
        case '^':
            if (do_rand == true) {
                if (flip() == 0 && character.keeper1key.id != std::to_string(keyring[keySet][0]).erase(0, 1)) {
                    character.keeper1key.setKey(keyring[keySet][0]);
                    character.keeper1key.id = std::to_string(keyring[keySet][0]).erase(0, 1);
                    printk = character.keeper1key.getKey();
                } else {
                    character.keeper2Key.setKey(keyring[keySet][1]);
                    character.keeper2Key.id = std::to_string(keyring[keySet][1]).erase(0, 1);
                    printk = character.keeper2Key.getKey();
                };
            } else {
                character.keeper1key.setKey(keyring[1][0]);
                character.keeper1key.id = std::to_string(keyring[1][0]).erase(0, 1);
                printk = character.keeper1key.getKey();
            };
            cout << "\nYou found a key. The number " << printk << " is on it." << endl;
            break;
        case 'X':
            cout << "\nYou've won the game!" << endl;
            gameOver = true;
            break;
        case '+':
            character.gainLife(10);
            cout << "\nYou have found a health charm-shard." << endl;
            cout << "\nYour health is now at " << character.getLife() << endl;
    };
};

bool detected_in(char current_grid[20][20], player character, int LTstart, int area) {
    size_t col;
    size_t row;
    for (col = 0;col < area; col++) {
        for (row = 0;row < area; row++) {
            if (current_grid[LTstart +col][LTstart +row] == current_grid[character.x][character.y]) {
                return true;
            };
        };
    };
    if ((col = area) || (row = area)) {
        return false;
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
                if (character.gateSignature == gatekeeper1.gateSignature) {
                    gatekeeper1.unlock(current_grid, character);
                    if ((gatekeeper2.unlocked == true) && (gatekeeper1.unlocked == true)) {
                        current_grid[gatekeeper1.extX][gatekeeper1.extY] = '|';
                        current_grid[gatekeeper2.extX][gatekeeper2.extY] = '|';
                    };
                } else if (character.gateSignature == gatekeeper2.gateSignature) {
                    gatekeeper2.unlock(current_grid, character);
                    if ((gatekeeper2.unlocked == true) && (gatekeeper1.unlocked == true)) {
                        current_grid[gatekeeper1.extX][gatekeeper1.extY] = '|';
                        current_grid[gatekeeper2.extX][gatekeeper2.extY] = '|';
                    };
                } else {
                    cout << "\nThere isn't a gate." << endl;
                };
            } else if (command == "keys") {
                if ((character.keeper1key.id != "00") || (character.keeper2Key.id != "00")) {
                    cout << "\nYou have key ";
                } else { cout << "\nYou have no keys."; };
                if (character.keeper1key.id != "00") {
                    cout << character.keeper1key.getKey();
                    if (character.keeper2Key.id != "00") {
                        cout << " and key " << character.keeper2Key.getKey() << ".";
                    } else { cout << "."; };
                } else {
                    if (character.keeper2Key.id != "00") {
                        cout << character.keeper2Key.getKey() << ".";
                    };
                };
                cout << endl;
            } else if ((command == "open") && character.gateSignature[0] == 'd') {
                current_grid[(int) character.gateSignature[2]][(int) character.gateSignature[3]] = '_';
                cout << "\nDoor opened." << endl;
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

void step(char current_grid[20][20], player& character, int grid_size, char& move_direction) {
    current_grid[character.x][character.y] = character.skin;
    //printing grid again
    display_grid(current_grid, grid_size);
    //replacing last cell that the character was in
    current_grid[character.x][character.y] = ' ';
    cin >> move_direction;
};

void obj_reset(char current_grid[20][20], player& character, int grid_size, char& move_direction, char client) {
    if (client == '#') { cout << "\nYou cannot move here." << endl; };
    if (client == '/') { cout << "\nA door is blocking your path. You should be able to open it." << endl; };
    if (client == '=') { cout << "\nThere's a gate here. Maybe there's a lock nearby." << endl; };
    character.x = character.prev_x_coord;//settings player to previous coords (before moved into a wall)
    character.y = character.prev_y_coord;
    if (client != '/') { display_grid(current_grid, grid_size); };
    if (client != '/') { cin >> move_direction; };
};

void is_alive(player character, bool& gameOver) {
    if (character.getLife() == 0) {
        cout << "\nYou died." << endl;
        gameOver = true;
        delete &character;
    };
};

void enemy_action(char current_grid[20][20], enemy& MonsterOne, player& character) {
    if (MonsterOne.entry == true) {
        MonsterOne.prev_x_coord = MonsterOne.x; MonsterOne.prev_y_coord = MonsterOne.y;
        MonsterOne.auto_move(current_grid, character);
        current_grid[MonsterOne.x][MonsterOne.y] = MonsterOne.skin;
        current_grid[MonsterOne.prev_x_coord][MonsterOne.prev_y_coord] = ' ';
    };
};

char justify_move(char current_grid[20][20], player subject) {
    switch (current_grid[subject.x][subject.y]) {
        case '#': return '#';
        case 'M': return 'M';
        case 'H': return 'H';
        case '/': return '/';
        case '_': return '_';
        case '=': return '=';
        default: break;
    };
};

char deduct_approach(player character, box subject) {
    if (character.prev_y_coord < subject.y) { return 'l'; };
    if (character.prev_y_coord > subject.y) { return 'r'; };
    if (character.prev_x_coord > subject.x) { return 'd'; };
    if (character.prev_x_coord < subject.x) { return 'u'; };
};
