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

const int st = 2;
const int en = 5498;

int get_dim(int n, int k) {
    int d;

    for (d = k / 2; d <= k; d++) {

    }
}

void helpBessie(int v)
{
    int n, k, pass, where, i, act, l, r;

    n = getTrainLength();
    k = getWindowLength();
    pass = getCurrentPassIndex();
    where = getCurrentCarIndex();

    int dim = get_dim(n, k);

    if (pass == 1) return;

    if (where == 0) {
        set(0, st);
        set(1, st);
    }
    l = get(0);
    r = get(1);

    while (l != r) {
        if (r <= st) r = en + 2;
        if (l == r) break;

        if (get(r - 2) < v) break;
        r -= 2;
    }

    {
        if (r > en) r = st;
        set(r, v);
        set(r + 1, where);
        r += 2;
    }

    if (get(l + 1) <= where - k) {
        l += 2;
        if (l > en) l = st;
    }

    if (where >= k - 1)
        shoutMinimum(get(l));

    set(0, l);
    set(1, r);
}
