#include "xylophone.h"
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

const int maxN = 5011;

static int a[maxN], i, j, n;
static int dif[maxN];
static bool on[maxN];

bool check() {
    int mini = n + 13;
    int i, j;

    a[0] = 0;
    for (i = 1; i < n; i++)
        a[i] = a[i - 1] + dif[i - 1];

    for (i = 0; i < n; i++)
        mini = min(mini, a[i]);

    for (i = 0; i < n; i++)
            a[i] -= mini;

    memset(on, 0, sizeof(on));
    for (i = 0; i < n; i++) {
        if (a[i] >= n) return false;
        if (on[a[i]]) return false;
        on[a[i]] = true;
    }

    for (i = 0; a[i] != 0; i++);
    for (j = 0; a[j] != n - 1 && j < n; j++);

    return i < j;
}

void detect_pitch(int N) {

    n = N;
	for (i = 0; i + 1 < n; i++)
        dif[i] = ask(i, i + 1);

    for (i = 0; i + 2 < n; i++) {
        if (abs(dif[i]) + abs(dif[i + 1]) != ask(i, i + 2)) {
            if (dif[i] > 0)
                dif[i + 1] *= -1;
        } else {
            if (dif[i] < 0)
                dif[i + 1] *= -1;
        }
    }

    if (!check()) {
        for (i = 0; i + 1 < n; i++) dif[i] *= -1;
        check();
    }

    for (i = 0; i < n; i++) answer(i, a[i]);
}
