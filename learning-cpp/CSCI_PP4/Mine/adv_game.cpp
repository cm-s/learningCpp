#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void erect_border(int grid_size, string grid);

void grid_constructor(int grid_size, string grid);

int main() {
    int grid_size;
    int x; int y;
    char move_direction;//fill at end

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
    cin >> move_direction;

    //erect_border(grid_size, grid);
return 0;
};

void erect_border(int grid_size, string& grid) {

};

void grid_constructor(int grid_size, string grid, int x, int y) {
    /*for (int row =0; row <= (y -1); row++) {
        for (int col =0; col <= (x -1); col++) {
            cout << grid[row][col] << ' ';
        };
        cout << endl;
    };*/
    //this code will be needed
};
