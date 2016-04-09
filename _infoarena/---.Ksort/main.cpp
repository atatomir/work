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

#define maxN 100011

int n, k, i, j, kk;
int go[maxN];
vector< pair<int, int> > norm;
bool us[maxN];

vector<int> aux;
vector< vector<int> > cicl;
vector<int> good;

vector< pair<int, int> > sol;



void dfs(int node) {
    us[node] = true;
    aux.pb(node);

    if (us[go[node]] == false)
        dfs(go[node]);
}

bool cmp(const vector<int>& a, const vector<int>& b) {
    return a.size() < b.size();
}

void print_sol() {
    for (i = 1; i <= n; i++)
        if (go[i] == i) kk--;

    if (kk != 0) {
        printf("-1");
        return;
    }



    printf("%d\n", sol.size());
    for (auto e : sol) {
        if (e.first > e.second) swap(e.first, e.second);
        printf("%d %d\n", e.first, e.second);
    }

    if (n <= 100)
        for (i = 1; i <= n; i++) cerr << go[i] << ' ';
}

void move(int a, int b) {
    sol.pb(mp(a, b));
    swap(go[a], go[b]);
}

void add_last() {
    int i;
    aux = cicl.back();

    if (k + 1 < aux.size()) {
        //! swap just a part of it
        for (i = k; i >= 1; i--) move(aux[i - 1], aux[i]);
    } else {
        if (k == 1) {
            move(aux[0], aux[1]);
            move(aux[0], cicl[ cicl.size() - 2 ][0]);
            return;
        }

        for (i = k - 1; i >= 1; i--) move(aux[i - 1], aux[i]);

        cicl.pop_back();
        aux = cicl.back();
        move(aux[0], aux[1]);
    }
}



int main()
{
    freopen("ksort.in","r",stdin);
    freopen("ksort.out","w",stdout);

    scanf("%d%d", &n, &k); kk = k;
    for (i = 1; i <= n; i++) {
        scanf("%d", &go[i]);
        norm.pb(mp(go[i], i));
    }

    if (k == n - 1) {
        printf("-1");
        return 0;
    }

    sort(norm.begin(), norm.end());
    for (i = 0; i < norm.size(); i++) go[norm[i].second] = i + 1;

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        if (go[i] == i) {
            good.pb(i);
            continue;
        }

        aux.clear();
        dfs(i);
        cicl.pb(aux);
    }

    sort(cicl.begin(), cicl.end(), cmp);

    if (k == good.size()) {
        printf("0");
        return 0;
    }

    if (k < good.size()) {
        good.resize(good.size() - k);
        while (good.size() > 3 || good.size() % 2 == 0) {
            int n1 = good.back(); good.pop_back();
            int n2 = good.back(); good.pop_back();
            move(n1, n2);

            if (good.empty()) break;
        }

        if (good.size() == 1) move(good.back(), cicl[0][0]), good.pop_back();

        if (good.size() == 3) {
            int n1 = good.back(); good.pop_back();
            int n2 = good.back(); good.pop_back();
            int n3 = good.back(); good.pop_back();

            move(n1, n2);
            move(n2, n3);
        }

        print_sol();
        return 0;
    }

    //! k < good.size()
    k -= good.size();

    for (i = 0; i < cicl.size(), cicl[i].size() <= k; i++) {
        k -= cicl[i].size();
        for (j = cicl[i].size() - 1; j >= 1; j--) move(cicl[i][j - 1], cicl[i][j]);
    }

    if (k) add_last();

    print_sol();

    return 0;
}
