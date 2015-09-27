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

#define maxN 50011

struct Node {
    int key, aux;
    int id;

    void read(int _id) {
        scanf("%d%d", &key, &aux);
        id = _id;
    }

    bool operator<(const Node& who)const {
        return key < who.key;
    }
};

int n, i, top;
Node v[maxN];
int lSon[maxN], rSon[maxN];
int dad[maxN];
stack<int> S;

void dfs(int node) {
    if (lSon[node]) {
        dad[ lSon[node] ] = node;
        dfs(lSon[node]);
    }
    if (rSon[node]) {
        dad[ rSon[node] ] = node;
        dfs(rSon[node]);
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) v[i].read(i);
    sort(v + 1, v + n + 1);

    top = 1;
    S.push(1);

    for (i = 2; i <= n; i++) {
        if (v[i].aux < v[top].aux) {
            lSon[ v[i].id ] = v[top].id;
            top = i;

            while (!S.empty()) S.pop();
            S.push(i);
        } else {
            while (!S.empty()) {
                int now = S.top();
                if (v[now].aux < v[i].aux) break;

                rSon[ v[now].id ] = lSon[ v[i].id ];
                lSon[ v[i].id ] = v[now].id;

                S.pop();
            }

            int now = S.top();
            rSon[ v[now].id ] = v[i].id;
            S.push(i);
        }
    }

    dfs(v[top].id);
    printf("YES\n");
    for (i = 1; i <= n; i++)
        printf("%d %d %d\n", dad[i], lSon[i], rSon[i]);


    return 0;
}
