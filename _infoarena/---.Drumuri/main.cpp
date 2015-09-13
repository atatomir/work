#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10011

int n, m, i, x, y;
vector<int> list[maxN];
int dad[maxN];
bool us[maxN];
bool done[maxN];

void removeEdge(int dad, int id) {
    list[dad][id] = list[dad][ list[dad].size() -1 ];
    list[dad].pop_back();
}

bool dfs(int node) {
    //! returns true if the edge dad-son was used , false otherwise
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int newNode = list[node][i];

        if (dad[node] == newNode) {
            removeEdge(node, i);
            i--;
            continue;
        }

        if (done[newNode]) {
            removeEdge(node, i);
            i--;
            continue;
        }
        if (us[newNode]) continue;

        dad[newNode] = node;
        if (dfs(newNode) == true) {
            removeEdge(node, i);
            i--;
            continue;
        }
    }

    while (list[node].size() > 1) {
        int n1 = list[node][ list[node].size() - 1 ];
        list[node].pop_back();
        int n2 = list[node][ list[node].size() - 1 ];
        list[node].pop_back();

        printf("%d %d %d\n", n1, node, n2);
    }

    done[node] = true;

    if (list[node].size() == 0) return false;

    printf("%d %d %d\n", list[node][0], node, dad[node]);

    return true;
}

int main()
{
    freopen("drumuri.in","r",stdin);
    freopen("drumuri.out","w",stdout);

    scanf("%d %d", &n, &m);

    if (m % 2 == 1) {
        printf("0");
        return 0;
    }
    printf("1\n");

    for (i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);

    return 0;
}
