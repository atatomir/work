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

#define maxN 200011

struct aib {
    int n;
    int data[maxN];

    void init(int _n) {
        n = _n;
        memset(data, 0, sizeof(data));
    }

    int zrs(int x) {
        return (x & (x - 1)) ^ x;
    }

    void add(int pos, int v) {
        while (pos <= n) {
            data[pos] += v;
            pos += zrs(pos);
        }
    }

    int sum(int pos) {
        int ans = 0;
        while (pos > 0) {
            ans += data[pos];
            pos -= zrs(pos);
        }
        return ans;
    }
};

int n, i, odd, done;
char s[maxN];
vector<int> where[33];
bool used[maxN];
int pr[maxN];
aib work;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (i = 1; i <= n; i++)
        where[s[i] - 'a'].pb(i);

    odd = -1;
    for (i = 0; i < 26; i++) {
        if (where[i].size() & 1) {
            if (odd == -1) {
                odd = i;
            } else {
                printf("-1");
                return 0;
            }
        }

        int p1 = 0;
        int p2 = where[i].size() - 1;
        while (p1 < p2) {
            pr[where[i][p1]] = where[i][p2];
            pr[where[i][p2]] = where[i][p1];
            p1++; p2--;
        }
    }

    work.init(n);
    for (i = 1; done < n / 2; i++) {
        if (used[i]) continue;
        if (pr[i] == 0) continue;

        done++;
        ans += 1LL * (i - done) - work.sum(i);
        ans += 1LL * (n - done + 1 - pr[i]) + (work.sum(pr[i]));
        used[i] = used[pr[i]] = true;
        work.add(pr[i], +1);
    }

    printf("%lld", ans);


    return 0;
}
