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

ll m, ini, i;
ll nxt, cnt, how, need, aux, sum;
pair< ll, ll > ans;
multiset<ll> pk;

void get_next() {
    while ( (nxt * nxt * nxt) + sum >= (nxt + 1) * (nxt + 1) * (nxt + 1) ) {
        nxt++;
        cnt = 1;
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%I64d", &m);
    ini = m;

    nxt = 1; cnt = 1;
    pk.clear();

    while (m >= nxt * nxt * nxt) {
        m -= nxt * nxt * nxt;
        sum += nxt * nxt * nxt;
        how++; cnt++;

        pk.insert(nxt * nxt * nxt);
        get_next();
    }

    ans = mp(how, sum);

    for (i = 1; i <= 2 * how; i++) {
        sum += nxt * nxt * nxt;
        cnt++; how++;
        pk.insert(nxt * nxt * nxt);

        if (sum <= ini) {
            ans = max(ans, mp(how, sum));
            get_next();
            continue;
        }

        while (sum > ini) {

            auto it = pk.lower_bound(sum - ini);

            if (*it == nxt * nxt * nxt) {
                if (it != pk.begin())
                    it--;
                else
                    break;
            }


            sum -= *it;
            pk.erase(it);
            how--;

        }

        get_next();
        ans = max(ans, mp(how, sum));
    }

    printf("%I64d %I64d", ans.first, ans.second);

    return 0;
}
