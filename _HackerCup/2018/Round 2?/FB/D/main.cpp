#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

typedef pair<ll, int> tp;

const int maxN = 1000011;
const ll inf = 1LL << 60;

int t, ti;
ll n, S, M, k, i;
ll L, A, X, Y, Z;
ll p[maxN], d[maxN];
pair<ll, ll> aux[maxN];

priority_queue<tp, vector<tp>, greater<tp> > H;
ll here[maxN], dp[maxN];
deque<tp> Q;

void read_bucket(ll* &pt) {
    ll i;

    scanf("%lld%lld%lld%lld%lld", &L, &A, &X, &Y, &Z);
    (*pt) = A; pt++;
    for (i = 2; i <= L; i++) {
        A = ((X * A + Y) % Z) + 1;
        (*pt) = A; pt++;
    }
}

void find_best(int pos) {
    while (!H.empty()) {
        auto act = H.top();
        H.pop();
        if (here[act.second] != act.first) continue;
        H.push(act);
        dp[pos] = min(dp[pos], act.first);
        return;
    }

    cerr << "NF\n";
}

ll solve() {
    ll i, j, ind;
    ll *pt;

    scanf("%lld%lld%lld%lld", &n, &S, &M, &k);
    M = M * 2 + 1;

    //! citire
    pt = p + 1;
    for (i = 1; i <= k; i++) read_bucket(pt);
    pt = d + 1;
    for (i = 1; i <= k; i++) read_bucket(pt);

    //! sortare
    for (i = 1; i <= n; i++) aux[i] = mp(p[i], d[i]);
    sort(aux + 1, aux + n + 1);
    for (i = 1; i <= n; i++) {
        p[i] = aux[i].first;
        d[i] = aux[i].second;
    }

    //! init
    for (i = 0; i <= n; i++) here[i] = dp[i] = inf;
    while (!H.empty()) H.pop();
    while (!Q.empty()) Q.pop_back();


    //! rezolvare
    dp[0] = 0;
    ind = 0;

    for (i = 1; i <= n; i++) {
        while (p[i] - p[ind + 1] >= M) ind++;

        //! elimina de la inceput
        while (!Q.empty()) {
            auto fr = Q.front();
            if (p[i] - p[fr.second] <= M) break;
            Q.pop_front();
            here[fr.second] = inf;
        }

        //! elimina de la sfarsit
        while (!Q.empty()) {
            auto en = Q.back();
            if (en.first > d[i]) break;
            Q.pop_back();
            here[en.second] = inf;
        }

        //! adauga la sfarsit
        if (Q.empty()) {
            dp[i] = dp[ind] + S + d[i];
            Q.push_back(mp(d[i], i));
        } else {
            dp[i] = dp[ind] + S + Q.front().first;

            auto en = Q.back();
            here[en.second] = dp[en.second] + S + d[i];
            H.push(mp(here[en.second], en.second));
            Q.push_back(mp(d[i], i));

            find_best(i);
        }

    }

    return dp[n];
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        printf("Case #%d: %lld\n", ti, solve());
    }


    return 0;
}
