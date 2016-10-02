#include "aliens.h"

#include <cstdio>
#include <cassert>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int n, m, k;
vector<int> R, C;

void norm_read() {
    assert(3 == scanf("%d %d %d", &n, &m, &k));
    vector<int> r(n), c(n);
    for (int i = 0; i < n; i++) {
        assert(2 == scanf("%d %d", &r[i], &c[i]));
    }

    R = r;
    C = c;
}

void rand_read() {
    assert(3 == scanf("%d %d %d", &n, &m, &k));
    vector<int> r(n), c(n);
    for (int i = 0; i < n; i++) {
        r[i] = rand() % m;
        c[i] = rand() % m;
    }

    R = r;
    C = c;
}

void testing(int cnt) {
    srand(time(NULL));

    while (cnt--) {
        printf("%d\n", cnt);

        freopen("test.in", "r", stdin);
        rand_read();

        printf("%lld\n", take_photos(n, m, k, R, C));
        if (take_photos(n, m, k, R, C) != take_photos2(n, m, k, R, C)) {
            printf("error");
            take_photos(n, m, k, R, C);
            return;
        }
    }
}

int main() {
    freopen("test.in", "r", stdin);

    //testing(10000);
    //return 0;

    norm_read();
    long long ans = take_photos(n, m, k, R, C);


    printf("%lld\n", ans);
    return 0;
}
