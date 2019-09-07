#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <cassert>
using namespace std;

struct Info {
    int vmin, vmax, left, right;
};

bool everyValue(const vector<int>& p, int m) {
    return (int) set<int>(p.begin(), p.end()).size() == m;
}

int main() {
    ifstream fin("compact.in");
    ofstream fout("compact.out");

    int n, m;
    fin >> n >> m;

    vector<int> values(n);
    for (int& x: values) {
        fin >> x;
        assert(1 <= x && x <= m);
        x--;
    }
    assert(everyValue(values, m));

    vector<Info> posInfo(n);
    vector<Info> valInfo(n);
    vector<int> minPos(n, n), maxPos(n, 0);
    for (int i = 0; i < n; ++i) {
        posInfo[i] = Info{values[i], values[i], i, i};
        minPos[values[i]] = min(minPos[values[i]], i);
        maxPos[values[i]] = max(maxPos[values[i]], i);
    }
    for (int i = 0; i < n; ++i) {
        valInfo[i] = Info{-1, -1, -1, -1};
    }

    vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        used[i] = true;
        Info have = Info{values[i], values[i], i, i};
        Info need = Info{values[i], values[i], minPos[values[i]], maxPos[values[i]]};
        for (bool change = true; change; ) {
            change = false;
            while (have.left > need.left) {
                --have.left;
                used[have.left] = change = true;
                need.vmax = max(need.vmax, posInfo[have.left].vmax);
                need.vmin = min(need.vmin, posInfo[have.left].vmin);
                have.left = posInfo[have.left].left;
            }
            while (have.right < need.right) {
                ++have.right;
                used[have.right] = change = true;
                need.vmax = max(need.vmax, posInfo[have.right].vmax);
                need.vmin = min(need.vmin, posInfo[have.right].vmin);
                have.right = posInfo[have.right].right;
            }
            while (have.vmin > need.vmin) {
                change = true;
                --have.vmin;
                if (valInfo[have.vmin].left != -1) {
                    need.right = max(need.right, valInfo[have.vmin].right);
                    need.left = min(need.left, valInfo[have.vmin].left);
                    have.vmin = valInfo[have.vmin].vmin;
                } else {
                    need.right = max(need.right, maxPos[have.vmin]);
                    need.left = min(need.left, minPos[have.vmin]);
                }
            }
            while (have.vmax < need.vmax) {
                change = true;
                ++have.vmax;
                if (valInfo[have.vmax].left != -1) {
                    need.right = max(need.right, valInfo[have.vmax].right);
                    need.left = min(need.left, valInfo[have.vmax].left);
                    have.vmax = valInfo[have.vmax].vmax;
                } else {
                    need.right = max(need.right, maxPos[have.vmax]);
                    need.left = min(need.left, minPos[have.vmax]);
                }
            }
        }
        posInfo[need.left] = need;
        posInfo[need.right] = need;
        valInfo[need.vmin] = need;
        valInfo[need.vmax] = need;
    }
    vector<int> fans;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += 1;
        i = posInfo[i].right;
        fans.push_back(i + 1);
    }
    fout << ans << '\n';
    for (int pos: fans) {
        fout << pos << ' ';
    }
    fout << '\n';
    
}
