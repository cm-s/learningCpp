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
    void detect(char current_grid[20][20], player& character);
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
