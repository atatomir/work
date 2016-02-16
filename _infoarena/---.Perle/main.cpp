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

#define maxN 10111

int n, i, t;
int v[maxN];

int check(int pos, char op) {
    int i;
    int rem = n - pos + 1;

    if (rem == 0) return -1;

    if (op == 'A') {
        return pos + 1;
    }
    if (op == 'B') {
        if (v[pos] == 3) return -1;
        if (v[pos] == 2) { //! 2B
            return check(pos + 1, 'B');
        } else { //! 1A3AC
            if (rem < 5) return -1;
            if (v[pos + 2] != 3) return - 1;
            return check(pos + 4, 'C');
        }
    }
    if (op == 'C') {
        if (v[pos] == 2) return pos + 1;
        if (v[pos] == 1) { //! 12A
            if (rem < 3) return -1;
            if (v[pos + 1] != 2) return -1;

            return pos + 3;
        } else { //! 3BC
            int wh = check(pos + 1, 'B');
            if (wh == -1) return -1;
            return check(wh, 'C');
        }
    }

}

int main()
{
    freopen("perle.in","r",stdin);
    freopen("perle.out","w",stdout);

    for (scanf("%d", &t); t > 0; t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            scanf("%d", &v[i]);

        bool good = false;
        good |= check(1, 'A') == n + 1;
        good |= check(1, 'B') == n + 1;
        good |= check(1, 'C') == n + 1;

        if (good)
            printf("1\n");
        else
            printf("0\n");
    }


    return 0;
}
