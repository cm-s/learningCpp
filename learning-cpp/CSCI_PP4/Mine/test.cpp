#include <iostream>
 #include <string>
 #include <cstring>
 using namespace std;

class player
{
public:
    int x, y;
    char skin;
};

 int main() {
     int grid_size;
     int x; int y;
     char move_direction;//fill at end
     bool gameOver = false;

     cout << "What size would you like the playing board to be";

     cin >> grid_size;
     x = grid_size;
     y = grid_size;

     string grid[grid_size][grid_size];
     for (size_t row =0; row <= (y -1); row++) {
         for (size_t col =0; col <= (x -1); col++) {
             grid[row][col] += '#';
             cout << grid[row][col] << ' ';
         };
         cout << endl;
     };
     cout << endl;
     for (size_t ln =0; ln < grid_size; ln++) {
         grid[ln][0] = '0';
         grid[0][ln] = '0';
         grid[ln][(grid_size -1)] = '0';
         grid[(grid_size -1)][ln] = '0';
     };
     for (size_t row =0; row <= (y -1); row++) {
         for (size_t col =0; col <= (x -1); col++) {
             cout << grid[row][col] << ' ';
         };
         cout << endl;
     };
     cout << "\nUse the WASD keys to move your character" << endl;

     player character;
     character.x = character.y = (grid_size /2);
     character.skin = '$';

     do {
         grid[character.x][character.y] = character.skin;
         for (size_t row =0; row <= (y -1); row++) {
             for (size_t col =0; col <= (x -1); col++) {
                 cout << grid[row][col] << ' ';
             };
             cout << endl;
         };
         for (size_t md = 1; md <= 10; md++) {
             //making space for new grid
             for (size_t space = 0; space <= 15; space++) {
                 cout << endl;
             }
             //changing character's coords depending on the move_direction
             switch (toupper(move_direction)) {
                 case 'W':
                    character.y += 1;
                 case 'A':
                    character.x -= 1;
                 case 'S':
                    character.y -= 1;
                 case 'D':
                    character.x += 1;
             };
             //checking if character is moving into a wall
             //if (grid[character.x][character.y] == grid[charater.x][]) {
                 //cout << "\nYou cannot move here." << endl;
             //} else {
                 grid[character.x][character.y] = character.skin;
             //};
             //printing grid again
             for (size_t row =0; row <= (y -1); row++) {
                 for (size_t col =0; col <= (x -1); col++) {
                     cout << grid[row][col] << ' ';
                 };
                 cout << endl;
             }
             //replacing last cell that the charater was in
             grid[character.x][character.y] = '#';
             cin >> move_direction;
         };
     } while(gameOver = false);
 return 0;
 };
