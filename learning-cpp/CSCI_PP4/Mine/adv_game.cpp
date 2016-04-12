#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void erect_border(int grid_size, string grid);

void grid_constructor(int grid_size, string grid);

void character_dynamic(char& palyer, string& grid, char& move_direction);

int main() {
    int grid_size;
    int x; int y;
    char move_direction;//fill at end
    char palyer;

    cout << "Enter board size: ";

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
    erect_border(grid_size, grid);
    grid_constructor(grid_size, grid, x, y);
    character_dynamic(player, grid, move_direction);

    cout << "\nUse the WASD keys to move your character" << endl;

return 0;
};

void erect_border(int grid_size, string& gridState) {
    for (size_t ln =0; ln < grid_size; ln++) {
        gridState[ln][0] = '0';
        gridState[0][ln] = '0';
        gridState[ln][(grid_size -1)] = '0';
        gridState[(grid_size -1)][ln] = '0';
    };
};//function complete

void grid_constructor(int grid_size, string gridState, int x, int y) {
    for (size_t row =0; row <= (y -1); row++) {
        for (size_t col =0; col <= (x -1); col++) {
            cout << gridState[row][col] << ' ';
        };
        cout << endl;
    };
};//function complete

void character_dynamic(char& player, string& grid, char& move_direction) {
    //place character in center initially
    grid[(grid_size -1)/2][(grid_size -1)/2] = '&';
    grid_constructor(grid_size, grid, x, y);
    cin >> move_direction; cout << endl;

};
