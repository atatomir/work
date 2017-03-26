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

#define maxN 4017

int n, i, t, ti;
vector<int> ord;

void solve() {
    int i, j;

    i = 0; j = ord.size() - 1;

    printf("1 ");
    while (i < j) {
        printf("%d %d ", ord[i], ord[j]);
        i++; j--;
    }
    printf("1\n");
}

int main()
{
    freopen("rez.in","r",stdin);
    freopen("rez.out","w",stdout);

    scanf("%d", &n);
    t = (n - 1) / 2;

    for (i = 2; i <= n; i++)
        ord.pb(i);


    for (ti = 1; ti <= t; ti++) {
        solve();
        ord.pb(ord[0]);
        for (i = 1; i < ord.size(); i++)
            ord[i - 1] = ord[i];
        ord.pop_back();
    }


    return 0;
}
