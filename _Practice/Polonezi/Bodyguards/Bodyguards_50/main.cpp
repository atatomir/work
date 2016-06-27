/*
 *  50 points
 */

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

int t, ti;
int n, m, cnt, i, req, no;

int ln[maxN], co[maxN];


bool check() {
    int i, j, p1, p2, need;

    reverse(ln + 1, ln + n + 1);
    reverse(co + 1, co + m + 1);

    for (i = 1; i <= n; i++) {
        if (ln[i] == 0) break;

        if (co[ ln[i] ] <= 0) return false;
        int critic = co[ ln[i] ];

        p1 = m + 1; p2 = 0;
        for (j = 1; j <= m; j++) {
            if (co[j] != critic) continue;
            p1 = min(p1, j);
            p2 = j;
        }

        need = ln[i] - p1 + 1;

        for (j = 1; j < p1; j++) co[j]--;
        for (j = p2 - need + 1; j <= p2; j++) co[j]--;
    }


    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        cnt = 0;

        for (i = 1; i <= n; i++) {
            scanf("%d%d", &req, &no);
            while (no--) ln[++cnt] = req;
        }

        n = cnt;
        sort(ln + 1, ln + n + 1);

        ///////////////////////////////

        scanf("%d", &m);
        cnt = 0;

        for (i = 1; i <= m; i++) {
            scanf("%d%d", &req, &no);
            while (no--) co[++cnt] = req;
        }

        m = cnt;
        sort(co + 1, co + m + 1);

        if (check())
            printf("1\n");
        else
            printf("0\n");
    }


    return 0;
}
