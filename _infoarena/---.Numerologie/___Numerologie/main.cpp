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

#define maxN 1301
#define inf (1251000000)

int n, m, i, j, x;
vector<int> divs[maxN];
vector<int> solves[maxN];
vector<int> primes;
int cost[maxN];

int solved[maxN];
int cnt, sumi;

int ans = inf;

bool dead[maxN];


bool cmp(const vector<int>& a, const vector<int>& b) {
    return a.size() < b.size();
}

bool can_kill(vector<int>& dad, vector<int>& son) {
    bool found;

    for (int s : son) {
        found = false;
        for (int d : dad)
            if (d == s) {found = true; break;}
        if (!found) return false;
    }

    return true;
}

void _back(int pas) {
    if (pas == primes.size()) {
        if (cnt != n) return;
        ans = sumi;
        return;
    }

    _back(pas + 1);

    sumi += cost[ primes[pas] ];
    for (int e : solves[ primes[pas] ])
        if(++solved[e] == 1) cnt++;

    if (sumi < ans) _back(pas + 1);

    sumi -= cost[ primes[pas] ];
    for (int e : solves[ primes[pas] ])
        if(--solved[e] == 0) cnt--;
}

int main()
{
    freopen("numerologie.in","r",stdin);
    freopen("numerologie.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        for (j = 2; j * j <= x; j++) {
            if (x % j) continue;
            divs[i].pb(j);
            while (x % j == 0) x /= j;
        }

        if (x != 1) {
            divs[i].pb(x);
        }
    }

    sort(divs + 1, divs + n + 1, cmp);
    for (i = 2; i <= n; i++)
        for (j = 1; j < i; j++)
            if (can_kill(divs[i], divs[j]))
                {dead[i] = true; break;}

    int pos = 0;
    for (i = 1; i <= n; i++) {
        if (dead[i]) continue;
        divs[++pos] = divs[i];

        for (int e : divs[i]) {
            primes.pb(e);
            solves[e].pb(pos);
        }
    }
    n = pos;


    ///!-------------------------------------

    sort(primes.begin(), primes.end());
    primes.resize(unique(primes.begin(), primes.end()) - primes.begin());

    random_shuffle(primes.begin(), primes.end());

    for (i = 1; i <= m; i++) scanf("%d", &cost[i]);
    _back(0);

    printf("%d", ans);

    return 0;
}
