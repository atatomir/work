#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, x, cnt;
int go[maxN];
int gr_in[maxN];
int gr_out[maxN];
bool us[maxN];

int id;
int iter[maxN];

int ans;
int sol[maxN][2];

//! ------------------------------

void dfs_good(int node) {
    cnt++;
    us[node] = true;

    if (us[go[node]] == false)
        dfs_good(go[node]);
}

void check_all_good() {
    int i;

    for (i = 1; i <= n; i++)
        if (gr_in[i] != 1)
            return;

    dfs_good(1);
    if (cnt == n) {
        printf("0");
        exit(0);
    }
}

//! ------------------------------

void dfs_rm(int node) {
    us[node] = true;
    iter[node] = id;

    if (us[go[node]]) {
        if (iter[ go[node] ] != id) //! s-a ajuns in alta parcurgere
            return;

        gr_in[ go[node] ]--;
        go[node] = 0;
        ans++;
    } else {
        dfs_rm(go[node]);
    }
}

void remove_any_cycle() {
    int i;

    //! coada + ciclu
    memset(us, 0, sizeof(us));
    for (i = 1; i <= n; i++) {
        if (gr_in[i] == 0) {
            id++;
            dfs_rm(i);
        }
    }

    //! ciclu
    for (i = 1; i <= n; i++) {
        if (us[i] == false) {
            id++;
            dfs_rm(i);
        }
    }
}

//! ------------------------------

void remove_wrong_edges() {
    int i;

    for (i = 1; i <= n; i++) {
        if (go[i] == 0) continue;

        if (gr_in[ go[i] ] > 1) {
            gr_in[ go[i] ]--;
            go[i] = 0;
            ans++;
        }
    }
}

//! ------------------------------

int pos;

void dfs_get(int node) {
    if (go[node] == 0)
        sol[pos][1] = node;
    else
        dfs_get( go[node] );
}

void get_first_last() {
    int i;

    pos = 0;

    for (i = 1; i <= n; i++) {
        if (gr_in[i] != 0) continue;

        sol[++pos][0] = i;
        dfs_get(i);
    }
}

int main()
{
    freopen("telefon2.in","r",stdin);
    freopen("telefon2.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        go[i] = x;

        gr_in[x]++;
        gr_out[i]++;
    }

    check_all_good();
    remove_any_cycle();
    remove_wrong_edges();

    get_first_last();

    //! ------------------------------

    printf("%d\n", ans);
    for (i = 1; i < ans; i++)
        printf("%d %d\n", sol[i][1], sol[i + 1][0]);
    printf("%d %d\n", sol[ans][1], sol[1][0]);

    return 0;
}
