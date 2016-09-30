#include "objs.h"

// PLAYER method definitions
void PLAYER::move() {
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
            } else if ( cmstd.in(command, quit_alises) ) {
                cout << "Game: Exiting...\n";
                exit(EXIT_SUCCESS);
            } else if (command == "keys") {
                cout << "Game: Keys in your inventory: ";
                for (size_t k = 0; k < keys_write_head; k++) {
                    cout << keys[k];
                };
                cout << '.' << endl;
            };
            break;
        default:
            cout << "Game: (" << direction << ") isn't a move. Type \"help\" for a list of commands." << endl;
            break;
    };
};
void PLAYER::object_reaction(char current_grid[20][20], ENEMY &aggrogate) {
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
        case '^':
            int* hasKey;
            hasKey = new int;
            *hasKey = 0;
            if ( (rand() % 2 == 0) && (*hasKey != 1) ) {
                keys[keys_write_head] = new key(retrieve_key(0, 0));
                keys_write_head++;
                *hasKey = 1;
            } else if ( *hasKey != 2 ) {
                keys[keys_write_head] = new key(retrieve_key(0, 0));
                keys_write_head++;
                *hasKey = 2;
            };
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
        case '?':
            cout << "Message" << endl;
            switch (gameLevel) {
                case 1:
                    break;
                case 2:
                    msgCode = "Narrator: You see a deranged crawler screaming and moving around blindly.\nYou: I better be careful, this guy seems dangerous.";
                    break;
                case 3:
                    msgCode = "You: There seems to be a pressure plate across the room, I wonder if this box could activate it...";
                    break;
                case 4:
                    msgCode = "Narrator: As you enter the root, a dim light illuminates a strange old object in the distance.";
                    break;
            };
            break;
    };
    current_grid[x][y] = skin;
    current_grid[prev_x][prev_y] = ' ';
};
void PLAYER::object_reaction(char current_grid[20][20], NULL_ENTITY &aggrogate) {
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
        case '^':
            int* hasKey;
            hasKey = new int;
            *hasKey = 0;
            if ( (rand() % 2 == 0) && (*hasKey != 1) ) {
                keys[keys_write_head] = new key(retrieve_key(0, 0));
                keys_write_head++;
                *hasKey = 1;
            } else if ( *hasKey != 2 ) {
                keys[keys_write_head] = new key(retrieve_key(0, 0));
                keys_write_head++;
                *hasKey = 2;
            };
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
        case '?':
            cout << "Message" << endl;
            switch (gameLevel) {
                case 1:
                    break;
                case 2:
                    msgCode = "Narrator: You see a deranged crawler screaming and moving around blindly.\nYou: I better be careful, this guy seems dangerous.";
                    break;
                case 3:
                    msgCode = "You: There seems to be a pressure plate across the room, I wonder if this box could activate it...";
                    break;
                case 4:
                    msgCode = "Narrator: As you enter the root, a dim light illuminates a strange old object in the distance.";
                    break;
            };
    };
    current_grid[x][y] = skin;
    current_grid[prev_x][prev_y] = ' ';
};

// ENEMY method definitions
void ENEMY::loseHealth(int value) {
    if (health <= 0) {
        skin = '#';
        x = 0;
        y = 0;
    };
    health -= value;
    cout << "Debug; ENEMY health: " << health << endl;
};
void ENEMY::autoMove(char current_grid[20][20], PLAYER target) {
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

// BOX method definitions
string BOX::deduct_approach(PLAYER subject) {
    if (subject.y > subject.prev_y) { return "east"; }; //player moving to the east
    if (subject.y < subject.prev_y) { return "west"; }; //etc...
    if (subject.x > subject.prev_x) { return "south"; };
    if (subject.x < subject.prev_x) { return "north"; };
};
void BOX::checkif_pushed(char current_grid[20][20], PLAYER &player) {
    if (player.x == x && player.y == y)
    {
        prev_x = x; prev_y = y;
        if (deduct_approach(player) == "east") { y += 1; };
        if (deduct_approach(player) == "west") { y -= 1; };
        if (deduct_approach(player) == "south") { x += 1; };
        if (deduct_approach(player) == "north") { x -= 1; };
        if ((collision_report(current_grid, this) == '#') || (collision_report(current_grid, this) == 'H')) {
            player.x = player.prev_x;
            player.y = player.prev_y;
            x = prev_x; y = prev_y;
            cout << "You: It seems stuck." << endl;
        };
        if (collision_report(current_grid, this) == '*') {
            switch (player.gameLevel) {
                case 3:
                    current_grid[2][8] = ' ';
                    break;
            };
        }
    };
    current_grid[x][y] = skin;
};
