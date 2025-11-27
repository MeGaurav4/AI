#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class CSPSolver {
private:
    vector<string> variables;
    unordered_map<string, vector<string>> domains;
    vector<pair<string, string>> constraints;
    unordered_map<string, string> assignment;
    unordered_map<string, unordered_map<string, vector<string>>> pruned;

public:
    CSPSolver(const vector<string>& vars, 
              const unordered_map<string, vector<string>>& doms,
              const vector<pair<string, string>>& cons) 
        : variables(vars), domains(doms), constraints(cons) {}


    vector<string> getNeighbors(const string& var) {
        vector<string> neighbors;
        for (const auto& constraint : constraints) {
            if (constraint.first == var) {
                neighbors.push_back(constraint.second);
            } else if (constraint.second == var) {
                neighbors.push_back(constraint.first);
            }
        }
        return neighbors;
    }


    bool isConsistent(const string& var, const string& value) {
        vector<string> neighbors = getNeighbors(var);
        for (const string& neighbor : neighbors) {
            if (assignment.find(neighbor) != assignment.end()) {
                if (!constraintSatisfied(var, value, neighbor, assignment[neighbor])) {
                    return false;
                }
            }
        }
        return true;
    }


    bool constraintSatisfied(const string& var1, const string& val1,
                           const string& var2, const string& val2) {
        // For map coloring: adjacent regions must have different colors
        return val1 != val2;
    }


    bool forwardCheck(const string& var, const string& value) {
        unordered_map<string, vector<string>> prunedThisStep;
        
        vector<string> neighbors = getNeighbors(var);
        for (const string& neighbor : neighbors) {
            if (assignment.find(neighbor) == assignment.end()) { 
                vector<string> prunedValues;
                

                vector<string> domainCopy = domains[neighbor];
                
                for (const string& val : domainCopy) {
                    if (!constraintSatisfied(var, value, neighbor, val)) {
                        
                        auto it = find(domains[neighbor].begin(), domains[neighbor].end(), val);
                        if (it != domains[neighbor].end()) {
                            domains[neighbor].erase(it);
                            prunedValues.push_back(val);
                        }
                    }
                }
                
           
                if (!prunedValues.empty()) {
                    prunedThisStep[neighbor] = prunedValues;
                }
                
               
                if (domains[neighbor].empty()) {
                  
                    restoreDomains(prunedThisStep);
                    return false;
                }
            }
        }
        
    
        if (!prunedThisStep.empty()) {
            pruned[var] = prunedThisStep;
        }
        
        return true;
    }


    void restoreDomains(const unordered_map<string, vector<string>>& prunedValues) {
        for (const auto& entry : prunedValues) {
            const string& var = entry.first;
            const vector<string>& values = entry.second;
            for (const string& value : values) {
                domains[var].push_back(value);
            }
        }
    }

  
    string selectUnassignedVariable() {
        string bestVar = "";
        int minDomainSize = INT_MAX;
        
        for (const string& var : variables) {
            if (assignment.find(var) == assignment.end()) {
                if (domains[var].size() < minDomainSize) {
                    minDomainSize = domains[var].size();
                    bestVar = var;
                }
            }
        }
        
        return bestVar;
    }


    bool backtrackSearch() {
        return backtrack();
    }


    bool backtrack() {
        // Check if assignment is complete
        if (assignment.size() == variables.size()) {
            return true;
        }
        
     
        string var = selectUnassignedVariable();
        if (var.empty()) {
            return true;
        }
        
       
        vector<string> domainCopy = domains[var];
        
     
        for (const string& value : domainCopy) {
            if (isConsistent(var, value)) {
                
                assignment[var] = value;
                
                
                if (forwardCheck(var, value)) {
                    // Recursively solve
                    if (backtrack()) {
                        return true;
                    }
                }
                
               
                assignment.erase(var);
                if (pruned.find(var) != pruned.end()) {
                    restoreDomains(pruned[var]);
                    pruned.erase(var);
                }
            }
        }
        
        return false;
    }

 
    bool solve() {
        return backtrackSearch();
    }

   
    void printSolution() {
        if (solve()) {
            cout << "Solution found:" << endl;
            for (const string& var : variables) {
                cout << var << " = " << assignment[var] << endl;
            }
        } else {
            cout << "No solution exists!" << endl;
        }
    }

 
    unordered_map<string, string> getAssignment() {
        return assignment;
    }

    
    bool verifyConstraints() {
        for (const auto& constraint : constraints) {
            const string& var1 = constraint.first;
            const string& var2 = constraint.second;
            
            if (assignment.find(var1) != assignment.end() && 
                assignment.find(var2) != assignment.end()) {
                if (!constraintSatisfied(var1, assignment[var1], var2, assignment[var2])) {
                    return false;
                }
            }
        }
        return true;
    }
};


void australiaMapColoring() {
    cout << "=== Australia Map Coloring with Forward Checking ===" << endl << endl;
    
    // Variables (Australian regions)
    vector<string> variables = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};
    
    // Domains (possible colors)
    vector<string> colors = {"Red", "Green", "Blue"};
    unordered_map<string, vector<string>> domains;
    for (const string& var : variables) {
        domains[var] = colors;
    }
    
  
    vector<pair<string, string>> constraints = {
        {"WA", "NT"}, {"WA", "SA"}, {"NT", "SA"}, {"NT", "Q"},
        {"SA", "Q"}, {"SA", "NSW"}, {"SA", "V"}, {"Q", "NSW"}, {"NSW", "V"}
    };
    
  
    CSPSolver csp(variables, domains, constraints);
    
    cout << "Variables: ";
    for (const string& var : variables) {
        cout << var << " ";
    }
    cout << endl;
    
    cout << "Available colors: ";
    for (const string& color : colors) {
        cout << color << " ";
    }
    cout << endl;
    
    cout << "Constraints (adjacent regions):" << endl;
    for (const auto& constraint : constraints) {
        cout << "  " << constraint.first << " - " << constraint.second << endl;
    }
    cout << endl;
    
    csp.printSolution();
    
    if (csp.solve()) {
        cout << endl << "Verification:" << endl;
        cout << "Checking all constraints..." << endl;
        
        auto assignment = csp.getAssignment();
        bool allSatisfied = true;
        
        for (const auto& constraint : constraints) {
            const string& var1 = constraint.first;
            const string& var2 = constraint.second;
            string color1 = assignment[var1];
            string color2 = assignment[var2];
            bool satisfied = (color1 != color2);
            
            cout << "  " << var1 << "(" << color1 << ") != " 
                      << var2 << "(" << color2 << "): " 
                      << (satisfied ? "true" : "false") << endl;
            
            allSatisfied = allSatisfied && satisfied;
        }
        
        cout << endl << "All constraints satisfied: " 
                  << (allSatisfied ? "true" : "false") << endl;
    }
}



int main() {
    // Run the Australia map coloring example
    australiaMapColoring();
    
    return 0;
}