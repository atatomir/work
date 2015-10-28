#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int n, i, k, x, y;
int pos1, pos2;

int main()
{
    freopen("sn.in","r",stdin);
    freopen("sn.out","w",stdout);

    pos1 = pos2 = 1;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x, &y);
        if (x > pos1 || x > pos2) cerr << "Error";
        if (pos1 < pos2) {
            pos1 = max(pos1, y);
            printf("0\n");
        } else {
            pos2 = max(pos2, y);
            printf("1\n");
        }
    }

    return 0;
}
