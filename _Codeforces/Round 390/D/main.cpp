#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 300011

int n, k, i, j, last, cnt;
pair<ll, ll> intr[maxN];
vector< pair<ll, ll> > events;
ll start_pos;
pair<ll, ll> ans;
ll l, r, dist;

multiset<ll> S;
int rem;


int main()
{
    //freopen("test.in","r",stdin);

    events.reserve(2 * n);
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%lld%lld", &intr[i].first, &intr[i].second);

    events.clear();
    for (i = 1; i <= n; i++) {
        events.pb(mp(intr[i].first, +i));
        events.pb(mp(intr[i].second + 1, -i));
    }

    sort(events.begin(), events.end());

    start_pos = 1LL << 60;
    ans = mp(0, 0);

    cnt = 0;
    for (i = 0; i < events.size(); i = j) {

        for (j = i; j < events.size(); j++) {
            if (events[i].first != events[j].first) break;

            if (events[j].second < 0) {
                if (rem > 0) {
                    rem--;
                    continue;
                }

                cnt--;
                auto it = S.begin();
                S.erase(it);
            } else {
                cnt++;
                S.insert(intr[events[j].second].second);
            }

        }


        if (cnt >= k) {
            while (cnt > k) {
                auto it = S.begin();
                S.erase(it);
                cnt--;
                rem++;
            }

            dist = *S.begin() - events[i].first + 1;
            ans = max(ans, mp(dist, events[i].first));
        }

    }

    printf("%lld\n", ans);

    if (ans.first == 0) {
        for (i = 1; i <= k; i++)
            printf("%d ", i);
    } else {
        l = ans.second; r = l + ans.first - 1;
        for (i = 1; i <= n && k > 0; i++) {
            if (intr[i].first <= l && r <= intr[i].second) {
                k--;
                printf("%d ", i);
            }
        }
    }


    return 0;
}
