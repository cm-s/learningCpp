#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <stdlib.h>
using namespace std;

class item
{
public:
    short int keyNum;
    /**
     * Empty constructor. This function has the only practical purpose of offsetting the memory of one item
     * from another, so the data from the creation of another item does not fit into the structure of another.
     *
     * @param the number distinguishing which key is being created. (Will always be 1 or 2)
     */
    item(short int keyNum);
    string id = "00";
    short int getKey() { return key; };
    void setKey(int value) { key = value; };
    ~item();
private:
    short int keyNumber;
    short int key;
};

class player
{
public:
    player();
    bool firstPlay = true;
    int x = 10;
    int y = 10;
    char skin = '&';
    int prev_x_coord;
    int prev_y_coord;
    item *keeper1key = new item(1);
    item *keeper2key = new item(2);
    string gateSignature;
    /**
     * Function to subtract life from the player and output what life the player has left.
     *
     * @param intager value describing how much life is to be subtracted from the player.
     */
    void looseLife(double life_lost) {
        life -= life_lost;
        cout << "\nYou've been attacked. You have " << getLife() << " life remaining." << endl;
    };
    int getLife() { return life; };
    void gainLife(int value) { life += value; };
    int getDamage() { return damage; };
    int setDamage(short int gain) { damage += gain; };
    ~player();
private:
    double life = 500;
    double damage = 50;
};

class enemy
{
public:
    double dmg; double hp;
    enemy(double dmg, double hp);
    int x, y;
    char skin = 'M';
    int prev_x_coord;
    int prev_y_coord;
    bool entry = false;
    void attack(player& targetEntity) { targetEntity.looseLife(damage); };
    /**
     * Automatically moves the enemy towards the player after the player has made a move.
     *
     * @param grid variable.
     * @param character targeted to be moved towards.
     */
    void auto_move(char current_grid[20][20], player& character);
    /**
     * Function for subtracting life from the enemy and checking if the enemy has any life left.
     *
     * @param grid variable.
     * @param player to damage the parent enemy.
     */
    void looseLife(char current_grid[20][20], player character);
    double getLife() { return life; };
    double getDamage() { return damage; };
    ~enemy();
private:
    double life;
    double damage;
};

class lock
{
public:
    lock();
    int key;
    int x, y;
    int extX = 21;
    int extY = 21;
    char skin = '@';
    string gateSignature;
    bool unlocked = false;
    /**
     * Function for moving the player out of the gate's grid cell and for informing the player
     * what key can unlock the gate.
     *
     * @param grid variable.
     * @param player whom will be moved out of the cell that is occupied by the skin of the gate.
     */
    void detect(char current_grid[20][20], player& character);
    /**
     * Function called upon the player's command. Essentially unlocks the gate that was previously attempted to be moved through.
     * Makes the gate passable.
     *
     * @param grid variable.
     * @param player to be checked for having the correct key.
     */
    void unlock(char current_grid[20][20], player& character);
    ~lock();
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
