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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 1000011;
int n, m, i, cnt, done[maxN];
priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > H;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) H.push(mp(0, i));

    for (i = 1; i <= m; i++) {
        scanf("%d", &cnt);

        int tm = H.top().first;
        int id = H.top().second;
        H.pop();
        done[id]++;

        tm += cnt;
        if (done[id] % 10 == 0) tm += 5;
        H.push(mp(tm, id));
    }

    for (i = 1; i <= n; i++) printf("%d ", done[i]);


    return 0;
}
