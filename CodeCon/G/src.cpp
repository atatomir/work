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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 55;
int n, k, i, j;
int pos[maxN];

bool check(int dist) {
    int last = pos[1];
    int need = k - 1;

    for (i = 2; i <= n; i++) {
        if (pos[i] - last < dist) continue;
        last = pos[i];
        need--;
    }
    return need <= 0;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%d", &pos[i]);
    sort(pos + 1, pos + n + 1);

    int ans = 0;
    for (int step = 1 << 30; step > 0; step >>= 1)
        if (check(ans + step))
            ans += step;

    printf("%d", ans);



    return 0;
}
