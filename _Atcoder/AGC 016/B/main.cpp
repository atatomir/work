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

int n, i, x, mini, maxi;
int cnt[maxN], l, r;

void No() {
    cout << "No";
    exit(0);
}

void Yes() {
    cout << "Yes";
    exit(0);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    mini = n + 13;
    maxi = -1;

    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        mini = min(mini, x);
        maxi = max(maxi, x);
        cnt[x]++;
    }

    if (maxi - mini > 1)
        No();

    if (maxi == mini) {
        if (maxi == n - 1)
            Yes(); //! all are 1

        l = 1; r = n / 2;
        if (l <= maxi && maxi <= r)
            Yes();
        else
            No();
    } else {
        int gr_small = cnt[mini];
        l = gr_small + 1;
        r = gr_small + (cnt[maxi] / 2);

        if (l <= maxi && maxi <= r)
            Yes();
        else
            No();
    }



    return 0;
}
