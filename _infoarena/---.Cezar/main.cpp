#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 10011


int n, k, x, y, i;
vector<short> list[maxN];
short cnt[maxN];

struct cmp {
    bool operator()(short a, short b) {
        return cnt[a] > cnt[b] ;
    }
};

priority_queue<short, vector<short>, cmp > H;
short gr[maxN];
bitset<maxN> us;



int main()
{
    freopen("cezar.in","r",stdin);
    freopen("cezar.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);

        gr[x]++; gr[y]++;
    }

    for (i = 1; i <= n; i++) {
        cnt[i] = 1;
        if (gr[i] == 1)
            H.push(i);
    }

    int ans = 0;
    while (n > k + 1) {
        int node = H.top();
        H.pop();

        n--;
        ans += cnt[node];
        us[node] = true;

        for (auto to : list[node]) {
            if (us[to]) continue;
            cnt[to] += cnt[node];
            gr[to]--;

            if (gr[to] == 1) H.push(to);
        }
    }

    printf("%d", ans);


    return 0;
}
