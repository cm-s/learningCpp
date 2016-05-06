#include "player_enemy.h"

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
