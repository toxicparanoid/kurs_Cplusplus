#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
using namespace std;

void printGrid(const vector<vector<bool>>& grid, int generation, int liveCells) {
    cout << "Generation: " << generation << ", Live cells: " << liveCells << endl;
    for (const auto& row : grid) {
        for (bool cell : row) {
            cout << (cell ? '*' : '-') << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int countLiveNeighbors(const vector<vector<bool>>& grid, int x, int y, int height, int width) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < height && ny >= 0 && ny < width && grid[nx][ny]) {
                ++count;
            }
        }
    }
    return count;
}

bool updateGrid(vector<vector<bool>>& grid, int height, int width) {
    vector<vector<bool>> newGrid = grid;
    bool changed = false;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int liveNeighbors = countLiveNeighbors(grid, i, j, height, width);

            if (grid[i][j]) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newGrid[i][j] = false;
                    changed = true;
                }
            } else {
                if (liveNeighbors == 3) {
                    newGrid[i][j] = true;
                    changed = true;
                }
            }
        }
    }

    grid = newGrid;
    return changed;
}

int countLiveCells(const vector<vector<bool>>& grid) {
    int count = 0;
    for (const auto& row : grid) {
        for (bool cell : row) {
            if (cell) ++count;
        }
    }
    return count;
}

bool loadInitialConfiguration(const string& filename, vector<vector<bool>>& grid, int& height, int& width) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    file >> height >> width;
    grid.resize(height, vector<bool>(width, false));

    int row, col;
    while (file >> row >> col) {
        if (row >= 0 && row < height && col >= 0 && col < width) {
            grid[row][col] = true;
        }
    }

    file.close();
    return true;
}

int main() {
    string filename = "life.txt";
    int height, width;
    vector<vector<bool>> grid;

    if (!loadInitialConfiguration(filename, grid, height, width)) {
        return 1;
    }

    int generation = 0;
    int liveCells = countLiveCells(grid);
    bool changed = true;

    while (changed && liveCells > 0) {
        printGrid(grid, generation, liveCells);
        changed = updateGrid(grid, height, width);
        liveCells = countLiveCells(grid);
        ++generation;
        usleep(200000);
    }

    printGrid(grid, generation, liveCells);
    if (liveCells == 0) {
        cout << "All cells are dead. Game over!" << endl;
    } else {
        cout << "The world has stagnated. Game over!" << endl;
    }

    return 0;
}