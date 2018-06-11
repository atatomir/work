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

static int n, k, pass, where, i, act;

void helpBessie(int v)
{
    n = getTrainLength();
    k = getWindowLength();
    pass = getCurrentPassIndex();
    where = getCurrentCarIndex();

    if (pass == 1) return;
    set(where % k, v);

    if (where >= k - 1) {
        act = inf;
        for (i = 0; i < k; i++)
            act = min(act, get(i));

        shoutMinimum(act);
    }
}
