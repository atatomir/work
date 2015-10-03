#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxVal 250011
#define maxN 100011

int L;
int dim;

struct Drept {
    int cost, x1, y1, x2, y2;

    void read() {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &cost);
        x1 = max(1, x1 - L + 1);
        y1 = max(1, y1 - L + 1);

        x2 = min(dim, x2);
        y2 = min(dim, y2);
    }
    bool operator<(const Drept& who)const {
        return cost > who.cost;
    }
};

int n, i;
Drept Use[maxN];
vector<int> norm_x, norm_y;
int id_line[maxVal];
int id_column[maxVal];

unordered_map<long long, bool> Tree;
Drept act;

void Update(long long node, int l1, int l2, int c1, int c2) {
    if (Tree[node]) return;
    if (act.x1 <= l1 && l2 <= act.x2 &&
        act.y1 <= c1 && c2 <= act.y2){

        Tree[node] = true;
        return;
    }

    int mid_l = (l1 + l2) >> 1;
    int mid_c = (c1 + c2) >> 1;

    if (act.x1 <= mid_l && act.y1 <= mid_c)
        Update(node * 4, l1, mid_l, c1, mid_c);
    if (act.x1 <= mid_l && act.y2 > mid_c)
        Update(node * 4 + 1, l1, mid_l, mid_c + 1, c2);
    if (act.x2 > mid_l && act.y1 <= mid_c)
        Update(node * 4 + 2, mid_l + 1, l2, l1, mid_c);
    if (act.x2 > mid_l && act.y2 > mid_c)
        Update(node * 4 + 3, mid_l + 1, l2, mid_c + 1, c2);

    Tree[node] = Tree[node * 4] & Tree[node * 4 + 1] & Tree[node * 4 + 2] & Tree[node * 4 + 3];
}

int main()
{
    freopen("mm.in","r",stdin);
    freopen("mm.out","w",stdout);

    scanf("%d %d %d", &dim, &L, &n);
    dim -= L - 1;

    for (i = 1; i <= n; i++) {
        Use[i].read();

        norm_x.pb(Use[i].x1);
        norm_x.pb(Use[i].x2);

        norm_y.pb(Use[i].y1);
        norm_y.pb(Use[i].y2);
    }

    sort(norm_x.begin(), norm_x.end());
    norm_x.resize( unique(norm_x.begin(), norm_x.end()) - norm_x.begin() );
    for (i = 0; i < norm_x.size(); i++)
        id_line[ norm_x[i] ] = i + 1;
    //norm_x.clear();

    sort(norm_y.begin(), norm_y.end());
    norm_y.resize( unique(norm_y.begin(), norm_y.end()) - norm_y.begin() );
    for (i = 0; i < norm_y.size(); i++)
        id_column[ norm_y[i] ] = i + 1;
    //norm_y.clear();

    sort(Use + 1, Use + n + 1);

    Tree[1] = false;
    for (i = 1; i <= n; i++) {
        act = Use[i];

        act.x1 = id_line[act.x1];
        act.x2 = id_line[act.x2];

        act.y1 = id_column[act.y1];
        act.y2 = id_column[act.y2];

        Update(1, 1, norm_x.size(), 1, norm_y.size());
        if (Tree[1] == true) {
            printf("%d", act.cost);
            return 0;
        }
    }

    printf("0");

    return 0;
}
