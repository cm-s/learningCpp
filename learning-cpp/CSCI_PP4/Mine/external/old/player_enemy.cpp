/*
    This code is the first and only iteration of the player_enemy files that were previously included in the main program.
    This code exists here only to serve as history for the new objs.cpp and objs.h files.
*/
#include "player_enemy.h"

player::player() {};
player::~player() {};

enemy::enemy(double dmg, double hp): damage(dmg), life(hp) {
    cout << "\nDEBUG MESSAGE: Enemy object created with damage " << getDamage() << " and life " << getLife() << endl;
};

void enemy::auto_move(char current_grid[20][20], player& character) {
        if ((character.x % x <= 1 && character.x / x <= 1) && (character.y % y <= 1 && character.y / y <= 1)) {
            attack(character);
        } else {
            if (x < character.x) {
                x += 1;
            } else if (x > character.x) {
                x -= 1;
            } else if (y < character.y) {
                y += 1;
            } else if (y > character.y) { y -= 1; };
        };
        if (current_grid[x][y] == '#') {
            x = prev_x_coord;
            y = prev_y_coord;
        };
    };

void enemy::looseLife(char current_grid[20][20], player character) {
        life -= character.getDamage();
        if (life <= 0) {
            current_grid[x][y] = ' ';
            skin = ' ';
            x = 19; y = 19;
            prev_x_coord = 19; prev_y_coord = 19;
            skin = '#';
        };
    };

enemy::~enemy() {};
