#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Maze {
private:
    int width, height;
    vector<vector<char>> maze;
    vector<vector<bool>> visited;

    const char WALL = '#';
    const char PATH = ' ';
    const char START = 'S';
    const char END = 'E';
    const char SOLUTION = '.';

    void initializeMaze() {
        maze.resize(height, vector<char>(width, WALL));
        visited.resize(height, vector<bool>(width, false));
    }

    bool isValid(int x, int y) {
        return (x >= 0 && x < height && y >= 0 && y < width);
    }

    void generateMaze(int x, int y) {
        stack<pair<int, int>> s;
        s.push({x, y});
        visited[x][y] = true;
        maze[x][y] = PATH;

        while (!s.empty()) {
            int cx = s.top().first;
            int cy = s.top().second;
            s.pop();

            vector<pair<int, int>> directions = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
            random_shuffle(directions.begin(), directions.end());

            for (auto dir : directions) {
                int nx = cx + dir.first;
                int ny = cy + dir.second;

                if (isValid(nx, ny) && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    maze[nx][ny] = PATH;
                    maze[(cx + nx) / 2][(cy + ny) / 2] = PATH;
                    s.push({nx, ny});
                }
            }
        }
    }

    bool solveMazeUtil(int x, int y) {
        if (x == height - 1 && y == width - 1) {
            maze[x][y] = END;
            return true;
        }

        if (isValid(x, y) && (maze[x][y] == PATH || maze[x][y] == START) && !visited[x][y]) {
            visited[x][y] = true;

            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                if (solveMazeUtil(nx, ny)) {
                    if (maze[x][y] != START) {
                        maze[x][y] = SOLUTION;
                    }
                    return true;
                }
            }
        }

        return false;
    }

public:
    Maze(int w, int h) : width(w), height(h) {
        initializeMaze();
    }

    void createMaze() {
        srand(time(0));
        generateMaze(0, 0);
        maze[0][0] = START;
        maze[height - 1][width - 1] = PATH; // Initially mark the end as PATH to ensure connection
        visited.assign(height, vector<bool>(width, false));
        solveMazeUtil(0, 0); // Ensure there is a path from start to end
        maze[height - 1][width - 1] = END; // Mark the end point correctly
    }

    void printMaze() {
        for (const auto &row : maze) {
            for (const auto &cell : row) {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    int width, height;

    cout << "Ingrese el ancho del laberinto: ";
    cin >> width;
    cout << "Ingrese la altura del laberinto: ";
    cin >> height;

    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;

    Maze maze(width, height);
    maze.createMaze();
    maze.printMaze();

    return 0;
}
