#include <bits/stdc++.h>
using namespace std;

using KB = unordered_map<string, vector<string>>;

void add_fact(KB &kb, const string &parent, const string &child) {
    kb[parent].push_back(child);
}

unordered_map<string, vector<string>> build_reverse(const KB &kb) {
    unordered_map<string, vector<string>> rev;
    for (auto &p : kb) {
        for (auto &c : p.second) rev[c].push_back(p.first);
    }
    return rev;
}

bool is_parent(const KB &kb, const unordered_map<string, vector<string>> &rev,
               const string &a, const string &b) {
    auto it = kb.find(a);
    if (it == kb.end()) return false;
    for (auto &ch : it->second) if (ch == b) return true;
    return false;
}

bool is_sibling(const unordered_map<string, vector<string>> &rev,
                const string &a, const string &b) {
    if (a == b) return false;
    auto pa = rev.find(a), pb = rev.find(b);
    if (pa == rev.end() || pb == rev.end()) return false;
    for (auto &p1 : pa->second)
        for (auto &p2 : pb->second)
            if (p1 == p2) return true;
    return false;
}

bool is_ancestor(const KB &kb, const unordered_map<string, vector<string>> &rev,
                 const string &a, const string &b) {
    if (a == b) return false;
    unordered_set<string> seen;
    stack<string> st;
    st.push(a);
    while (!st.empty()) {
        string cur = st.top(); st.pop();
        auto it = kb.find(cur);
        if (it == kb.end()) continue;
        for (auto &child : it->second) {
            if (child == b) return true;
            if (!seen.count(child)) { seen.insert(child); st.push(child); }
        }
    }
    return false;
}

bool is_grandparent(const KB &kb, const unordered_map<string, vector<string>> &rev,
                    const string &a, const string &b) {
    auto it = kb.find(a);
    if (it == kb.end()) return false;
    for (auto &mid : it->second) {
        if (is_parent(kb, rev, mid, b)) return true;
    }
    return false;
}

int main() {
    KB kb;

    add_fact(kb, "rajesh", "amit");
    add_fact(kb, "rajesh", "priya");
    add_fact(kb, "sunita", "amit");
    add_fact(kb, "sunita", "priya");

    add_fact(kb, "amit", "rahul");
    add_fact(kb, "amit", "sneha");

    add_fact(kb, "priya", "kiran");
    add_fact(kb, "priya", "arjun");

    add_fact(kb, "rahul", "meera");

    auto rev = build_reverse(kb);

    cout << "Prolog-style Family KB. Query forms:\n";
    cout << "1 parent A B      -> is A parent of B?\n";
    cout << "2 sibling A B     -> are A and B siblings?\n";
    cout << "3 ancestor A B    -> is A ancestor of B?\n";
    cout << "4 grandparent A B -> is A grandparent of B?\n";
    cout << "5 exit\n\n";

    while (true) {
        cout << "cmd> ";
        string cmd; if (!(cin >> cmd)) break;
        if (cmd == "5" || cmd == "exit") break;

        string a, b;
        if (cmd == "1" || cmd == "parent") {
            cin >> a >> b;
            cout << (is_parent(kb, rev, a, b) ? "Yes\n" : "No\n");
        } else if (cmd == "2" || cmd == "sibling") {
            cin >> a >> b;
            cout << (is_sibling(rev, a, b) ? "Yes\n" : "No\n");
        } else if (cmd == "3" || cmd == "ancestor") {
            cin >> a >> b;
            cout << (is_ancestor(kb, rev, a, b) ? "Yes\n" : "No\n");
        } else if (cmd == "4" || cmd == "grandparent") {
            cin >> a >> b;
            cout << (is_grandparent(kb, rev, a, b) ? "Yes\n" : "No\n");
        } else {
            cout << "Unknown cmd. Use 1..5 or parent/sibling/ancestor/grandparent.\n";
        }
    }

    cout << "Bye.\n";
    return 0;
}
