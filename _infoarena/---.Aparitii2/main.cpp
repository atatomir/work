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

#define maxN 1000011

int n, m, i, mini;
char A[maxN], B[maxN];
int pref[maxN], suff[maxN];

int ans[maxN];

void zalgo(int n, int m, char* A, char *B, int *dest) {
    vector<char> data;
    vector<int> lcp;
    int i, dim, bg, sz;

    dim = n + m + 1;
    data.resize(dim + 3);
    lcp = vector<int>(dim + 3, 0);

    for (i = 1; i <= m; i++) data[i] = B[i];
    data[m + 1] = '#';
    for (i = 1; i <= n; i++) data[m + 1 + i] = A[i];
    data[dim + 1] = '@';

    bg = sz = 0;
    for (i = 2; i <= dim; i++) {
        if (i <= bg + sz - 1) lcp[i] = min(lcp[i - bg + 1], (bg + sz - 1) - i + 1);
        while (data[ lcp[i] + 1 ] == data[i + lcp[i]]) lcp[i]++;
        if (i + lcp[i] - 1 > bg + sz - 1) {
            bg = i;
            sz = lcp[i];
        }
    }

    for (i = 1; i <= n; i++) dest[i] = lcp[m + 1 + i];
}

int main()
{
    freopen("aparitii2.in","r",stdin);
    freopen("aparitii2.out","w",stdout);

    scanf("%s\n%s", A + 1, B + 1);
    n = strlen(A + 1);
    m = strlen(B + 1);

    zalgo(n, m, A, B, pref);
    reverse(A + 1, A + n + 1);
    reverse(B + 1, B + m + 1);
    zalgo(n, m, A, B, suff);
    reverse(suff + 1, suff + n + 1);

    for (i = 1; i + m - 1 <= n; i++) {
        mini = min(pref[i], suff[i + m - 1]);
        mini = min(mini, m / 2);
        ans[mini]++;
    }

    for (i = m / 2; i > 0; i--) ans[i] += ans[i + 1];
    for (i = 1; i <= m / 2; i++) printf("%d\n", ans[i]);


    return 0;
}
