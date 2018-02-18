#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define mod 998244353

string s;

map<string, int> dp;

void add(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int solve(string s) {
    int i, j, k, sz, n;
    vector<int> aux = vector<int>(s.size() + 2, 0);
    string saux;

    auto &act = dp[s];
    if (act != 0) return act - 1;

    n = s.size();
    aux[0] = 1;

    for (i = 1; i <= n; i++) {
        add(aux[i], aux[i - 1]);
        if (s[i - 1] == '1') add(aux[i], aux[i - 1]);

        for (sz = 1; 2 * sz <= i; sz++) {
            saux.clear();

            for (j = 0; j < sz; j++) saux.pb(s[i - j - 1]);
            for (k = 2; k * sz <= i; k++) {
                for (j = 0; j < sz; j++)
                    saux[j] = min(saux[j], s[i - j - 1 - (k - 1) * sz]);

                add(aux[i], (1LL * aux[i - k * sz] * solve(saux)) % mod );
            }
        }
    }

    act = aux[n] + 1;
    return aux[n];
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> s;
    cout << solve(s);



    return 0;
}
