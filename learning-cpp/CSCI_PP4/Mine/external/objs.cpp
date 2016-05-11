#include "objs.h"

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

lock::lock() {};

void lock::detect(char current_grid[20][20], player& character) {
    if (x == character.x && y == character.y) {
        cout << "\nIt looks like you can insert a key." << endl;
        cout << "\nThe Number on the lock says: " << key << endl;
        character.x = character.prev_x_coord;
        character.y = character.prev_y_coord;
        character.gateSignature = gateSignature;
    };
};

void lock::unlock(char current_grid[20][20], player& character) {
    if (key == character.keeper1key -> getKey()) {
        current_grid[x][y] = '%';
        unlocked = true;
        x = 0; y = 0;
    };
    if (key == character.keeper2key -> getKey()) {
        current_grid[x][y] = '%';
        unlocked = true;
        x = 0; y = 0;
    };
};

lock::~lock() {};

item::item(short int keyNum): keyNumber(keyNum) {
    //params for this constructor will always be 1 for keeper1key and 2 for keeper2key.
    /*This param only exists because the size of item (I think keeper2key) fit into the memory address allignment of other objects
    upon deletion, reducing precision of the delete statement.*/
};
item::~item() {};
