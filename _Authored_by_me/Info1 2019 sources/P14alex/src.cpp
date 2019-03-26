#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

//#define testing


#ifndef testing
    #include "grader.h"
#endif

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long


#ifdef testing

const vector<int>  expected = {8, 9, 3, 2, 1, 7, 6, 5, 4, 10};

int query(vector<int> v) {
    int ans = 0;
    static int count = 0;
    count++;
    for (int i = 0; i < v.size(); i++)
        if (v[i] == expected[i])
            ans++;
    
    cerr << count << "-";
    for (auto e: v) cerr << e << ' ';
    cerr << "=> " << ans << "\n";
    return ans;
}
#endif

const int maxN = 555;

int n, matches;
vector<int> answer;
vector<int> vals, pos;
vector<bool> found;
vector<bool> found_vals;

int ask(vector<int>& v) {
    int ans = query(v);
    if (ans == n) {cerr << "All done\n"; exit(0);}
    return ans;
}

vector< pair<int, int> > find_matches() {
    vector<bool> any;
    vector< pair<int, int> > modif = {};
    bool any_combo = false;

    pos.pb(pos[0]);
    vals.pb(vals[0]);
    any.clear();


    for (int i = 0; i + 1 < vals.size(); i++) {
        swap(answer[pos[i]], answer[pos[i + 1]]);
        int dif = matches - ask(answer);
        swap(answer[pos[i]], answer[pos[i + 1]]);

        if (dif == 2) {
            any_combo = true;
            modif.pb(mp(pos[i], vals[i]));
            modif.pb(mp(pos[i + 1], vals[i + 1]));
        }

        if (dif == 1) 
            any.pb(true);
        else
            any.pb(false);
    }

    //if (any_combo) cerr << "Combo\n";
    if (any_combo) return modif;
    
    int p;
    for (p = 0; p < any.size() && any[p] == true; p++);
    if (p == any.size()) return modif;

    for (int i = p + 1; i < any.size(); i++) {
        if (any[i]) {
            modif.pb(mp(pos[i + 1], vals[i + 1]));
            i++;
        }
    }

    for (int i = p - 1; i >= 0; i--) {
        if (any[i]) {
            modif.pb(mp(pos[i], vals[i]));
            i--;
        }
    }
    
    return modif;
}

void solve(int N) {
    n = N;

    vals = answer = vector<int>(n, 0); 
    found_vals = found = vector<bool>(n, false);
     

    while (!vals.empty()) {
        pos.clear();
        vals.clear();

        for (int i = 0; i < n; i++) {
            if (!found[i]) pos.pb(i);
            if (!found_vals[i]) vals.pb(i + 1);
        }

        if (vals.size() <= 1) break;

        random_shuffle(vals.begin(), vals.end());
        for (int i = 0; i < pos.size(); i++)
            answer[pos[i]] = vals[i];

        matches = ask(answer);
        if (matches == 0) continue;
        
        auto modif = find_matches();
        for (auto e : modif) {
            //cerr << "matched " << e.first << ' ' << e.second << '\n';
            answer[e.first] = e.second;
            found[e.first] = true;
            found_vals[e.second - 1] = true;
        }
    }

    ask(answer);
}

#ifdef testing
int main() {
    solve(10);
    cerr << "Expected ";
    for (auto e : expected) cerr << e << ' ';
    return 0;
}
#endif

