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

#define maxN 100011

int n, i, x, v;
int cnt[maxN];

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> x;
        if (x != 0) cnt[x - 1]++;
        cnt[x]++;
        cnt[x + 1]++;
    }

    for (i = 1; i <= 100001; i++)
        if (cnt[i] > cnt[v])
            v = i;

    cout << cnt[v];



    return 0;
}
