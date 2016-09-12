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

#define maxN 1024
#define sigma 26

struct stringer {
    int dim, i;
    char data[maxN];
    int nxt[maxN][sigma];

    void init() {
        memset(data, 0, sizeof(data));
        scanf("%s\n", data + 1);
        dim = strlen(data + 1);

/*
        // fake
        dim = 1000;
        for (i = 1; i <= dim; i++) data[i] = 'B';
        //
*/

        memset(nxt[dim + 1], 0, sizeof(nxt[dim + 1]));
        for (i = dim; i > 0; i--) {
            memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
            nxt[i][data[i] - 'A'] = i;
        }
    }
};

int t, ti;
int k, i, j, p1, p2, done;
stringer A, B;

int dp[maxN][maxN];

void comp_dp() {
    int i, j, n, m;
    char *aa = A.data;
    char *bb = B.data;

    memset(dp, 0, sizeof(dp));
    n = A.dim; m = B.dim;

    for (i = n; i > 0; i--) {
        for (j = m; j > 0; j--) {
            if (aa[i] == bb[j])
                dp[i][j] = dp[i + 1][j + 1] + 1;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
        }
    }
}

int main()
{
    freopen("seif.in","r",stdin);
    freopen("seif.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &k);
        A.init();
        B.init();


        comp_dp();
        done = 0;


        p1 = p2 = 1;
        while (p1 <= A.dim && p2 <= B.dim) {
            for (i = sigma - 1; i >= 0; i--) {
                if (A.nxt[p1][i] == 0 || B.nxt[p2][i] == 0) continue;
                if (dp[A.nxt[p1][i]][B.nxt[p2][i]] + done < k) continue;

                printf("%c", 'A' + i);
                p1 = A.nxt[p1][i] + 1;
                p2 = B.nxt[p2][i] + 1;
                done++;

                break;
            }

            if (i == -1) break;
        }

        printf("\n");
    }


    return 0;
}
