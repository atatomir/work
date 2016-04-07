#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 222

int n, m, i, j, x, y, z, opt, rel, rez, cnt;
bitset<maxN> data[3 * maxN];
vector<int> list[maxN];
vector<int> ids[maxN];
bool us[maxN];

vector<int> not_fixed;
int ans[maxN];



void dfs(int node) {
    us[node] = true;
    for (int to : list[node])
        if (!us[to])
            dfs(to);
}

void precompute() {
    int i, j, k;
    bool found;

    i = 1; j = 1;

    while (i <= rel && j < rez) {
        //! find a suitable ecuation
        found = false;
        for (k = i; k <= rel; k++) {
            if (data[k][j] == 0) continue;
            found = true;
            swap(data[i], data[k]);
            break;
        }

        if (!found) {
            not_fixed.pb(j);
            j++;
            continue;
        }

        //! remove other relations with variable j
        for (k = i + 1; k <= rel; k++)
            if (data[k][j])
                data[k] = data[k] ^ data[i];

        i++; j++;
    }
}

void solve() {
    int i, j;

    for (i = rel; i > 0; i--) {
        int vr;
        for (vr = 1; vr < rez && data[i][vr] == 0; vr++);
        if (vr == rez) continue;

        ans[vr] = data[i][rez];
        for (j = vr + 1; j < rez; j++) {
            if (data[i][j] == 0) continue;
            ans[vr] ^= ans[j];
        }

    }
}




int main()
{
    freopen("bcolor.in","r",stdin);
    freopen("bcolor.out","w",stdout);

    scanf("%d%d%d", &n, &m, &cnt);
    for (i = 1; i <= 3 * n; i++) data[i].reset();
    rez = m + 1;

    for (i = m; i >= 1; i--) {
        scanf("%d%d%d", &x, &y, &z);
        data[x][i] = 1;
        data[y][i] = 1;

        if (z == 1)
            data[n + (++opt)][i] = 1, data[n + opt][rez] = 0;
        if (z == 2)
            data[n + (++opt)][i] = 1, data[n + opt][rez] = 1;

        list[x].pb(y); ids[x].pb(i);
        list[y].pb(x); ids[y].pb(i);
    }

    dfs(1);
    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        for (j = 0; j < list[i].size(); j++) {
            int to = list[i][j];

            if (i > to) continue;
            data[n + (++opt)][ ids[i][j] ] = 1;
            data[n + opt][rez] = 0;
        }
    }

    rel = n + opt;
    precompute();


    cnt--;
    for (i = 0; i < not_fixed.size(); i++) {
        int id = not_fixed[i];

        data[n + (++opt)][ id ] = 1;
        data[n + opt][rez] = cnt & 1;
        cnt >>= 1;
    }


    not_fixed.clear();
    rel = n + opt;
    precompute();

    solve();
    for (i = m; i >= 1; i--)
        if (ans[i] == 0)
            printf("A");
        else
            printf("R");


    return 0;
}
