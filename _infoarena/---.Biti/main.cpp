#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxBit 20
#define maxNode (1 << maxBit)
#define pi pair<int, int>

int n, i, x;
int mask, lim;
bool Edge[maxNode];

int dim;
int S[maxNode];
vector<int> ans;

void virtual_dfs() {
    dim = 1;
    S[1] = 0;

    while (dim > 0) {
        int suff = S[dim];

        bool any = false;
        for (int bit = 0; bit <= 1; bit++) {
            int my_edge = (suff << 1) | bit;

            if (Edge[my_edge])
                continue;

            Edge[my_edge] = true;
            any = true;

            S[++dim] = my_edge & mask;
            break;
        }

        if (any == false) {
            ans.pb(S[dim]);
            dim--;
        }
    }
}

int main()
{
    freopen("biti.in","r",stdin);
    freopen("biti.out","w",stdout);

    scanf("%d", &n);
    mask = 1 << (n - 1);
    mask = mask - 1;
    lim = 1 << n;

    if (n == 1) {
        printf("2\n01");
        return 0;
    }

    virtual_dfs();

    printf("%d\n", n - 1 + lim);
    for (i = 1; i < n; i++)
        printf("0");
    for (i = ans.size() - 2; i >= 0; i--)
        printf("%d", ans[i] & 1);


    return 0;
}
