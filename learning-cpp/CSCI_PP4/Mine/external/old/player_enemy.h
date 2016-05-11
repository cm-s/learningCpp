/*
    This code is the first and only iteration of the player_enemy files that were previously included in the main program.
    This code exists here only to serve as history for the new objs.cpp and objs.h files.
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
    player();
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
    void auto_move(char current_grid[20][20], player& character);
    void looseLife(char current_grid[20][20], player character);
    double getLife() { return life; };
    double getDamage() { return damage; };
    ~enemy();
private:
    double life;
    double damage;
};
