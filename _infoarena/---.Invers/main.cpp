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

#define maxN 10011

int t, ti, n, i;
char s[maxN];
int aux[maxN], rez[maxN];



bool solve(int l, int r) {
    if (l == 1 && aux[n] == 0) return false;

    while (l + 1 < r) {
        if (aux[l] < 0 || aux[l] >= 20 || aux[r] < 0 || aux[r] >= 20) return false;
        if (aux[l] < aux[r]) return false;

        if (aux[l] == aux[r]) {
            aux[l++] = aux[r--] = 0;
            continue;
        }

        if (aux[l] - 10 >= aux[r]) {
            int i;
            for (i = r - 1; aux[i] == 0 && i > l; aux[i--] = 9);
            //if (i == l) return false;

            if (aux[r] == 9) return false;

            aux[i]--;
            aux[r] += 10;
            aux[l] -= aux[r]; aux[r] = 0;
        }

        if (aux[l] - 1 == aux[r]) {
            aux[l + 1] += 10;
            aux[l++] = aux[r--] = 0;
            continue;
        }

        if (aux[l] != aux[r]) return false;
        l++; r--;
    }

    if (l == r)
        if (aux[l] % 2 == 1) return false;
    if (l + 1 == r && aux[l] != aux[r] && aux[l] - aux[r] != 11) return false;

    return true;
}

bool check() {
    memcpy(rez, aux, sizeof(rez));
    if (solve(1, n))
        return true;

    memcpy(aux, rez, sizeof(rez));
    if (aux[1] == 1 && n > 1) {
        aux[2] += 10;
        if (solve(2, n))
            return true;
    }

    return false;
}

int main()
{
    freopen("invers.in","r",stdin);
    freopen("invers.out","w",stdout);

    scanf("%d\n", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%s\n", s + 1);
        n = strlen(s + 1);
        for (i = 1; i <= n; i++) aux[i] = s[i] - '0';

        if (check())
            printf("DA\n");
        else
            printf("NU\n");

        for (i = 1; i <= n; i++) aux[i] = 0;
    }


    return 0;
}
