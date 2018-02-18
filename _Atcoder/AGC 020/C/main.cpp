#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2018
#define maxLen 4000011

int n, i, a[maxN], need, sum;
bitset<maxLen> act;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    act.reset(); act[0] = 1;


    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    sort(a + 1, a + n + 1);

    need = (sum + 1) / 2;
    for (i = 1; i <= n; i++) {
        act = act | (act << a[i]);
        if (act[need]) {
            printf("%d", need);
            return 0;
        }
    }

    while (act[need] == 0) need++;
    printf("%d", need);


    return 0;
}
