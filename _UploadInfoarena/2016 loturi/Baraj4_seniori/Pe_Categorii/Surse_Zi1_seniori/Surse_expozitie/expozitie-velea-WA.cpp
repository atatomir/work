#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define int64 long long

ifstream fin("expozitie.in");
ofstream fout("expozitie.out");

#define cin fin
#define cout fout

const int maxOut = 100;

vector<int64> Solve(const vector<int>& bonus, const vector<pair<int, int>>& _queries) {
    int n = bonus.size();
    vector<int> first_encounter(maxOut, -1);
    int time = 0;
    int sum = 0;
    vector<int> elements_here;

    while (first_encounter[sum] == -1 and sum < maxOut) {
        first_encounter[sum] = time;
        for (int i = 0; i < n; i += 1, time += 1) {
            if (sum + bonus[i] >= 0) {
                sum += bonus[i];
            }

            elements_here.push_back(sum);
        }
    }

    vector<int> queries; queries.reserve(_queries.size());
    for (auto itr : _queries) {
        itr.second -= 1;
        itr.first -= 1;

        if (itr.first == -1) {
            itr.first += n;
        }

        if (itr.first > itr.second) {
            queries.push_back(-1);
            continue;
        }

        itr.second = itr.second - (itr.second - itr.first) % n; 
        queries.push_back(itr.second);
    }

    vector<int64> result; result.reserve(queries.size());

    if (not (sum < maxOut)) {
        for (auto& itr : queries) {
            if (itr == -1) {
                result.push_back(0);
                continue;
            }

            if (itr < time) {
                result.push_back(elements_here[itr]);
            } else {
                result.push_back(1LL * elements_here[itr % time] + sum + 1LL * int((itr - time - 1) / time) * (sum));
            }
        }
    } else {
        int first_position = first_encounter[sum];
        int cicle_count = time - first_encounter[sum];
        for (auto& itr : queries) {
            if (itr == -1) {
                result.push_back(0);
                continue;
            }

            if (itr < time) {
                result.push_back(elements_here[itr]);
            } else {
                result.push_back(elements_here[first_position + (itr - time) % cicle_count]);
            }
        }
    }

    return result;
}

int main() {
    int n, q; cin >> n >> q;
    vector<int> bonus(n + 1);
    cin >> bonus[0];
    for (int i = 1; i <= n; i += 1) {
        cin >> bonus[i];
        bonus[i] *= -1;
    }

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i += 1) {
        cin >> queries[i].second >> queries[i].first;
    }

    auto result = Solve(bonus, queries);
    for (auto itr : result) {
        cout << itr << '\n';
    }
    return 0;
}
