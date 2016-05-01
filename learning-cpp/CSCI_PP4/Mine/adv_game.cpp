/*
 * adv_game (v2.2.1)
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
    item keeper1key;
    item keeper2Key;
    string gateSignature;
    void looseLife(double life_lost) {
        life -= life_lost;
        cout << "\nYou've been attacked. You have " << getLife() << " life remaining." << endl;
    };
    int getLife() { return life; };
    void gainLife(int value) { life += value; };
    int getDamage() { return damage; };
private:
    double life = 500;
    double damage = 50;
};

class enemy
{
public:
    int x, y;
    char skin = 'M';
    int prev_x_coord;
    int prev_y_coord;
    bool entry = false;
    void attack(player& targetEntity) {
        targetEntity.looseLife(damage);
    };
    void auto_move(char current_grid[20][20], player& character) {
        if ((character.x % x <= 1 && character.x / x <= 1) && (character.y % y <= 1 && character.y / y <= 1)) {
            attack(character);
        } else {//alternate algorythm sited to the right. Results in much more sperattic behavior.
            if (x < character.x) {                  //    if (x < character.x) {
                x += 1;                             //        x += 1;
            } else if (x > character.x) {           //    } else { x -= 1; };
                x -= 1;                             //    if (y < character.y) {
            } else if (y < character.y) {           //        y += 1;
                y += 1;                             //    } else { y -= 1; };
            } else if (y > character.y) { y -= 1; };
        };
        if (current_grid[x][y] == '#') {
            x = prev_x_coord;
            y = prev_y_coord;
        };
    };
    void looseLife(char current_grid[20][20], player character) {
        life -= character.getDamage();
        if (life <= 0) {
            current_grid[x][y] = ' ';
            skin = ' ';
            x = 19; y = 19;
            prev_x_coord = 19; prev_y_coord = 19;
        };
    };
private:
    double life = 100;
    double damage = 25;
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
        if (key == character.keeper1key.getKey()) {
            current_grid[x][y] = '%';
            x = 0; y = 0;
        };
        if (key == character.keeper2Key.getKey()) {
            current_grid[x][y] = '%';
            x = 0; y = 0;
        };
    };
};

/*Random functions*/
int flip(); int flip() { return rand() %2; };
int randomCell(); int randomCell() { srand(time(NULL));
                                     return rand() % 19 + 3; };

void item_pickup(player& character, char current_grid[20][20], bool& gameOver, int keyring[10][2], int keySet);

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
        item_pickup(character, current_grid, gameOver, keyring, 0);
        step(current_grid, character, grid_size, move_direction);
    };
} while(gameOver == false);

memset(current_grid[20], 0, 20);

    //setup level two
    move_direction = 's';
    gameOver = false;
    character.firstPlay = true;
    levelConstruct(levelTwo, current_grid);
    game_level = 2;

    lock gatekeeper1; gatekeeper1.x = 11; gatekeeper1.y = 16;
    gatekeeper1.key = keyring[0][0]; gatekeeper1.gateSignature = std::to_string(keyring[0][0]).erase(0, 1);
    lock gatekeeper2; gatekeeper2.x = 11; gatekeeper2.y = 13;
    gatekeeper2.key = keyring[0][1]; gatekeeper2.gateSignature = std::to_string(keyring[0][1]).erase(0, 1);
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
        if (justify_move(current_grid, character) == '#') {
            obj_reset(current_grid, character, grid_size, move_direction, '#');
        } else {
            item_pickup(character, current_grid, gameOver, keyring, 0);
            step(current_grid, character, grid_size, move_direction);
        };
    } while(gameOver == false);
        //cleaning up for level three
        //delete gatekeeper1; delete gatekeeper2;

        move_direction = 'w';
        gameOver = false;
        character.firstPlay = true;
        levelConstruct(levelThree, current_grid);
        game_level = 3;

        display_grid(current_grid, grid_size);
        //declare gatekeeers

        //for now these two statements are to create a backtrace at the end of the program.
        memset(current_grid[20], 0, 20);
        delete &current_grid[20][20];
        //all above code ends with stack smashing as of versions 1.0.1 and over. Newest errors below.
        /* *** Error in `./a.out': double free or corruption (out): 0x00007ffc30ce8c90 *** Aborted (core dumped) */
        /* *** Error in `./a.out': munmap_chunk(): invalid pointer: 0x00007ffdd6f71920 *** Aborted (core dumped) */

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
    //looping though the template and setting values to corresponding grid cells (plus random)
    for (size_t col = 0; col < 5; col++) {
        for (size_t row = 0; row < 5; row++) {
            current_grid[posNum +col][posNum +row] = templateStruct[col][row];
        };
    };
};

void item_pickup(player& character, char current_grid[20][20], bool& gameOver, int keyring[10][2], int keySet) {
    int printk;
    switch(current_grid[character.x][character.y]) {
        case '^':
            if (flip() == 0 && character.keeper1key.id != std::to_string(keyring[keySet][0]).erase(0, 1)) {
                character.keeper1key.setKey(keyring[keySet][0]);
                character.keeper1key.id = std::to_string(keyring[keySet][0]).erase(0, 1);
                printk = character.keeper1key.getKey();
            } else {
                character.keeper2Key.setKey(keyring[keySet][1]);
                character.keeper2Key.id = std::to_string(keyring[keySet][1]).erase(0, 1);
                printk = character.keeper2Key.getKey();
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
                } else if (character.gateSignature == gatekeeper2.gateSignature) {
                    gatekeeper2.unlock(current_grid, character);
                } else if ((character.gateSignature != gatekeeper1.gateSignature) || (character.gateSignature != gatekeeper2.gateSignature)) {
                    cout << "\nThe gate didn't budge" << endl;
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
    character.x = character.prev_x_coord;//settings player to previous coords (before moved into a wall)
    character.y = character.prev_y_coord;
    display_grid(current_grid, grid_size);
    cin >> move_direction;
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
        case '#':
            return '#';
        case 'M':
            return 'M';
        default:
            break;
    };
};
