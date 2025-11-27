#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

const vector<int> goal_state = {1,2,3,4,5,6,7,8,0};


string stateToString(const vector<int>& state) {
    string s;
    for (int x : state) s += to_string(x);
    return s;
}


vector<vector<int>> getSuccessors(const vector<int>& state) {
    vector<vector<int>> successors;
    int zero_pos = find(state.begin(), state.end(), 0) - state.begin();
    int row = zero_pos / 3;
    int col = zero_pos % 3;

    vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}}; // up,down,left,right

    for (auto& d : directions) {
        int new_row = row + d.first;
        int new_col = col + d.second;
        if (new_row >= 0 && new_row < 3 && new_col >=0 && new_col < 3) {
            int new_pos = new_row * 3 + new_col;
            vector<int> new_state = state;
            swap(new_state[zero_pos], new_state[new_pos]);
            successors.push_back(new_state);
        }
    }
    return successors;
}


bool bfs(const vector<int>& start) {
    queue<vector<int>> q;
    unordered_set<string> visited;

    q.push(start);
    visited.insert(stateToString(start));

    while (!q.empty()) {
        vector<int> state = q.front(); q.pop();

        if (state == goal_state) {
            cout << "Goal reached by BFS!\n";
            return true;
        }

        for (auto& next_state : getSuccessors(state)) {
            string s = stateToString(next_state);
            if (visited.find(s) == visited.end()) {
                visited.insert(s);
                q.push(next_state);
            }
        }
    }
    return false;
}


bool dfs(const vector<int>& start) {
    stack<vector<int>> st;
    unordered_set<string> visited;

    st.push(start);
    visited.insert(stateToString(start));

    while (!st.empty()) {
        vector<int> state = st.top(); st.pop();

        if (state == goal_state) {
            cout << "Goal reached by DFS!\n";
            return true;
        }

        for (auto& next_state : getSuccessors(state)) {
            string s = stateToString(next_state);
            if (visited.find(s) == visited.end()) {
                visited.insert(s);
                st.push(next_state);
            }
        }
    }
    return false;
}

int main() {
    vector<int> start_state = {1,2,3,4,5,6,0,7,8}; // Example start

    cout << "Running BFS...\n";
    bfs(start_state);

    cout << "Running DFS...\n";
    dfs(start_state);

    return 0;
}