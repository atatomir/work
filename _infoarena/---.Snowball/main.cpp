#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxM 10011

int n, m, i, x, id;
unordered_map<int, int> M;
int data[maxM];

int ans_max, act;
ll ans_cnt;

int main()
{
    freopen("snowball.in","r",stdin);
    freopen("snowball.out","w",stdout);

    scanf("%d%d", &m, &n);
    for (i = 1; i <= m; i++) {
        scanf("%d", &x);
        M[x] = i;
    }

    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        id = M[x];

        if (id != 0) {
            if (id == 1)
                data[1] = i;
            else
                data[id] = data[id - 1];
        }

        act = data[m];
        ans_cnt += 1LL * (i - act);
        ans_max = max(ans_max, i - act);
    }

    printf("%d %lld", ans_max, ans_cnt);


    return 0;
}
