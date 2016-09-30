#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include "cm.std.cpp"
using namespace std;

/**
 * NULL_ENTITY
 *
 * Dummy object that serves in the place of a real entity, when an entity object is required
 * to be passed in, but not needed.
 *
 */
class NULL_ENTITY {
public:
    void loseHealth(int none) {};
    short int x = 0;
    short int y = 0;
    char skin = '#';
    short int prev_x = 0;
    short int prev_y = 0;
    string deduct_approach(auto none) {};
};
/**
 * collision_report
 *
 * Somewhat trivial function that will return the value of a grid cell from the
 * x and y coordinates of a specified object.
 *
 * @param grid to be checked for the return value. Always the current_grid.
 * @param object, whose coordinates will be read in order to determine where the desired grid cell is.
 * @return any value that could possibly occur in the grid.
 */
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
        case '?': return '?';
        case '*': return '*';
    };
};

/**
 * PLAYER
 *
 * Class encapsulating all methods necessicary to allow the player to move and interact
 * with the environment in the game.
 *
 */
class ENEMY;
class PLAYER {
public:
    /**
     * key
     *
     * Nested class that contains all logic to allow complete operability of keys that the player
     * may or may not have.
     *
     */
    class key
    {
    private:
        short int keycode;
    public:
        const short int &codecast;
        key(short int index): codecast(index), keycode{index} {
            cout << "You: It seems I've found a key, the number on it is " << getCode() << '.' << endl;
        };
        short int getCode() {
            return keycode;
        };
    };
    CMSTD cmstd;
    string signature;
    string msgCode;
    string quit_alises[3] = { {"break"}, {"quit"}, {"exit"} };
    key *keys[];
    int keys_write_head = 0;
    char direction;
    short int gameLevel = 1;
    short int prev_x;
    short int prev_y;
    short int x;
    short int y;
    char skin;
    const int &bindInt;
    const char &bindSkin;
    /**
     * PLAYER (constructor)
     *
     * Binding constructor for the player.
     *
     * @param x coordinate describing the horizontal plane by which the player will be predisplaced.
     * @param y coordinate describing the vertical place by which the player will be predisplaced.
     * @param skin depicting the player. This is a permanent setting.
     *
     */
    PLAYER(short int x, short int y, char skin): bindInt(x), x{x}, y{y}, bindSkin(x), skin{skin} {
        prev_x = x;
        prev_y = y;
    };
    /**
     * getDamage
     *
     * Accessor method for the characters damage value.
     *
     * @return the damage value of the character
     *
     */
    int getDamage() { return damage; };
    /**
     * getHealth
     *
     * Accessor method for the characters health value.
     *
     * @return health value of the character.
     *
     */
    int getHealth() { return health; };
    short int retrieve_key(short int set, short int index) {
        return keyring[set][index];
    };
    /**
     * loseHealth
     *
     * Mutator for characters health value.
     *
     * @return value to be subtracted from characters health.
     *
     */
    void loseHealth(int value) {
        health -= value;
    };
    /**
     * attack
     *
     * Trivial function to complete the action of attacking, by calling the target's loseHealth function.
     *
     * @param target to be attacked.
     *
     */
    void attack(auto target) {
        target.loseHealth(damage);
    };

    /**
     * move
     *
     * Method handling all user input, either movement or direct game commmands.
     *
     */
    void move();
    /**
     * object_reaction
     *
     * Method encapsulating logical reactions the player will make to it's environment.
     * This method does not encompass all reactions that the player will make to it's environment.
     *
     * @param current_grid variable to access objective data within the current_grid.
     * @param ENEMY or NULL_ENTITY instance to allow access to derived methods in order to chain
     * reactions that the instace will perform.
     *
     */
    void object_reaction(char current_grid[20][20], ENEMY &aggrogate);
    void object_reaction(char current_grid[20][20], NULL_ENTITY &aggrogate);
private:
    char internal_command;
    int damage = 20;
    int health = 400;
    /*
     * This variable holds all keys that can be used in the game.
     * These keys are in pairs because most gates will have a partner with a key and the second key plays
     * a cruical part in authentication.
     */
    int keyring[10][2] = {
        {323, 232}, {890, 208},
        {157, 176}, {225, 755},
        {114, 495}, {611, 815},
        {212, 311}, {732, 326},
        {985, 860}, {615, 524}
    };
};
/**
 * ENEMY
 *
 * Object that behaves somewhat like a hunter, when deployed in the game.
 * This object's purpose is to defeat the main character.
 *
 */
class ENEMY {
public:
    short int prev_x;
    short int prev_y;
    short int x;
    short int y;
    char skin;
    const short int &bindx;
    const char &bindSkin;
    /**
     * ENEMY (constructor)
     *
     * Binding constructor for an enemy.
     *
     * @param x coordinate describing the horizontal predisposition of the enemy.
     * @param y coordinate describing the vertical predisposition of the enemy.
     * @param skin depicting the enemy.
     *
     */
    ENEMY(short int x, short int y, char skin): bindx(x), x{x}, y{y}, bindSkin(x), skin{skin} {
        cout << "Narrator: You've encountered an enemy!" << endl;
        prev_x = x;
        prev_y = y;
    };
    /**
     * loseHealth
     *
     * Short method to delete the enemy if it's health is at zero.
     * This method also works as a one-way mutator.
     *
     * @param value to be subtracted from the enemy's health.
     *
     */
    void loseHealth(int value);
    /**
     * attack
     *
     * Method to attack a specified target. This is performed by calling loseHealth on the target.
     *
     * @param target to be attacked.
     *
     */
    void attack(PLAYER target) {
        target.loseHealth(damage);
    };
    /**
     * autoMove
     *
     * Methodology controlling all movements and influencing or invoking all actions performed by the
     * enemy.
     *
     * @param current_grid variable to allow access to enviromental data.
     * @param target for the enemy to pursue.
     *
     */
    void autoMove(char current_grid[20][20], PLAYER target);
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
    /**
     * BOX (constructor)
     *
     * Method executing during the creation of a BOX object
     *
     * @param x coordinate of the horizontal plane on which the object will be initially placed
     * @param y coordinate of the vertical plane on which the object will be initially placed
     * @param skin to repersent the object
     *
     */
    BOX(short int x, short int y, char skin): bindInt(x), x{x}, y{y}, bindSkin(x), skin{skin} {
        prev_x = x;
        prev_y = y;
    };

    string deduct_approach(PLAYER subject);
    void checkif_pushed(char current_grid[20][20], PLAYER &player);
};
class GATE {
public:
    int x;
    int y;
    char skin;
    const int& bindCoord;
    const char& bindSkin;
    GATE(short int x, short int y, char skin): bindCoord(x), x{x}, y{y}, bindSkin(skin), skin{skin} {  };
    /**
     * lock_check
     *
     * Method to check and inforce the state of the gate, either being locked or unlocked.
     *
     * @param keyin, being the key that is inserted into the lock;
     *
     */
    void lock_check(int keyin);

private:
    int passcode;
};
