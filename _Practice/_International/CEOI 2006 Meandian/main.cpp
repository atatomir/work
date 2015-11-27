#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include "libmean.h"

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111

struct Query {
    int A, B, C, D;
    int ans;

    Query(int _A, int _B, int _C, int _D) {
        A = _A; B = _B; C = _C; D = _D;
        ans = Meandian(A, B, C, D) * 2;
    }
};

int n, i;
int v[maxN];
queue<int> Q;
int aux[5];
vector<Query> now;

bool my_cmp(const Query& a, const Query& b) {
    return a.ans < b.ans;
}

int main()
{
    n = init();

    for (i = 1; i <= n; i++)
        v[i] = -1;

    while (!Q.empty()) Q.pop();
    for (i = 1; i <= n; i++) Q.push(i);

    while (Q.size() > 4) {
        aux[0] = Q.front(); Q.pop();
        aux[1] = Q.front(); Q.pop();
        aux[2] = Q.front(); Q.pop();
        aux[3] = Q.front(); Q.pop();
        aux[4] = Q.front(); Q.pop();

        now.clear();
        now.pb(Query(aux[0], aux[1], aux[2], aux[3]));
        now.pb(Query(aux[0], aux[1], aux[2], aux[4]));
        now.pb(Query(aux[0], aux[1], aux[3], aux[4]));
        now.pb(Query(aux[0], aux[2], aux[3], aux[4]));
        now.pb(Query(aux[1], aux[2], aux[3], aux[4]));

        sort(now.begin(), now.end(), my_cmp);

        int a = now[0].ans;
        int b = now[2].ans;
        int c = now[4].ans;

        int sum = (a + b + c) / 2;

        int mid_val = sum - b;
        int mid_id;

        for (i = 0; i < 5; i++) {
            if (now[2].A == aux[i]) continue;
            if (now[2].B == aux[i]) continue;
            if (now[2].C == aux[i]) continue;
            if (now[2].D == aux[i]) continue;

            mid_id = aux[i];
            break;
        }

        v[mid_id] = mid_val;
        for (i = 0; i < 5; i++) {
            if (aux[i] != mid_id) {
                Q.push(aux[i]);
            }
        }
    }

    Solution(v);

    return 0;
}
