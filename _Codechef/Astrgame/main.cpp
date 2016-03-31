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

#define maxN 33

int t, ti;

int n, i, j, dim;
char s[maxN];
char aux[maxN];
vector< pair<int, int> > dels;

int pr[maxN];
int u;

int dp[maxN][maxN];


void get_dels() {
    int i;
    int aux_dim = strlen(aux + 1);

    memset(pr, 0, sizeof(pr));
    u = 0;

    for (i = 2; i <= aux_dim; i++) {
        while ( u && aux[u + 1] != aux[i] ) u = pr[u];
        if (aux[u + 1] == aux[i]) u++;
        pr[i] = u;
    }

    u = 0;
    for (i = 1; i <= dim; i++) {
        while (u && s[i] != aux[u + 1]) u = pr[u];
        if (aux[u + 1] == s[i]) u++;

        if (u == aux_dim) {
            dels.pb(mp(i - aux_dim + 1, i));
            u = pr[u];
        }
    }
}

int compute(int l, int r) {
    vector<int> sg;
    sg.clear();

    if (dp[l][r] == -1) {
        //! compute for [l, r]
        dp[l][r] = 0;

        for (auto op : dels) {
            if (op.first < l || op.second > r) continue;

            int res = compute(l, op.first - 1) ^ compute(op.second + 1, r);
            sg.pb(res);
        }

        sort(sg.begin(), sg.end());
        sg.resize(unique(sg.begin(), sg.end()) - sg.begin());

        sg.pb(-1);
        for (int i = 0; i < sg.size(); i++)
            if (sg[i] != i)
                {dp[l][r] = i; return dp[l][r];}
    }


    return dp[l][r];
}

int main()
{
    //freopen("astrgame.in","r",stdin);

    scanf("%d\n", &t);
    for (ti = 1; ti <= t; ti++) {
        memset(s, 0, sizeof(s));
        dels.clear();

        scanf("%s\n%d\n", s + 1, &n);
        dim = strlen(s + 1);

        for (i = 1; i <= n; i++) {
            memset(aux, 0, sizeof(aux));
            scanf("%s\n", aux + 1);
            get_dels();
        }

        sort(dels.begin(), dels.end());
        dels.resize(unique(dels.begin(), dels.end()) - dels.begin());

        for (i = 1; i <= dim; i++)
            for (j = 1; j <= dim; j++)
                dp[i][j] = -1;

        if (compute(1, dim))
            printf("Teddy\n");
        else
            printf("Tracy\n");
    }


    return 0;
}
