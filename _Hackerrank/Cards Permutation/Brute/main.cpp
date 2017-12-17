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

#define maxN 300011
#define mod 1000000007

int n, i;
int a[maxN];
vector<int> perm;

bool check() {
    int i;

    for (i = 1; i <= n; i++) {
        if (a[i] != 0 && a[i] != perm[i - 1])
            return false;
    }

    return true;
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    cin >> n; perm = {};
    for (i = 1; i <= n; i++)
        cin >> a[i], perm.pb(i);

    int cnt = 0;
    int ans = 0;
    do {
        cnt++;
        if (check())
            ans += cnt, ans %= mod;
    } while (next_permutation(perm.begin(), perm.end()));

    cout << ans;

    return 0;
}
