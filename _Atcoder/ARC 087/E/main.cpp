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

struct node {
    node *son[2];
    bool dead;

    node() {
        son[0] = son[1] = NULL;
        dead = false;
    }
};

ll n, i, L;
string s;
node *Head;
ll SG;

ll get_sg(ll x) {
    ll bit;

    return (x ^ (x - 1)) & x;

    for (bit = 1LL << 60; bit > 0; bit >>= 1) {
        if (x < bit) continue;
        if (x == bit) return x;
        x ^= bit;
    }
}

void compute() {
    int i, j, act;
    int dp[111];
    vector<int> aux;

    dp[0] = 0;
    for (i = 1; i <= 100; i++) {
        aux = {0};
        act = 0;

        for (j = i - 1; j > 0; j--) {
            act ^= dp[j];
            aux.pb(act);
        }

        sort(aux.begin(), aux.end());
        aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
        aux.pb(-1);

        for (j = 0; aux[j] == j; j++);
        dp[i] = j;
        cerr << i << ' ' << dp[i] << ' ' << get_sg(i) << '\n';
    }
}

void add(string& s) {
    int id;
    node* act = Head;

    for (auto c : s) {
        id = c - '0';
        if (act->son[id] == NULL)
            act->son[id] = new node();
        act = act->son[id];
    }

    act->dead = true;
}

void dfs(node* act, ll lvl) {
    if (act->dead) return;

    if (act->son[0] != NULL) {
        dfs(act->son[0], lvl + 1);
    } else {
        SG ^= get_sg(L - lvl);
    }

    if (act->son[1] != NULL) {
        dfs(act->son[1], lvl + 1);
    } else {
        SG ^= get_sg(L - lvl);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    //compute();
    cin >> n >> L;

    Head = new node();
    for (i = 1; i <= n; i++) {
        cin >> s;
        add(s);
    }

    dfs(Head, 0);
    if (SG)
        cout << "Alice";
    else
        cout << "Bob";


    return 0;
}
