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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

#define lSon (node << 1)
#define rSon (lSon | 1)
#define rank smecherie

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}


const int maxN = 150011;

struct aint {
    vector<int> data[maxN * 4 + 11];

    void init(int n) {
        for (int i = 0; i <= 4 * n + 3; i++)
            data[i].clear();
    }

    void add(int node, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            data[node].pb(v);
            return;
        }

        int mid = (l + r) >> 1;
        if (ql <= mid) add(lSon, l, mid, ql, qr, v);
        if (qr > mid) add(rSon, mid + 1, r, ql, qr, v);
    }
};

int t, ti;
int n, m, i, x, y;
int a[maxN], b[maxN];
vector<int> whoA[maxN], whoB[maxN], list[maxN];

int dad[maxN], rank[maxN];
vector<int> rev_dad;
vector<pair<int, int> > rev_rank;
bool solution, on[maxN];
aint work;

int stamp_id;
int stamp[maxN];

void erase_data() {
    int i;

    work.init(n);
    for (i = 1; i <= n; i++) {
        whoA[i].clear();
        whoB[i].clear();
        dad[i] = i;
        list[i].clear();
        on[i] = false;
        rank[i] = 0;
    }
    rev_dad.clear();
    rev_rank.clear();
}

int Find(int x) {
    if (dad[x] == x) return x;
    return Find(dad[x]);
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);
    
    if (x == y) return false;
    if (rank[x] > rank[y]) swap(x, y);

    dad[x] = y;
    rev_dad.pb(x);
    rev_rank.pb(mp(y, rank[y]));
    rank[y] = max(rank[y], rank[x] + 1);
    
    return true;
}

void add_node(int id) {
    on[id] = true;
    for (auto e : list[id])
        if (on[e])
            Merge(e, id);

    //cerr << "added " << id << '\n'; 
}

void run(int node, int l, int r) {
    vector<int>& to_do = work.data[node];
    int limit = rev_dad.size();

    for (auto e : to_do) add_node(e);

    if (l == r) {
        stamp_id++;
        for (auto e : whoA[l]) 
            stamp[Find(e)] = stamp_id;
        for (auto e : whoB[l])
            if (stamp[Find(e)] != stamp_id)
                solution = false;
    
    /*
    debug(l);
    for (i = 1; i <= n; i++) cerr << dad[i] << ' '; cerr << '\n';
    for (i = 1; i <= n; i++) cerr << stamp[i] << ' '; cerr << '\n';
    */
                
    } else {
        int mid = (l + r) >> 1;
        run(lSon, l, mid);
        run(rSon, mid + 1, r);
    }

    for (auto e : to_do) {
        on[e] = false; 
        //cerr << "rm " << e << '\n';
    }
    
    while (rev_dad.size() > limit) {
        int id = rev_dad.back(); rev_dad.pop_back();
        pair<int, int> rnk = rev_rank.back(); rev_rank.pop_back();
        dad[id] = id;
        rank[rnk.first] = rnk.second;
    }
}

int main()
{
    //freopen("test.in","r",stdin);
    freopen("colors2.in", "r", stdin);
    freopen("colors2.out", "w", stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);
        erase_data();
        solution = true;

        for (i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            whoA[a[i]].pb(i);
        }
        for (i = 1; i <= n; i++) {
            scanf("%d", &b[i]);
            whoB[b[i]].pb(i);
            if (a[i] < b[i]) solution = false;
            else             work.add(1, 1, n, b[i], a[i], i);
        }

        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(y);
            list[y].pb(x);
        }


        if (!solution) {
            printf("0\n");
            continue;
        }

        run(1, 1, n);

        if (solution)
            printf("1\n");
        else
            printf("0\n");

    }   




    return 0;
}
