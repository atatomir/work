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

#define maxN 71
#define move(a,b) ans.pb(mp(a, b))
#define inf (1LL << 40)

int n, m, i;
ll dp[maxN][maxN]; //! dp[pegs][discs]
int prov[maxN][maxN];

vector< pair<int, int> > ans;
vector<int> act[maxN];

vector<int> v3(int a, int b, int c) {
    static vector<int> aux;
    aux.clear();

    aux.pb(a); aux.pb(b); aux.pb(c);
    return aux;
}


ll compute(int p, int d) {
    if (dp[p][d]) return dp[p][d];

    if (p == 3) {
        prov[p][d] = d;

        dp[p][d] = (1LL << d) - 1;
        if (d >= 60) dp[p][d] = inf;

        dp[p][d] = min(dp[p][d], inf);
        return dp[p][d];
    }

    dp[p][d] = (1LL << d) - 1;
    if (d >= 60) dp[p][d] = inf;

    prov[p][d] = d;
    for (int k = 1; k < d; k++) {
        ll aux = compute(p, k) + compute(p - 1, d - k) + compute(p, k);
        if (aux < dp[p][d]) {
            dp[p][d] = aux;
            prov[p][d] = k;
        }
    }

    dp[p][d] = min(dp[p][d], inf);
    return dp[p][d];
}

void just_three(int d, vector<int> pegs) {
    if (d == 0) return;

    just_three(d - 1, v3(pegs[0], pegs[2], pegs[1]));
    move(pegs[0], pegs[2]);
    just_three(d - 1, v3(pegs[1], pegs[0], pegs[2]));
}

void roll_back(int d, vector<int> pegs) {
    if (prov[pegs.size()][d] == d) {
        just_three(d, v3(pegs[0], pegs[1], pegs.back()));
        return;
    }

    vector<int> aux;
    int k = prov[pegs.size()][d];

    //! move k from 0 to 1
    aux = pegs;
    swap(aux[1], aux[ aux.size() - 1 ]);
    roll_back(k, aux);

    //! move d - k from 0 to last
    aux.pop_back();
    swap(aux[1], aux[ aux.size() - 1 ]);
    roll_back(d - k, aux);

    //! move k from 1 to last
    aux = pegs;
    swap(aux[1], aux[0]);
    roll_back(k, aux);
}

void print(int s, int d) {
    printf("move %d from %d to %d ", act[s].back(), s, d);
    if (act[d].size()) printf("atop %d", act[d].back());
    printf("\n");

    act[d].pb(act[s].back());
    act[s].pop_back();
}



int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    printf("%lld\n", compute(m, n));

    vector<int> aux; aux.clear();
    for (i = 1; i <= m; i++) aux.pb(i);

    for (i = n; i > 0; i--) act[1].pb(i);
    roll_back(n, aux);
    for (i = 0; i < ans.size(); i++)
        print(ans[i].first, ans[i].second);


    //! ---------------------------
    cerr << ans.size();
    //for (int e : act[m]) cerr << e << ' ';

    return 0;
}
