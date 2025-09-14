#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

int h[10000][3], b[10000];
int xx[4] = {-1, 1, 0, 0}, yy[4] = {0, 0, -1, 1};
int map_orig[100][100], map_used[100][100];
int rows, cols;

int main(int argc, char *argv[]) {
    if (argc != 6) {
        cout << "Usage: " << argv[0] << " <map_file_path> <start_x> <start_y> <goal_x> <goal_y>" << endl;
        return 1;
    }

    string map_file_path = argv[1];
    int start_x = atoi(argv[2]);
    int start_y = atoi(argv[3]);
    int goal_x = atoi(argv[4]);
    int goal_y = atoi(argv[5]);

    ifstream fin(map_file_path);
    if (!fin) {
        cout << "Cannot open file: " << map_file_path << endl;
        return 1;
    }

    string line;
    rows = 0;
    while (getline(fin, line)) {
        stringstream ss(line);
        int num;
        cols = 0;
        while (ss >> num) {
            if (rows < 100 && cols < 100) {
                map_orig[rows][cols] = num;
                map_used[rows][cols] = num;
            }
            cols++;
        }
        rows++;
    }
    fin.close();

    if (rows > 100 || cols > 100) {
        cout << "Map size too large, maximum 100x100" << endl;
        return 1;
    }

    if (start_x < 0 || start_x >= rows || start_y < 0 || start_y >= cols) {
        cout << "I can’t go to the postion (" << start_x << "," << start_y << ")." << endl;
        return 0;
    }
    if (map_used[start_x][start_y] != 0) {
        cout << "I can’t go to the postion (" << start_x << "," << start_y << ")." << endl;
        return 0;
    }
    if (goal_x < 0 || goal_x >= rows || goal_y < 0 || goal_y >= cols) {
        cout << "I can’t go to the postion (" << goal_x << "," << goal_y << ")." << endl;
        return 0;
    }
    if (map_used[goal_x][goal_y] != 0) {
        cout << "I can’t go to the postion (" << goal_x << "," << goal_y << ")." << endl;
        return 0;
    }

    int t = 0, w = 1;
    h[1][0] = 0;
    h[1][1] = start_x;
    h[1][2] = start_y;
    map_used[start_x][start_y] = 1;

    bool found = false;
    if (start_x == goal_x && start_y == goal_y) {
        found = true;
    } else {
        do {
            t++;
            for (int i = 0; i < 4; i++) {
                int x = h[t][1] + xx[i];
                int y = h[t][2] + yy[i];
                if (x >= 0 && x < rows && y >= 0 && y < cols && map_used[x][y] == 0) {
                    map_used[x][y] = 1;
                    w++;
                    h[w][0] = t;
                    h[w][1] = x;
                    h[w][2] = y;
                    if (x == goal_x && y == goal_y) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) break;
        } while (t < w);
    }

    if (!found) {
        cout << "I can’t go to the postion (" << goal_x << "," << goal_y << ")." << endl;
        return 0;
    }

    int k = 0;
    int current = w;
    while (current != 0) {
        k++;
        b[k] = current;
        current = h[current][0];
    }

    char output_map[100][100];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            output_map[i][j] = map_orig[i][j] + '0';
        }
    }

    for (int i = 1; i <= k; i++) {
        int idx = b[i];
        int x = h[idx][1];
        int y = h[idx][2];
        output_map[x][y] = '*';
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << output_map[i][j];
            if (j < cols - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

