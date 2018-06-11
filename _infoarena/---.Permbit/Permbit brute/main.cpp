#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1024

int n, m, tp, i;
string s[maxN];
vector<int> p;
vector< vector<int> > ans;

bool check() {
    int i, j;

    for (i = 1; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (s[i][j] != s[i + 1][p[j]])
                return false;
        }
    }

    return true;
}

int main()
{
    freopen("permbit.in","r",stdin);
    freopen("permbit.ok","w",stdout);

    cin >> tp >> n >> m;
    for (i = 1; i <= n; i++) cin >> s[i];

    for (i = 0; i < m; i++) p.pb(i);
    do {
        if (check())
            ans.pb(p);
    } while (next_permutation(p.begin(), p.end()));

    if (tp == 1 || tp == 2) {
        sort(ans.begin(), ans.end());
        int c = (0 + ans.size() - 1) / 2;
        for (auto e : ans[c]) cout << e + 1 << ' ';
    } else {
        cout << ans.size();
    }



    return 0;
}
