#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 777

struct Circle {
    int x, y, R;

    void read() {
        scanf("%d%d%d", &x, &y, &R);
        x++;
        y++;
    }

    bool is_in(int xx, int yy) {
        int dist = (x - xx) * (x - xx) + (y - yy) * (y - yy) ;
        return dist < R * R;
    }
};

int n, h, l, i, j;
Circle C[maxN];

int mat[maxN];
int from_l[maxN];
int from_r[maxN];
stack<int> work;
int ans;

bool is_ok(int x, int y) {
    for (int i = 1; i <= n; i++)
        if (C[i].is_in(x, y))
            return false;
    return true;
}

void compute_l() {
    int i;

    while (!work.empty()) work.pop();
    work.push(0);

    for (i = 1; i <= h; i++) {
        while (!work.empty()) {
            if (mat[i] > mat[work.top()]) break;
            work.pop();
        }
        from_l[i] = work.top();
        work.push(i);
    }
}

void compute_r() {
    int i;

    while (!work.empty()) work.pop();
    work.push(h + 1);

    for (i = h; i > 0; i--) {
        while (!work.empty()) {
            if (mat[i] > mat[work.top()]) break;
            work.pop();
        }
        from_r[i] = work.top();
        work.push(i);
    }
}

int main()
{
    freopen("amax.in","r",stdin);
    freopen("amax.out","w",stdout);

    scanf("%d%d%d", &h, &l, &n);
    l++; h++;

    for (i = 1; i <= n; i++)
        C[i].read();

    mat[0] = mat[h + 1] = -1;

    for (i = 1; i <= l; i++) {
        for (j = 1; j <= h; j++) {
            if (is_ok(i, j))
                mat[j]++;
            else
                mat[j] = 0;
        }

        compute_l();
        compute_r();

        for (j = 1; j <= h; j++) {
            ans = max(ans, (mat[j] - 1) * (j - from_l[j] + from_r[j] - j - 2));
        }
    }

    printf("%d", ans);

    return 0;
}
