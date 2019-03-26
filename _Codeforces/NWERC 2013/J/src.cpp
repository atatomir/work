#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<int> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 10011;
const int inf = 1 << 25;

int n, m, i, j;
vector<int> list[maxN];
char s[maxN];
stack<int> S;
bool ball[maxN];
int total;

vector<int> dp[maxN];

void gen_tree() {
    int i, j;

    n = 0;
    while (!S.empty()) S.pop();
    S.push(0);
    list[0].clear();
    total = 0;

    for (i = 1; i <= m; i++) {
        if (s[i] == '(') {
            list[S.top()].pb(n + 1);
            S.push(++n);
            list[n].clear();
            ball[n] = false;
            continue;
        }
        if (s[i] == ')') {
            S.pop();
            continue;
        }
        ball[S.top()] = true;
        total++;
    }
}

void upd(int& a, int b) {
    if (a < b) a = b;
}

void dfs(int node) {
    dp[node].clear();

    if (list[node].empty()) {
        if (ball[node]) {
            dp[node] = {0, 1};    
        } else {
            dp[node] = {0, 0};
        }
        return;
    }

    int a = list[node][0];
    int b = list[node][1];
    dfs(a);
    dfs(b);

    if (list[a].size() > list[b].size()) swap(a, b);
    dp[a].pb(-inf);
    dp[b].pb(-inf);

    dp[node] = vector<int>(dp[a].size() * 2, -inf);
    for (int i = 0; i + 1 < dp[a].size(); i++) {
        upd(dp[node][i + i], dp[a][i] + dp[b][i]);
        upd(dp[node][i + i + 1], dp[a][i] + dp[b][i + 1]);
        upd(dp[node][i + i + 1], dp[a][i + 1] + dp[b][i]);
    }

    while (dp[node].size() > 3) {
        if (dp[node].back() != -inf)
            break;
        dp[node].pop_back();
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    while (true) {
        s[1] = '@';
        scanf("%s\n", s + 1);
        if (s[1] != '(') break;
        m = strlen(s + 1);

        gen_tree();
        dfs(1);

        /*debug(dp[1]);
        debug(dp[2]);
        debug(dp[3]);
        debug(dp[4]);
        debug(dp[5]);
        debug(dp[6]);
        */

        while (total >= dp[1].size())
            dp[1].pb(-inf);

        if (dp[1][total] < 0)
            printf("impossible\n");
        else
            printf("%d\n", total - dp[1][total]);

        memset(s, 0, m + 3);
    }


    return 0;
}
