#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include "grader.h"

using namespace std;

static const int inf = 1000000011;
static const int maxMem = 5500;

void helpBessie(int v)
{
    int n, k, pass, where, i, act;

    n = getTrainLength();
    k = getWindowLength();
    pass = getCurrentPassIndex();
    where = getCurrentCarIndex();

    if (pass == 1) return;

    if (where == 0) set(0, 0);
    act = get(0);

    while (act > 0) {
        if (get(2 * act - 1) < v) break;
        act--;
    }

    act++;
    set(0, act);
    set(2 * act - 1, v);
    set(2 * act, where);

    if (get(2) <= where - k) {
        act--;
        set(0, act);

        for (i = 1; i <= 2 * act; i++)
            set(i, get(i + 2));
    }

    if (where >= k - 1)
        shoutMinimum(get(1));
}
