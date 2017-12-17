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
#define lSon (node << 1)
#define rSon (lSon | 1)

struct aint {
    int data[4 * maxN + 11], add[4 * maxN + 11];

    void build(int node, int l, int r) {
        if (l == r) {
            data[node] = l;
            add[node] = 0;
            return;
        }

        int mid = (l + r) >> 1;
        build(lSon, l, mid);
        build(rSon, mid + 1, r);
        data[node] = l;
        add[node] = 0;
    }

    void upd(int node, int l, int r, int qL, int qR) {
        if (qL <= l && r <= qR) {
            data[node]--;
            add[node]--;
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid) upd(lSon, l, mid, qL, qR);
        if (qR > mid) upd(rSon, mid + 1, r, qL, qR);
        data[node] = (min(data[lSon], data[rSon]) + add[node]);
    }
};

int n, i;
int c[maxN];
aint work;

int main()
{
    freopen("greedy.in","r",stdin);
    freopen("greedy.out","w",stdout);

    cin >> n;
    work.build(1, 1, n);

    for (i = 1; i <= n; i++) {
        cin >> c[i];
        c[i] = n - c[i];
        work.upd(1, 1, n, c[i], n);
        if (work.data[1] == 0) {
            cout << n - i;
            return 0;
        }
    }

    cout << 0;



    return 0;
}
