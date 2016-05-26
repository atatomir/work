#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

ifstream fin("purification.in");
ofstream fout("purification.out");

#define cin fin
#define cout fout

int Solve(const vector<int>& zerglings, const vector<int>& roots, const vector<vector<int>>& childrens) {
    auto Merge = [&](const vector<int>& lhs, const vector<int>& rhs) -> vector<int> {
        vector<vector<pair<int, int>>> dp(lhs.size() + 1, vector<pair<int, int>>(rhs.size() + 1, {+inf, 0}));
        for (int i = 0; i <= int(lhs.size()); i += 1) {
            for (int j = 0; j <= int(rhs.size()); j += 1) {
                dp[i][j] = {+inf, 0};
            }
        }

        dp[0][0] = {0, 0};
        for (int l = 0; l <= int(lhs.size()); l += 1) {
            for (int r = 0; r <= int(rhs.size()); r += 1) {
                if (l) {
                    int cost = (l + r) * lhs[l - 1] + dp[l - 1][r].first;
                    if (cost < dp[l][r].first) {
                        dp[l][r] = {cost, 0};
                    }
                }

                if (r) {
                    int cost = (r + l) * rhs[r - 1] + dp[l][r - 1].first;
                    if (cost < dp[l][r].first) {
                        dp[l][r] = {cost, 1};
                    }
                }
            }
        }

        int l = int(lhs.size());
        int r = int(rhs.size());

        vector<int> result;
        while (l + r > 0) {
            if (dp[l][r].second == 0) {
                l -= 1;
                result.push_back(lhs[l]);
            } else {
                r -= 1;
                result.push_back(rhs[r]);
            }
        }

        reverse(result.begin(), result.end());
        return result;
    };

    function<vector<int>(int)> GetOrder;

    GetOrder = [&](int root) -> vector<int> {
        vector<int> result = {};

        for (auto child : childrens[root]) {
            result = Merge(result, GetOrder(child));
        }

        result.insert(result.begin(), zerglings[root]);

        return result;
    };

    auto GetCost = [&](const vector<int>& v) -> int {
        int result = 0;
        for (int i = 0; i < int(v.size()); i += 1) {
            result += v[i] * i;
        }
        return result;
    };

    int result = 0;
    for (auto itr : roots) {
        result += GetCost(GetOrder(itr));
    }

    return result;
}

int main() {
    int n; cin >> n;

    vector<int> zerglings(n);
    vector<int> roots = {n};
    vector<vector<int>> childrens(n + 1);


    zerglings.resize(n + 1);

    for (int i = 0; i < n; i += 1) {
        cin >> zerglings[i];
    }

    for (int i = 0; i < n; i += 1) {
        int x; cin >> x;
        if (x == -1) {
            childrens[n].push_back(i);
        } else {
            childrens[x].push_back(i);
        }
    }

    cout << Solve(zerglings, roots, childrens) << '\n';
    return 0;
}
