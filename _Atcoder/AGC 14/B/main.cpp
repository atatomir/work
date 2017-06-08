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

int n, m, i, x, y;
int cnt[maxN];

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> m;
    for (i = 1; i <= m; i++) {
        cin >> x >> y;
        cnt[x]++; cnt[y]++;
    }

    for (i = 1; i <= n; i++) {
        if (cnt[i] & 1) {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";


    return 0;
}
