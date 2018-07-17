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

const int maxN = 111;

int n, i, j, ans;
int a[maxN];

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (i = 1; i <= n; i = j) {
        for (j = i; j <= n; j++)
            if (a[i] != a[j])
                break;

        ans += (j - i) / 2;
    }

    cout << ans;


    return 0;
}
