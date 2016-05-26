#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int kMod = 1e9+7;

int solve(int sigma, 
        const vector<vector<int>>& elements,
        vector<int> lines, 
        vector<int> columns) {
    int n = int(lines.size());
    int m = int(columns.size());

    bool find_line = false;
    int line_ind = -1;

    for (int i = 0; i < n; i += 1) {
        const int& itr = lines[i];
        if (itr == -1) {
            find_line = true;
            line_ind = i;
            break;
        }
    }

    if (find_line) {
        unordered_map<int, vector<int>> possible, required;
        for (int i = 0; i < m; i += 1) {
            if (columns[i] == -1) {
                possible[elements[line_ind][i]].push_back(i);
            } else if (elements[line_ind][i] != columns[i]) {
                required[elements[line_ind][i]].push_back(i);
            }
        }

        if (required.size() > 1) {
            return 0;
        }

        if (required.size() == 1) {
            const int& value = required.begin()->first;
            for (int i = 0; i < m; i += 1) {
                if (elements[line_ind][i] != value) {
                    columns[i] = elements[line_ind][i];
                }
            }
            lines[line_ind] = value;

            return solve(sigma, elements, move(lines), move(columns));
        } else {
            for (auto bucket : possible) {
                for (auto element : bucket.second) {
                    columns[element] = bucket.first;
                }
            }

            lines[line_ind] = -2;
            int sum = 1LL * (sigma - possible.size()) * solve(sigma, elements, lines, columns) % kMod;
            lines[line_ind] = -1;

            for (auto bucket : possible) {
                for (auto element : bucket.second) {
                    columns[element] = -1;
                }

                lines[line_ind] = bucket.first;
                sum += solve(sigma, elements, lines, columns);
                
                if (sum >= kMod) {
                    sum -= kMod;
                }

                lines[line_ind] = - 1;
                 
                for (auto element : bucket.second) {
                    columns[element] = bucket.first;
                } 
            }

            return sum;
        }
    } else {
        int exp = 1;
        for (int i = 0; i < m; i += 1) {
            if (columns[i] == -1) {
                exp = (1LL * exp * sigma) % kMod;
            }
        }
        return exp;
    }
}

int main() {
    ifstream cin ("entanglement.in");
    ofstream cout("entanglement.out");

    int t; cin >> t;
    int n, m, sigma;
    cin >> n >> m >> sigma;
    vector<vector<int>> elements(n, vector<int>(m, 0));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cin >> elements[i][j];
        }
    }

    int answer = solve(sigma, elements, vector<int>(n, -1), vector<int>(m, -1));

    if (t == 1) {
        if (answer) {
            cout << "DA\n";
        } else {
            cout << "NU\n";
        }
    } else {
        cout << answer << '\n';
    }
    return 0;
}                              
