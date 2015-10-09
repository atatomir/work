#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxCiur 100011

int n, i, t, m, p;
bool ciur[maxCiur];
vector<int> primes;

vector< pair<int, int> > need;

void compute_ciur() {
    int limit = 100000;

    for (int i = 2; i <= limit; i++) {
        if (ciur[i]) continue;

        primes.pb(i);
        for (long long j = 1LL * i * i; j <= limit; j += i) ciur[j] = true;
    }
}

int getCount(int val, int div) {
    int ans = 0;

    while (val > 0) {
        val /= div;
        ans += val;
    }

    return ans;
}

int getComb(int n, int k, int p) {
    int ans = getCount(n, p) - getCount(k, p) - getCount(n - k, p);
    return ans;
}

bool good() {
    for (auto who : need)
        if ( getComb(n + m - 2, n - 1, who.first) < who.second )
            return false;

    return true;
}

int main()
{
    freopen("far.in","r",stdin);
    freopen("far.out","w",stdout);

    compute_ciur();
    for (scanf("%d", &t); t > 0; t--) {
        scanf("%d%d%d", &n, &m, &p);
        need.clear();

        for (auto act_div : primes) {
            if (p % act_div != 0) continue;

            int cc = 0;
            while (p % act_div == 0) {
                cc ++;
                p /= act_div;
            }

            need.pb(mp(act_div, cc));
        }
        if (p > 1) need.pb(mp(p, 1));

        if (good())
            printf("1\n");
        else
            printf("0\n");
    }

    return 0;
}
