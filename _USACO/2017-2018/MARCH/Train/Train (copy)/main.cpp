#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdio>
#include "grader.h"

using namespace std;

static const int maxN = 100011;
static const int maxMem = 5500;

static int n, k, i, v[maxN], p;
static int car_index, pass_index;
static int mem[maxMem];

int getTrainLength() {
    return n;
}

int getWindowLength() {
    return k;
}

int getCurrentCarIndex() {
    return car_index;
}

int getCurrentPassIndex() {
    return pass_index;
}

void set(int x, int y) {
    if (x < 0 || x >= maxMem) {
        cerr << "Error in mem\n";
        return;
    }

    mem[x] = y;
}

int get(int x) {
    if (x < 0 || x >= maxMem) {
        cerr << "Err2";
        return 0;
    }
    return mem[x];
}

void shoutMinimum(int x) {
    printf("%d\n", x);
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);

    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++) scanf("%d", &v[i]);
    p = 0;

    pass_index = 0;
    for (i = 0; i < n; i++) {
        car_index = i;
        helpBessie(v[i]);
    }

    pass_index = 1;
    for (i = 0; i < n; i++) {
        car_index = i;
        helpBessie(v[i]);
    }

    return 0;
}
