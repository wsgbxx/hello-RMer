#include <iostream>
#include <fstream>
#include <vector>//动态数组容器
#include <queue>//队列容器
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>//标准异常类
#include <algorithm>//算法操作
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}//构造函数,例如Point p1(3, 4)，更简洁
    bool operator==(const Point& other)//重新定义 == 运算符的行为，使其能正确比较两个自定义类型的对象，并返回一个 bool（真或假）的结果。
    const {
        return x == other.x && y == other.y;
    }
};

vector<vector<int>> readMap(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open map file");
    }
    
    vector<vector<int>> map;
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int value;
        
        while (ss >> value) {
            row.push_back(value);
        }
        
        if (!row.empty()) {
            map.push_back(row);
        }
    }
    
    return map;
}

void printMap(const vector<vector<int>>& map, const vector<Point>& path) {
    vector<vector<char>> display(map.size(), vector<char>(map[0].size()));
    
    // 复制地图
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            display[i][j] = map[i][j] == 1 ? '1' : '0';
        }
    }
    
    // 标记路径
    for (const auto& point : path) {
        display[point.x][point.y] = '*';
    }
    
    // 打印地图
    for (const auto& row : display) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

vector<Point> findPathBFS(const vector<vector<int>>& map, Point start, Point goal) {
    int rows = map.size();
    int cols = map[0].size();
    
    // 检查起点和终点是否有效
    if (start.x < 0 || start.x >= rows || start.y < 0 || start.y >= cols || 
        goal.x < 0 || goal.x >= rows || goal.y < 0 || goal.y >= cols) {
        throw out_of_range("Start or goal point out of map bounds");
    }
    
    if (map[start.x][start.y] == 1) {
        throw runtime_error("Start point is obstacle");
    }
    
    if (map[goal.x][goal.y] == 1) {
        throw runtime_error("Goal point is obstacle");
    }
    
    // BFS相关数据结构
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Point>> parent(rows, vector<Point>(cols, Point(-1, -1)));
    queue<Point> q;
    
    // 方向：上、右、下、左
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    
    q.push(start);
    visited[start.x][start.y] = true;
    parent[start.x][start.y] = Point(-1, -1);
    
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        
        if (current.x == goal.x && current.y == goal.y) {
            // 找到路径，回溯构建路径
            vector<Point> path;
            Point p = goal;
            
            while (!(p == start)) {
                path.push_back(p);
                p = parent[p.x][p.y];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                !visited[nx][ny] && map[nx][ny] == 0) {
                visited[nx][ny] = true;
                parent[nx][ny] = current;
                q.push(Point(nx, ny));
            }
        }
    }
    
    throw runtime_error("No path found");
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " <map_file> <start_x> <start_y> <goal_x> <goal_y>" << endl;
        return 1;
    }
    
    try {
        string mapFile = argv[1];
        int startX = stoi(argv[2]);
        int startY = stoi(argv[3]);
        int goalX = stoi(argv[4]);
        int goalY = stoi(argv[5]);
        
        vector<vector<int>> map = readMap(mapFile);
        Point start(startX, startY);
        Point goal(goalX, goalY);
        
        vector<Point> path = findPathBFS(map, start, goal);
        printMap(map, path);
        
    } catch (const exception& e) {
        if (string(e.what()) == "No path found") {
            cout << "I can't go to the position (" << argv[4] << "," << argv[5] << ")." << endl;
        } else {
            cerr << "Error: " << e.what() << endl;
        }
        return 1;
    }
    
    return 0;
}
