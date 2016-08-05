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

#define maxN 16011

int n, i;
int x, y;
vector<int> list[maxN];

vector<int> *A[maxN], *B[maxN], *C[maxN];
int ans[maxN];



void combine(vector<int>* &a, vector<int>* &b) {
    if (a->size() > b->size()) {
        for (auto e : *b)
            a->pb(e);
    } else {
        for (auto e : *a)
            b->pb(e);
        a = b;
    }
}

void dfs(int node) {
    int s1, s2;
    int sa, sb, sc;

    if (list[node].empty()) {
        A[node] = new vector<int>;
        B[node] = new vector<int>;
        C[node] = new vector<int>;

        A[node]->clear();
        B[node]->clear();
        C[node]->clear();

        A[node]->pb(node);

        return;
    }

    if(list[node].size() == 1) {
        s1 = list[node][0];
        dfs(s1);

        A[node] = A[s1];
        B[node] = B[s1];
        C[node] = C[s1];

        if (B[node]->size() > C[node]->size())
            swap(B[node], C[node]);

        B[node]->pb(node);
        swap(A[node], B[node]);

        return;
    }

    int t1, t2;
    int best = n + 10;
    int max_sa = -1;

    s1 = list[node][0]; dfs(s1);
    s2 = list[node][1]; dfs(s2);

    /* find best */
    for (t1 = 0; t1 < 2; t1++) {
        for (t2 = 0; t2 < 2; t2++) {
            sa = 1;
            sb = A[s1]->size();
            sc = A[s2]->size();

            if (t1 == 0) {
                sa += B[s1]->size();
                sc += C[s1]->size();
            } else {
                sc += B[s1]->size();
                sa += C[s1]->size();
            }

            if (t2 == 0) {
                sa += B[s2]->size();
                sb += C[s2]->size();
            } else {
                sb += B[s2]->size();
                sa += C[s2]->size();
            }

            int aux = max(sa, max(sb, sc)) - min(sa, min(sb, sc));
            if (best > aux) {
                best = aux;
                max_sa = sa;
            }
            if (best == aux)
                max_sa = max(max_sa, sa);
        }
    }

    if (best > 1)
        cerr << "err best\n";

    /* compute best */
    A[node] = new vector<int>;
    A[node]->clear();
    A[node]->pb(node);

    B[node] = A[s1];
    C[node] = A[s2];

    for (t1 = 0; t1 < 2; t1++) {
        for (t2 = 0; t2 < 2; t2++) {
            sa = 1;
            sb = A[s1]->size();
            sc = A[s2]->size();

            if (t1 == 0) {
                sa += B[s1]->size();
                sc += C[s1]->size();
            } else {
                sc += B[s1]->size();
                sa += C[s1]->size();
            }

            if (t2 == 0) {
                sa += B[s2]->size();
                sb += C[s2]->size();
            } else {
                sb += B[s2]->size();
                sa += C[s2]->size();
            }

            if (max(sa, max(sb, sc)) - min(sa, min(sb, sc)) != best || sa != max_sa) continue;

            if (t1 == 0) {
                combine(A[node], B[s1]);
                combine(C[node], C[s1]);
            } else {
                combine(A[node], C[s1]);
                combine(C[node], B[s1]);
            }

            if (t2 == 0) {
                combine(A[node], B[s2]);
                combine(B[node], C[s2]);
            } else {
                combine(A[node], C[s2]);
                combine(B[node], B[s2]);
            }

            if (A[node]->size() != sa) cerr << "err\n";
            if (B[node]->size() != sb) cerr << "err\n";
            if (C[node]->size() != sc) cerr << "err\n";

            return;
        }
    }


}

int main()
{
    freopen("comp.in","r",stdin);
    freopen("comp.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[y].pb(x);
    }

    dfs(1);
    for (int e : *A[1])
        ans[e] = 1;
    for (int e : *B[1])
        ans[e] = 2;
    for (int e : *C[1])
        ans[e] = 3;

    for (i = 1; i <= n; i++)
        printf("%d ", ans[i]);

    int maxi = max(A[1]->size(), max(B[1]->size(), C[1]->size()));
    int mini = min(A[1]->size(), min(B[1]->size(), C[1]->size()));
    cerr << mini << ' ' << maxi << " -> " << maxi - mini << '\n';

    return 0;
}
