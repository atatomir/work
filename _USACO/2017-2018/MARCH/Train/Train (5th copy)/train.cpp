#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include "grader.h"

using namespace std;

const int inf = 1000000011;
const int maxMem = 5500;

void upd(int node, int l, int r, int qL, int qR, int v) {
    if (qL <= l && r <= qR) {
        int aux = get(3 * node);
        if (aux > v) set(3 * node, v);
        return;
    }

    int mid = (l + r) >> 1;
    if (qL <= mid) {
        if (get(3 * node - 2) == 0) {
            int cnt = get(0) + 1;
            set(0, cnt);

            set(3 * node - 2, cnt);
            set(3 * cnt, inf);
        }

        upd(get(3 * node - 2), l, mid, qL, qR, v);
    }

    if (qR > mid) {
        if (get(3 * node - 1) == 0) {
            int cnt = get(0) + 1;
            set(0, cnt);

            set(3 * node - 1, cnt);
            set(3 * cnt, inf);
        }

        upd(get(3 * node - 1), mid + 1, r, qL, qR, v);
    }
}

int que(int node, int l, int r, int p) {
    int ans = get(3 * node);
    if (l == r) return ans;

    int mid = (l + r) >> 1;
    if (p <= mid) {
        int aux = get(3 * node - 2);
        if (aux == 0) return ans;
        return min(ans, que(aux, l, mid, p));
    } else {
        int aux = get(3 * node - 1);
        if (aux == 0) return ans;
        return min(ans, que(aux, mid + 1, r, p));
    }
}

void helpBessie(int v)
{
    int n, k, pass, where, i, act, l, r;

    n = getTrainLength();
    k = getWindowLength();
    pass = getCurrentPassIndex();
    where = getCurrentCarIndex();

    if (pass == 0) {
        if (where == 0) {
            set(0, 1);

            set(1, 0);
            set(2, 0);
            set(3, inf);
        }

        l = where;
        r = min(n - 1, where + k - 1);
        l++; r++;

        upd(1, 1, n, l, r, v);
    } else {
        if (where >= k - 1) {
            int ans = que(1, 1, n, where + 1);
            shoutMinimum(ans);
        }
    }


}
