#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 65666

const ll def = 10000000000LL;

int n, i;
int v[maxN];

ll sum;
ll added;
deque< pair<ll, int> > DQ;

void rm_front(int cnt) {
    while (DQ.front().second < cnt) {
        sum -= (DQ.front().first + added) * DQ.front().second;
        cnt -= DQ.front().second;
        DQ.pop_front();
    }

    sum -= (DQ.front().first + added) * cnt;
    DQ.front().second -= cnt;
    if (DQ.front().second == 0) DQ.pop_front();
}

int main()
{
    freopen("caraibe.in","r",stdin);
    freopen("caraibe.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n - 2; i++) scanf("%d", &v[i]);

    DQ.pb(mp(def, 1));
    DQ.pb(mp(0, 1));
    added = 0;
    sum = def;

    for (i = n - 2; i > 0; i--) {
        int need = (n - i) - v[i];

        rm_front(need);
        added++;
        sum += v[i];

        if (DQ.back().first == -added)
            DQ.back().second += need;
        else
            DQ.push_back(mp(-added, need));

        if (DQ.front().first == def - sum - added)
            DQ.front().second++;
        else
            DQ.push_front(mp(def - sum - added, 1));

        sum = def;
    }

    printf("%lld", DQ.front().first + added);

    return 0;
}
