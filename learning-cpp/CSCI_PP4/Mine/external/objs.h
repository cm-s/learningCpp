#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include "cm.std.cpp"
using namespace std;

class NULL_ENTITY {
public:
    void looseHealth(int none) {};
    short int x = 0;
    short int y = 0;
    char skin = '#';
    short int prev_x = 0;
    short int prev_y = 0;
    string deduct_approach(auto none) {};
};

char collision_report(char current_grid[20][20], auto obj) {
    switch (current_grid[obj -> x][obj -> y]) {
        case '#': return '#';
        case 'X': return 'X';
        case 'M': return 'M';
        case '@': return '@';
        case '/': return '/';
        case 'H': return 'H';
        case '^': return '^';
        case 'T': return 'T';
        case '+': return '+';
        case '&': return '&';
    };
};
//entity declarations
class PLAYER {
public:
    CMSTD cmstd;
    string signature;
    char direction;
    short int gameLevel = 1;
    short int prev_x;
    short int prev_y;
    short int x;
    short int y;
    char skin;
    const int &bindInt;
    const char &bindSkin;
    PLAYER(short int x, short int y, char skin): bindInt(x), x{x}, y{y}, bindSkin(x), skin{skin} {
        prev_x = x;
        prev_y = y;
    };
    int getDamage() { return damage; };
    int getHealth() { return health; };
    short int retrieve_key(short int set, short int index) { return keyring[set][index]; };
    void looseHealth(int value) { health -= value; };
    void attack(auto target) { target.looseHealth(damage); };

    class key
    {
    private:
        short int keycode;
    public:
        const short int &codecast;
        key(short int index): codecast(index), keycode{keycode} {
            cout << "You: It seems I've found a key, the number on it is " << getCode() << '.' << endl;
        };
        short int getCode() { return keycode; };
    };

    void move() {
        prev_x = x;
        prev_y = y;
        string command;
        cout << "Game: Make a move: ";
        cin >> direction;
        switch (toupper(direction)) {
            case 'W': x -= 1; break;
            case 'A': y -= 1; break;
            case 'S': x += 1; break;
            case 'D': y += 1; break;
            case 'C':
                cout << "\nGame: Enter a command: ";
                cin >> command;
                if (command == "help") {
                    cout << "\nNarrator: You can enter the following commands: \'help\' \'unlock\' \'keys\' \'open\' \'health\'";
                } else if (command == "health") {
                    cout << "You: It seems my health is " << getHealth() << '.';
                } else if (command == "open") {
                    if (signature[0] == 'd') {
                        internal_command = 'o';
                    };
                } else if ( command == "quit" ) {
                    cout << "Game: Exiting...\n";
                    exit(EXIT_SUCCESS);
                };
                break;
            default:
                cout << "Game: (" << direction << ") isn't a move." << endl;
                break;
        };
    };
    void object_reaction(char current_grid[20][20], auto aggrogate) {
        switch (collision_report(current_grid, this)) {
            case '#':
                x = prev_x;
                y = prev_y;
                cout << "Game: You cannot move here." << endl;
                break;
            case 'X':
                cout << "Game: You've passed the level!" << endl;
                gameLevel += 1;
                break;
            case '^': //needs to be perfected
                int* hasKey; hasKey = new int; *hasKey = 0;
                if (rand()%2 == 0 & *hasKey != 1) {
                    key key1(retrieve_key(0, 0));
                    *hasKey = 1;
                } else { key key1(retrieve_key(0, 1)); };
                break;
            case 'T':
                cout << "You: Wow, a sword! This should help out." << endl;
                damage += 20;
                cout << "Narrator: Your damage has increased to " << damage << '.' << endl;
                break;
            case '+':
                health += 25;
                cout << "Narrator: You've picked up a health shard, your health is now at " << health << '.' << endl;
                break;
            case 'M':
                cout << "You: Take that!" << endl;
                attack(aggrogate);
                x = prev_x;
                y = prev_y;
                break;
            case '/':
                if (internal_command == 'o') { current_grid[x][y] = ' '; }
                else {
                    cout << "You: There's a door, maybe it isn't locked." << endl;
                    signature = 'd' + to_string(x) + to_string(y);
                    x = prev_x;
                    y = prev_y;
                };
                break;
        };
        current_grid[x][y] = skin;
        current_grid[prev_x][prev_y] = ' ';
    };
private:
    char internal_command;
    int damage = 20;
    int health = 400;
    int keyring[10][2] = {
        {323, 232}, {890, 208},
        {157, 176}, {225, 755},
        {114, 495}, {611, 815},
        {212, 311}, {732, 326},
        {985, 860}, {615, 524}
    };
};
class ENEMY {
public:
    short int prev_x;
    short int prev_y;
    short int x;
    short int y;
    char skin;
    const short int &bindx;
    const char &bindSkin;
    ENEMY(short int x, short int y, char skin): bindx(x), x{x}, y{y}, bindSkin(x), skin{skin} {
        cout << "Narrator: You've encountered an enemy!" << endl;
        prev_x = x;
        prev_y = y;
    };
    void looseHealth(int value) {
        health -= value;
        if (health <= 0) {
            delete this;
        };
    };
    void attack(PLAYER target) { target.looseHealth(damage); };
    void autoMove(char current_grid[20][20], PLAYER target) {
        prev_x = x; prev_y = y;
        if (x < target.x) { x += 1; }
        else if (x > target.x) { x -= 1; }
        else if (y < target.y) { y += 1; }
        else if (y > target.y) { y -= 1; };
        switch (collision_report(current_grid, this)) {
            case '#':
                x = prev_x;
                y = prev_y;
                break;
            case '&':
                attack(target);
                break;
        };
        current_grid[x][y] = skin;
        current_grid[prev_x][prev_y] = ' ';
    };
private:
    int damage = 20;
    int health = 50;
};

class BOX {
public:
    short int prev_x;
    short int prev_y;
    short int x;
    short int y;
    char skin;
    const char& bindSkin;
    const char& bindInt;
    BOX(short int x, short int y, char skin): bindInt(x), x{x}, y{y}, bindSkin(x), skin{skin} {
        prev_x = x;
        prev_y = y;
    };
    string deduct_approach(PLAYER subject) {
        if (subject.y > subject.prev_y) { return "east"; }; //player moving to the east
        if (subject.y < subject.prev_y) { return "west"; }; //etc...
        if (subject.x > subject.prev_x) { return "south"; };
        if (subject.x < subject.prev_x) { return "north"; };
    };
    void checkif_pushed(char current_grid[20][20], PLAYER player) {
        if (player.x == x && player.y == y)
        {
            prev_x = x; prev_y = y;
            if (deduct_approach(player) == "east") { y += 1; };
            if (deduct_approach(player) == "west") { y -= 1; };
            if (deduct_approach(player) == "south") { x += 1; };
            if (deduct_approach(player) == "north") { x -= 1; };
            if (collision_report(current_grid, this) == '#') {
                player.x = player.prev_x;
                player.y = player.prev_y;
                x = prev_x; y = prev_y;
                cout << "You: It seems stuck." << endl;
            };
        };
        current_grid[x][y] = skin;
    };
};
class GATE {
public:
    GATE(short int x, short int y, char skin) {  };
};
