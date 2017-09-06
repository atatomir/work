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
#define maxH 555

int n, h, i;
int a, b, c, d, l, r;
vector<int> list[maxH];
int in[maxH], out[maxH];
bool us[maxN], any;

void no_sol() {
    printf("NO");
    exit(0);
}

void dfs(int node) {
    us[node] = true;
    if (in[node] != out[node]) any = true;
    if (in[node] == 0 && out[node] == 0) any = true;
    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &h);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if (c == 0) l = a;
        else        l = -c;

        if (d == 0) r = -b;
        else        r = d;

        l += h;
        r += h;
        list[l].pb(r);
        list[r].pb(l);
        in[r]++;
        out[l]++;
    }

    for (i = 1; i <= h; i++)
        if (out[i + h] < in[i + h])
            no_sol();

    for (i = 1; i <= h; i++)
        if (out[-i + h] > in[-i + h])
            no_sol();

    for (i = 1; i <= h; i++) {
        if (!us[i + h]) {
            any = false;
            dfs(i + h);
            if (!any) no_sol();
        }

        if (!us[-i + h]) {
            any = false;
            dfs(-i + h);
            if (!any) no_sol();
        }
    }


    printf("YES");

    return 0;
}
