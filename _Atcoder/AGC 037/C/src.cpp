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

const int maxN = 200011;

int n;
int a[maxN], b[maxN];
priority_queue< pair<int, int> > H;
ll answer;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        H.push(mp(b[i], i));
    }

    while (!H.empty()) {
        auto act = H.top(); H.pop();
        int pos = act.second;

        int prv = (pos + n - 1) % n;
        int nxt = (pos + 1) % n;
        int sum = b[prv] + b[nxt];

        if (b[pos] < a[pos]) continue;

        int can = (b[pos] - a[pos]) / sum;
        if (can == 0) continue;
        answer += 1LL * can;
        b[pos] -= sum * can;
        H.push(mp(b[pos], pos));
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            printf("-1");
            exit(0);
        }
    }

    printf("%lld", answer);

    return 0;
}
