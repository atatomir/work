#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 20

int t, test, n, i, j;
int better[maxN][maxN];
int ans[maxN][2];

int perm[maxN];
int point[maxN];

queue<int> Q;

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.ok","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                scanf("%d", &better[i][j]);

        if (n == 16)
            continue;

        for (i = 1; i <= n; i++) {
            ans[i][0] = 20;
            ans[i][1] = 0;
        }

        for (i = 1; i <= n; i++)
            perm[i] = i;


        do {
            while (!Q.empty()) Q.pop();
            for (i = 1; i <= n; i++) {
                Q.push(perm[i]);
                point[i] = n / 2;
            }


            for (i = 1; i < n; i++) {
                int id1 = Q.front(); Q.pop();
                int id2 = Q.front(); Q.pop();

                if (better[id1][id2]) {
                    point[id1] >>= 1;
                    Q.push(id1);
                } else {
                    point[id2] >>= 1;
                    Q.push(id2);
                }
            }

            for (i = 1; i <= n; i++) {
                ans[i][0] = min(ans[i][0], point[i] + 1);
                ans[i][1] = max(ans[i][1], point[i] + 1);
            }
        } while (next_permutation(perm + 1, perm + n + 1));

        printf("Case #%d: \n", test);
        for (i = 1; i <= n; i++)
            printf("%d %d\n", ans[i][0], ans[i][1]);
        printf("\n");
    }

    return 0;
}
