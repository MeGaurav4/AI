#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<string, vector<vector<string>>> rules;  // rule base
vector<string> facts;                       // known facts

bool backwardChaining(string goal) {
    // If goal already known
    for (auto &fact : facts)
        if (fact == goal)
            return true;

    // If goal has no rules to infer it
    if (rules.find(goal) == rules.end())
        return false;

    // Check each rule whose conclusion is the goal
    for (auto &conditions : rules[goal]) {
        bool allTrue = true;
        for (auto &c : conditions) {
            if (!backwardChaining(c)) { // recursively check each condition
                allTrue = false;
                break;
            }
        }
        if (allTrue)
            return true;
    }
    return false;
}

int main() {
    // Example knowledge base
    rules["C"] = { {"A", "B"} };
    rules["D"] = { {"C"} };
    facts = {"A", "B"};

    string goal;
    cout << "Enter goal: ";
    cin >> goal;

    if (backwardChaining(goal))
        cout << "Goal " << goal << " is TRUE.\n";
    else
        cout << "Goal " << goal << " cannot be proven.\n";

    return 0;
}
