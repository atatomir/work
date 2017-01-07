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

#define maxN 111
#define sigma 26

int n, i, j;
char s[maxN][maxN];
int dim[maxN];
int p[maxN];

vector<int> list[sigma + 11];
int gr[sigma + 11];
char sol[sigma + 11];


void no_sol() {
    printf("NE");
    exit(0);
}

void add_rel(int id1, int id2) {
    int i;
    int lim = min(dim[id1], dim[id2]);

    for (i = 1; i <= lim; i++) {
        if (s[id1][i] == s[id2][i]) continue;
        list[ s[id1][i] - 'a' ].pb( s[id2][i] - 'a' );
        gr[ s[id2][i] - 'a' ]++;
        return;
    }

    if (dim[id1] > dim[id2]) no_sol();
}

void solve() {
    int i;
    char last = 'a';

    for (int steps = 1; steps <= sigma; steps++) {
        for (i = 0; i < sigma; i++) {
            if (gr[i] != 0) continue;

            sol[i] = last;
            last++;
            gr[i] = -1;


            for (auto to : list[i])
                gr[to]--;
        }
    }

    if (last != 'z' + 1) no_sol();
    for (i = 0; i < sigma; i++) {
        for (int to : list[i]) {
            if (sol[i] > sol[to])
                no_sol();
        }
    }

    printf("DA\n");
    for (i = 0; i < sigma; i++)
        printf("%c", sol[i]);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1), dim[i] = strlen(s[i] + 1);
    for (i = 1; i <= n; i++) scanf("%d", &p[i]);

    for (i = 2; i <= n; i++) {
        int id1 = p[i - 1];
        int id2 = p[i];

        add_rel(id1, id2);
    }

    solve();


    return 0;
}
