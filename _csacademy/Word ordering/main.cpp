#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111111

int n, i, pos;
char alph[30];
char s[maxN];
int dim[maxN];
int bg[maxN];

int id[maxN];
int M[ 333 ];


bool cmp(int id1, int id2) {
    int pos1 = bg[id1];
    int pos2 = bg[id2];

    int lim = min(dim[id1], dim[id2]);
    for (int i = 1; i <= lim && s[pos1] == s[pos2]; i++, pos1++, pos2++) ;
    return M[ s[pos1] ] < M[ s[pos2] ];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s\n%d\n", alph, &n);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + pos);
        bg[i] = pos;
        dim[i] = strlen(s + pos);

        pos += dim[i] + 2;
        id[i] = i;
    }

    for (i = 0; i < 26; i++) {
        M[alph[i]] = i + 1;
        M[alph[i] - 'a' + 'A'] = i + 30;
    }

    sort(id + 1, id + n + 1, cmp);
    for (i = 1; i <= n; i++)
        printf("%s\n", s + bg[ id[i] ]);

    return 0;
}
