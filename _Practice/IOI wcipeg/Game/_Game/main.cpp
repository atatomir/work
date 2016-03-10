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

#define life_is_beautiful true

ll n, m, k, i, a, b, c, d, op;

//! --------------GCD basic---------------------

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

//! ---------Small nodes management-------------

struct small_node {
    small_node *lSon, *rSon;
    ll gcd;

    small_node() {
        lSon = rSon = NULL;
        gcd = 0;
    }
};

void small_update(small_node* act, int l, int r, int pos, ll val) {
    if (l == r) {
        act->gcd = val;
        return;
    }

    int mid = (l + r) >> 1;
    if (pos <= mid) {
        if (act->lSon == NULL) act->lSon = new small_node();
        small_update(act->lSon, l, mid, pos, val);
    } else {
        if (act->rSon == NULL) act->rSon = new small_node();
        small_update(act->rSon, mid + 1, r, pos, val);
    }

    act->gcd = 0;
    if (act->lSon) act->gcd = gcd(act->gcd, act->lSon->gcd);
    if (act->rSon) act->gcd = gcd(act->gcd, act->rSon->gcd);
}

ll small_query(small_node* act, int l, int r, int qL, int qR) {
    if (act == NULL) return 0;
    if (qL <= l && r <= qR)
        return act->gcd;

    ll ans = 0;

    int mid = (l + r) >> 1;
    if (qL <= mid)
        ans = gcd(ans, small_query(act->lSon, l, mid, qL, qR));
    if (qR > mid)
        ans = gcd(ans, small_query(act->rSon, mid + 1, r, qL, qR));

    return ans;
}

//!----------Big nodes management----------------

int qx, qy;
int qx1, qx2, qy1, qy2;

struct big_node {
    big_node* lSon, *rSon;
    small_node* working_tree;

    big_node() {
        lSon = rSon = NULL;
        working_tree = new small_node;
    }
};

void refresh_branch(big_node *_D, big_node *_A, big_node *_B, int pos) {
    small_node *A, *B, *D;
    A = B = D = NULL;

    if (_A != NULL) A = _A->working_tree;
    if (_B != NULL) B = _B->working_tree;
    if (_D != NULL) D = _D->working_tree;

    int l = 1;
    int r = m;

    while (life_is_beautiful) {
        D->gcd = 0;
        if (A != NULL) D->gcd = gcd(D->gcd, A->gcd);
        if (B != NULL) D->gcd = gcd(D->gcd, B->gcd);

        if (l == r) break;

        int mid = (l + r) >> 1;
        if (pos <= mid) {
            r = mid;

            if (D->lSon == NULL) D->lSon = new small_node;
            D = D->lSon;

            if (A) A = A->lSon;
            if (B) B = B->lSon;
        } else {
            l = mid + 1;

            if (D->rSon == NULL) D->rSon = new small_node;
            D = D->rSon;

            if (A) A = A->rSon;
            if (B) B = B->rSon;
        }
    }

    //! done
}

void big_update(big_node* act, int l, int r, ll val) {
    if (l == r) {
        small_update(act->working_tree, 1, m, qy, val);
        return;
    }

    int mid = (l + r) >> 1;
    if (qx <= mid) {
        if (act->lSon == NULL) act->lSon = new big_node;
        big_update(act->lSon, l, mid, val);
    } else {
        if (act->rSon == NULL) act->rSon = new big_node;
        big_update(act->rSon, mid + 1, r, val);
    }

    refresh_branch(act, act->lSon, act->rSon, qy);
}

ll big_query(big_node* act, int l, int r) {
    if (act == NULL) return 0;
    if (qx1 <= l && r <= qx2)
        return small_query(act->working_tree, 1, m, qy1, qy2);

    ll ans = 0;

    int mid = (l + r) >> 1;
    if (qx1 <= mid)
        ans = gcd(ans, big_query(act->lSon, l, mid));
    if (qx2 > mid)
        ans = gcd(ans, big_query(act->rSon, mid + 1, r));

    return ans;
}

big_node *Head;

//! ---------------------------------------------


void update(int ln, int co, ll val) {
    qx = ln;
    qy = co;

    big_update(Head, 1, n, val);
}

ll query(int x1, int y1, int x2, int y2) {
    qx1 = x1;
    qy1 = y1;
    qx2 = x2;
    qy2 = y2;

    return big_query(Head, 1, n);
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.out", "w", stdout);

    scanf("%lld%lld%lld", &n, &m, &k);
    Head = new big_node;

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
