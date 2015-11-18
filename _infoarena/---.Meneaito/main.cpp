#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 200011

struct my_hash {
    size_t operator()(const pair<int, int> a)const {
        return a.first * 17 + a.second;
    }
};

int n, i;
int a[maxN], b[maxN];
unordered_map< pair<int, int>, bool, my_hash > H;
vector< pair<int, int> > v;

int lim = 200000;
bool deny[maxN];

void do_it(int id) {
    if (id < a[id] || id > b[id]) return;

    if (a[id] == b[id]) {
        printf("-1");
        exit(0);
    }

    int per = 2 * (b[id] - a[id]) ;
    int t1 = id - a[id];
    int t2 = per - (id - a[id]);

    auto aux = mp(t1, per);
    if (H[aux] == false) {
        v.pb(aux);
        H[aux] = true;
    }

    /**/ aux = mp(t2, per);
    if (H[aux] == false) {
        v.pb(aux);
        H[aux] = true;
    }
}

int main()
{
    freopen("meneaito.in","r",stdin);
    freopen("meneaito.out","w",stdout);

    H.clear();

    scanf("%d", &n);
    for (i = 2; i < n; i++) scanf("%d", &a[i]);
    for (i = 2; i < n; i++) scanf("%d", &b[i]);

    for (i = 2; i < n; i++)
        do_it(i);

    for (auto who : v) {
        int per = who.second;
        int st = who.first;

        for (; st <= lim; st += per) deny[st] = true;
    }

    for (i = 0; i <= lim; i++) {
        if (!deny[i]) {
            printf("%d", i);
            return 0;
        }
    }

    printf("%d", -1);

    return 0;
}
