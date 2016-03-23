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

#define maxN 3501

struct Box {
    int x, y, z;

    void read() {
        scanf("%d%d%d", &x, &y, &z);
    }

    bool operator<(const Box& who)const  {
        return x < who.x;
    }
};



int n, t, ans, i;
Box work[maxN];
int aib[maxN][maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int x, int y, int v) {
    int _y = y;

    while (x <= n) {
        y = _y;
        while (y <= n) {
            aib[x][y] = max(aib[x][y], v);
            y += zrs(y);
        }
        x += zrs(x);
    }
}

void rm(int x, int y) {
    int _y = y;

    while (x <= n) {
        y = _y;
        while (y <= n) {
            aib[x][y] = 0;
            y += zrs(y);
        }
        x += zrs(x);
    }
}

int query(int x, int y) {
    int ans = 0;
    int _y = y;

    while (x) {
        y = _y;
        while (y) {
            ans = max(ans, aib[x][y]);
            y -= zrs(y);
        }
        x -= zrs(x);
    }

    return ans;
}


int main()
{
    freopen("cutii.in","r",stdin);
    freopen("cutii.out","w",stdout);

    scanf("%d%d", &n, &t);

    for (int ti = 1; ti <= t; ti++) {
        ans = 0;

        for (i = 1; i <= n; i++) work[i].read();
        sort(work + 1, work + n + 1);

        for (i = 1; i <= n; i++) {
            int act = query(work[i].y, work[i].z);
            ans = max(ans, act + 1);
            add(work[i].y, work[i].z, act + 1);
        }

        printf("%d\n", ans);

        for (i = 1; i <= n; i++)
            rm(work[i].y, work[i].z);
    }


    return 0;
}
