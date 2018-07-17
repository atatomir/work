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

const int maxN = 711;

int n, m, i, j, x, y, S, D;
vector<int> list[maxN];

int cnt_S, cnt_D;
int assoc[maxN];
int from_S[maxN], from_D[maxN];
int last_S, last_D;
vector< pair<int, int> > data;
vector<int> knap;
int bonus;

bool possib[maxN];

int cnt_edges(int x) {
    return (x * (x - 1)) / 2;
}

void solve() {
    int i, j;

    cnt_S = 1;
    assoc[1] = 1;
    for (auto e : list[1]) from_S[e]++;
   

    bool any = true;
    while (any) {
        any = false;

        for (i = 1; i <= n; i++) {
            if (assoc[i]) continue;
            if (cnt_S == from_S[i] && cnt_D == from_D[i]) continue;
            if (cnt_S != from_S[i] && cnt_D != from_D[i]) {
                cout << -1;
                exit(0);
            }

            if (cnt_S == from_S[i]) {
                cnt_S++;
                assoc[i] = 1;
                for (auto e : list[i]) from_S[e]++;
                any = true;
        
                //cerr << i << " to RED1" << '\n';
                break;
            }

            if (cnt_D == from_D[i]) {
                cnt_D++;
                assoc[i] = 2;
                for (auto e : list[i]) from_D[e]++;
                any = true;

                //cerr << i << " to BLUE2\n";
                break;
            }
        }

        //for (i = 1; i <= n; i++) cerr << assoc[i] << ' ';
        //cerr << '\n';

        if (any) continue;

        data.pb(mp(cnt_S - last_S, cnt_D - last_D));
        last_S = cnt_S;
        last_D = cnt_D;

        for (i = 1; assoc[i] && i <= n; i++);
        if (i > n) break;

        cnt_S++;
        assoc[i] = 1;
        for (auto e : list[i]) from_S[e]++;
        any = true;

        //cerr << i << " to forced RED1\n";
    }
    
    for (auto e : data) {
        bonus += min(e.first, e.second);
        knap.pb(max(e.first, e.second) - min(e.first, e.second));
        if (knap.back() == 0) knap.pop_back();
    }

    possib[0] = true;
    for (auto e : knap) {
        for (j = n - e; j >= 0; j--)
            possib[j + e] |= possib[j];
    }

    int sol = cnt_edges(n); 
    for (i = 0; i <= n; i++) {
        if (!possib[i]) continue;
        sol = min(sol, cnt_edges(bonus + i) + cnt_edges(n - (bonus + i)));
    }

    cout << sol;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    if (m == cnt_edges(n)) {
        cout << cnt_edges(n / 2) + cnt_edges((n + 1) / 2);
        return 0;
    }

    solve();

    return 0;
}
