#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 20011

int n, i, x, y;
vector<int> list[maxN];
int M[maxN];

vector<int> aux, aux2;
map< pair<int, int>, bool > exist;

void dfs(int node, int root) {
    aux.pb(node);

    for (auto to : list[node])
        if (to != root)
            dfs(to, node);
}

void sh(vector<int>& aux) {
    vector<int> data = aux;
    aux.clear();

    if (rand() % 10 == 8) {
        aux = data;
        return;
    }

    if (rand() % 10 == 7) {
        aux = data;
        random_shuffle(aux.begin(), aux.end());
        return;
    }

    int ss = rand() % 4;

    if (ss == 0) {
        for (int i = 0; i < data.size(); i += 3) aux.pb(data[i]);
        for (int i = 1; i < data.size(); i += 3) aux.pb(data[i]);
        for (int i = 2; i < data.size(); i += 3) aux.pb(data[i]);
    }

    if (ss == 1) {
        for (int i = 0; i < data.size(); i += 2) aux.pb(data[i]);
        for (int i = 1; i < data.size(); i += 2) aux.pb(data[i]);
    }

    if (ss == 2) {
        for (int i = 0; i < data.size(); i += 7) aux.pb(data[i]);
        for (int i = 1; i < data.size(); i += 7) aux.pb(data[i]);
        for (int i = 2; i < data.size(); i += 7) aux.pb(data[i]);
        for (int i = 3; i < data.size(); i += 7) aux.pb(data[i]);
        for (int i = 4; i < data.size(); i += 7) aux.pb(data[i]);
        for (int i = 5; i < data.size(); i += 7) aux.pb(data[i]);
        for (int i = 6; i < data.size(); i += 7) aux.pb(data[i]);
    }

    if (ss == 3) {
        aux = data;
        random_shuffle(aux.begin(), aux.end());
    }

    if (ss % 2)
        reverse(aux.begin(), aux.end());
}

void check() {
    int i, R1, R2;

    for (i = 1; i <= 2 * n; i++)
        random_shuffle(list[i].begin(), list[i].end());

    R1 = (rand() % n) + 1;
    R2 = (rand() % n) + n + 1;

    aux.clear();
    dfs(R1, 0);
    aux2 = aux;

    aux.clear();
    dfs(R2, 0);

    sh(aux);

    for (i = 0; i < n; i++)
        M[aux[i]] = aux2[i];

    for (i = n + 1; i <= 2 * n; i++) {
        for (auto to : list[i]) {
            if (exist[mp(M[i], M[to])]) return;
        }
    }

    printf("Yes\n");
    for (i = n + 1; i <= 2 * n; i++) M[M[i]] = i;
    for (i = 1; i <= n; i++) printf("%d ", M[i]);
    exit(0);
}

void check2() {
    int i;

    for (i = n + 1; i <= 2 * n; i++) {
        for (auto to : list[i]) {
            if (exist[mp(M[i], M[to])]) return;
        }
    }

    printf("Yes\n");
    for (i = n + 1; i <= 2 * n; i++) M[M[i]] = i;
    for (i = 1; i <= n; i++) printf("%d ", M[i]);
    exit(0);
}

int main()
{
    srand(time(NULL));
    //freopen("test.in","r",stdin);

    auto ini = clock();

    scanf("%d", &n);
    for (i = 1; i <= (n - 1) * 2; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);

        if (x <= n) {
            exist[mp(x, y)] = exist[mp(y, x)] = true;
        }
    }

    if (n <= 10) {
        for (i = n + 1; i <= 2 * n; i++) M[i] = i - n;
        do {
            check2();
        } while (next_permutation(M + n + 1, M + 2 * n + 1));
    } else {
        while (true) {
            if (((1.00 * clock() - 1.00 * ini) / CLOCKS_PER_SEC) > 3.300) break;
            check();
        }
    }

    printf("No");


    return 0;
}
