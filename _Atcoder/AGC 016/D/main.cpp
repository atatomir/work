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

#define maxN 100011

int n, i;
int a[maxN], b[maxN], xoro, dif;
map<int, int> M, M_a, M_b;
vector<int> vals;

vector<int> neg, poz;

void no_sol() {
    printf("-1");
    exit(0);
}

void give_sol(int x) {
    printf("%d", x);
    exit(0);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]), xoro ^= a[i], vals.pb(a[i]), M[a[i]]++;
    for (i = 1; i <= n; i++) scanf("%d", &b[i]), vals.pb(b[i]), M[b[i]]--, dif += (a[i] != b[i]);

    for (i = 1; i <= n; i++) {
        if (a[i] == b[i]) continue;
        M_a[a[i]]++;
        M_b[b[i]]++;
    }

    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    for (auto e : vals) {
        if (M[e] < -1 || M[e] > 1) no_sol();
        if (M[e] == -1)
            neg.pb(e);
        if (M[e] == 1)
            poz.pb(e);
    }

    if (neg.size() > 1) no_sol();
    if (poz.size() > 1) no_sol();



    if (poz.empty()) {
        //! perfect match
        if (dif == 0) give_sol(0);
        if (dif == 2) give_sol(2);
        give_sol(dif + 1);

        if (M_a[xoro] > 0)
            give_sol(dif);
        else
            give_sol(dif + 1);
    } else {
        if (dif == 1) give_sol(1);
        if (dif == 2) give_sol(2);

        give_sol(dif + 1);

        int from = poz[0];
        int to = neg[0];
        int c1, c2;
        c1 = c2 = 0;

        for (i = 1; i <= n; i++){
            if (a[i] == b[i]) continue;
            if (a[i] != from) continue;
            if (b[i] == to) c1++;
            else            c2++;
        }

        if (c2 == 0)
            give_sol(dif + 1);
        else
            give_sol(dif);
    }


    return 0;
}
