#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main()
{
    freopen("colonii.in", "w", stdout);

    int n = 5000;
    int m = 650000;

    printf("%d %d 1\n", n, m);

    for (int step = 1; m > 0; step++) {
        for (int i = 1; i + step <= n && m > 0; i++) {
            printf("%d %d\n", i, i + step);
            m--;
        }
    }

    return 0;
}
