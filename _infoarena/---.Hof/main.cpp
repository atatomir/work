#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int n, i, l, r;
pair<ll, ll> Q[100011];

ll last, sum;
pair<ll, ll> fr;

int main()
{
    freopen("hof.in","r",stdin);
    freopen("hof.out","w",stdout);

    scanf("%d", &n);

    if (n == 1) {
        printf("1");
        return 0;
    }

    if (n == 2) {
        printf("3");
        return 0;
    }

    last = 3; sum = 0;
    Q[l = r = 1] = mp(4, 6);

    for (i = 3; i <= n; i++) {
        fr = Q[l]; l++;

        if (last != 3 && sum <= n) {
            Q[++r] = (mp(last + 1, last + fr.first - 1));
            sum += fr.first - 1;
        }

        last += fr.first;
        if (++fr.first <= fr.second) Q[--l] = fr;
    }

    printf("%lld", last);


    return 0;
}
