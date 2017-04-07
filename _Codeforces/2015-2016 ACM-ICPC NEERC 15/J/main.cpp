#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1024
//#define DEBUG

int n, i;
int data[maxN];
int aux[maxN];

#ifdef DEBUG
int to_solve[maxN];

int ask() {
    int ans = 0;
    static int cnt = 0;

    cnt++;

    for (int i = 1; i <= n; i++)
        ans += (data[i] == to_solve[i]);

    if (ans == n) {
        cerr << cnt;
        exit(0);
    }
    return (ans == n / 2 ? 1 : 0);
}

#else

int ask() {
    for (int i = 1; i <= n; i++)
        printf("%d", data[i]);
    printf("\n");
    fflush(stdout);

    int ans;
    scanf("%d", &ans);

    if (ans == n)
        exit(0);
    return (ans > 0 ? 1 : 0);
}

#endif

int main()
{
    srand(1805);

    scanf("%d", &n);

    #ifdef DEBUG
        for (i = 1; i <= n; i++) to_solve[i] = rand() % 2;
    #endif

    do {
        for (i = 1; i <= n; i++)
            data[i] = rand() % 2;
    } while (ask() == 0);

    memcpy(aux, data, sizeof(data));
    for (i = 2; i <= n; i++) {
        data[1] ^= 1;
        data[i] ^= 1;

        aux[i] ^= ask();

        data[1] ^= 1;
        data[i] ^= 1;
    }

    memcpy(data, aux, sizeof(aux));
    ask();

    for (i = 1; i <= n; i++) data[i] ^= 1;
    ask();

    return 0;
}
