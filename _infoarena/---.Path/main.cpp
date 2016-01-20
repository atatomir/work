#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 61

int n, m, k, i;
vector<int> list[maxN];
bool valid[maxN];
char c1, c2;

int deep[maxN];
int how[maxN];
int gr[maxN];
queue<int> Q;

vector<int> rev[maxN];
int now_deep, now_node;

int get_id(char c) {
    if ('a' <= c && c <= 'z')
        return c - 'a' + 1;
    else
        return c - 'A' + 26 + 1;
}

char get_char(char c) {
    if (c > 26)
        return 'A' + c - 26 - 1;
    else
        return 'a' + c - 1;
}

int main()
{
    freopen("path.in","r",stdin);
    freopen("path.out","w",stdout);

    scanf("%d%d%d\n", &n, &m, &k);
    n = 52;

    for (i = 1; i <= m; i++) {
        scanf("%c %c\n", &c1, &c2);

        int id1 = get_id(c1);
        int id2 = get_id(c2);

        valid[id1] = valid[id2] = true;
        list[id1].pb(id2);

        gr[id1]++;
        rev[id2].pb(id1);
    }

    for (i = 1; i <= n; i++) {
        if (valid[i] && gr[i] == 0) {
            Q.push(i);
            deep[i] = 1;
            how[i] = 1;
        }
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        for (auto to : rev[node]) {
            if (--gr[to] == 0)  Q.push(to);

            if (deep[to] > deep[node] + 1) continue;
            if (deep[to] == deep[node] + 1) how[to] += how[node];
            if (deep[to] < deep[node] + 1) {
                deep[to] = deep[node] + 1;
                how[to] = how[node];
            }
        }

        now_deep = max(now_deep, deep[node]);
    }

    for (i = 1; i <= n; i++)
        if (valid[i])
            list[0].pb(i);


    now_node = 0;
    for (int max_deep = now_deep; max_deep > 0; max_deep--) {
        for (int i = 0; i < list[now_node].size(); i++) {
            int to = list[now_node][i];

            if (deep[to] != now_deep) {
                list[now_node][i] = list[now_node][ list[now_node].size() - 1 ];
                list[now_node].pop_back();
                i--;
            }
        }

        sort(list[now_node].begin(), list[now_node].end());
        for (auto to : list[now_node]) {
            if (how[to] < k) {
                k -= how[to];
                now_node = to;
            } else {
                now_node = to;
                now_deep--;
                break;
            }
        }

        printf("%c", get_char(now_node));
    }


    return 0;
}
