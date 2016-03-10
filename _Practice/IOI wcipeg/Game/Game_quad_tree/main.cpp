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

struct node {
    ll gcd;
    node* son[4];

    node() {
        gcd = 0;
        son[0] = son[1] = son[2] = son[3] = NULL;
    }
};

ll n, m, k, i;
ll op, a, b, c, d;

node *Head;
int q_x1, q_x2, q_y1, q_y2;
ll q_val;

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);

    while (b) {
        a %= b;
        swap(a, b);
    }

    return a;
}

void quad_update(node* act, int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        act->gcd = q_val;
        return;
    }

    int mid_x = (x1 + x2) >> 1;
    int mid_y = (y1 + y2) >> 1;

    if (q_x1 <= mid_x && q_y1 <= mid_y) {
        if (act->son[0] == NULL) act->son[0] = new node();
        quad_update(act->son[0], x1, y1, mid_x, mid_y);
    }

    if (q_x1 <= mid_x && q_y1 > mid_y) {
        if (act->son[1] == NULL) act->son[1] = new node();
        quad_update(act->son[1], x1, mid_y + 1, mid_x, y2);
    }

    if (q_x1 > mid_x && q_y1 <= mid_y) {
        if (act->son[2] == NULL) act->son[2] = new node();
        quad_update(act->son[2], mid_x + 1, y1, x2, mid_y);
    }


    if (q_x1 > mid_x && q_y1 > mid_y) {
        if (act->son[3] == NULL) act->son[3] = new node();
        quad_update(act->son[3], mid_x + 1, mid_y + 1, x2, y2);
    }

    act->gcd = 0;
    if (act->son[0]) act->gcd = gcd(act->gcd, act->son[0]->gcd);
    if (act->son[1]) act->gcd = gcd(act->gcd, act->son[1]->gcd);
    if (act->son[2]) act->gcd = gcd(act->gcd, act->son[2]->gcd);
    if (act->son[3]) act->gcd = gcd(act->gcd, act->son[3]->gcd);
}

ll quad_query(node* act, int x1, int y1, int x2, int y2) {
    if (act == NULL) return 0;
    if (x1 > x2 || y1 > y2) return 0;

    if (q_x1 <= x1 && x2 <= q_x2 && q_y1 <= y1 && y2 <= q_y2)
        return act->gcd;

    int mid_x = (x1 + x2) >> 1;
    int mid_y = (y1 + y2) >> 1;

    ll ans = 0;

    if (q_x1 <= mid_x && q_y1 <= mid_y)
        ans = gcd(ans, quad_query(act->son[0], x1, y1, mid_x, mid_y));
    if (q_x1 <= mid_x && q_y2 > mid_y)
        ans = gcd(ans, quad_query(act->son[1], x1, mid_y + 1, mid_x, y2));
    if (q_x2 > mid_x && q_y1 <= mid_y)
        ans = gcd(ans, quad_query(act->son[2], mid_x + 1, y1, x2, mid_y));
    if (q_x2 > mid_x && q_y2 > mid_y)
        ans = gcd(ans, quad_query(act->son[3], mid_x + 1, mid_y + 1, x2, y2));

    return ans;
}

void update(int ln, int co, ll val) {
    q_x1 = ln;
    q_y1 = co;
    q_val = val;

    quad_update(Head, 1, 1, n, m);
}

ll query(int x1, int y1, int x2, int y2) {
    q_x1 = x1;
    q_x2 = x2;
    q_y1 = y1;
    q_y2 = y2;

    return quad_query(Head, 1, 1, n, m);
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    Head = new node();

    scanf("%lld%lld%lld", &n, &m, &k);

    for (i = 1; i <= k; i++) {
        scanf("%lld%lld%lld%lld", &op, &a, &b, &c);
        if (op == 1) {
            update(a + 1, b + 1, c);
        } else {
            scanf("%lld", &d);
            printf("%lld\n", query(a + 1, b + 1, c + 1, d + 1));
        }
    }


    return 0;
}
