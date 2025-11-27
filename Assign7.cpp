#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// Structure for a rule (IF conditions THEN conclusion)
struct Rule {
    vector<string> conditions;
    string conclusion;
};

bool allConditionsTrue(const vector<string>& conditions, const unordered_set<string>& facts) {
    for (const string& cond : conditions) {
        if (facts.find(cond) == facts.end())
            return false;
    }
    return true;
}

int main() {
    // --- Step 1: Define the Knowledge Base ---
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C", "D"}, "E"},
        {{"E"}, "F"}
    };

    // --- Step 2: Define initial facts ---
    unordered_set<string> facts = {"A", "B", "D"};

    // --- Step 3: Forward Chaining Process ---
    bool newFactInferred = true;
    while (newFactInferred) {
        newFactInferred = false;
        for (const auto& rule : rules) {
            // If all conditions of a rule are true
            if (allConditionsTrue(rule.conditions, facts) &&
                facts.find(rule.conclusion) == facts.end()) {

                cout << "Inferred: " << rule.conclusion << " (from rule) " << endl;
                facts.insert(rule.conclusion);
                newFactInferred = true;
                }
        }
    }

    // --- Step 4: Display final inferred facts ---
    cout << "\nFinal set of facts: ";
    for (const auto& f : facts) {
        cout << f << " ";
    }
    cout << endl;

    return 0;
}
