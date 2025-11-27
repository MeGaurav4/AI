#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;
    int f, g, h;
    Node* parent;
};

// Comparator for priority queue (min-heap based on f)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// Manhattan Distance heuristic
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check if cell is valid (within grid and not blocked)
bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& grid) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0);
}

void aStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Directions: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 2D array for visited
    vector<vector<bool>> closed(rows, vector<bool>(cols, false));

    // Open list as min-heap
    priority_queue<Node*, vector<Node*>, Compare> open;

    // Start node
    Node* startNode = new Node{start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second), 0, nullptr};
    startNode->f = startNode->g + startNode->h;
    open.push(startNode);

    while(!open.empty()) {
        Node* current = open.top();
        open.pop();

        int x = current->x, y = current->y;
        closed[x][y] = true;

        // Goal reached
        if (x == goal.first && y == goal.second) {
            cout << "Path found!\n";
            vector<pair<int,int>> path;
            while(current != nullptr) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            for(auto p : path)
                cout << "(" << p.first << "," << p.second << ") ";
            cout << endl;
            return;
        }

        // Explore neighbors
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if(isValid(nx, ny, rows, cols, grid) && !closed[nx][ny]) {
                int gNew = current->g + 1;
                int hNew = heuristic(nx, ny, goal.first, goal.second);
                int fNew = gNew + hNew;

                Node* neighbor = new Node{nx, ny, gNew, hNew, fNew, current};
                open.push(neighbor);
            }
        }
    }

    cout << "No path exists!\n";
}

int main() {
    // 0 = free cell, 1 = obstacle
    vector<vector<int>> grid = {
        {0,0,0,0,0},
        {1,1,0,1,0},
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,0,0}
    };

    pair<int,int> start = {0,0};
    pair<int,int> goal = {4,4};

    aStar(grid, start, goal);
    return 0;
}
