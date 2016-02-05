#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 255011
#define eps 1e-13
#define pii pair<double, int>

struct Point {
    double x, y;

    void read() {
        scanf("%lf %lf", &x, &y);
    }

    Point diff(Point &who) {
        Point ans;
        ans.x = x - who.x;
        ans.y = y - who.y;

        return ans;
    }

    double cross(Point who) {
        return x * who.y - y * who.x;
    }

    Point operator+(Point who) {
        Point ans;

        ans.x = x + who.x;
        ans.y = y + who.y;

        return ans;
    }
};

struct Node {
    Node *from, *to;
    int id;

    Node() {}
    Node(Node *_from, Node *_to, int _id) {
        from = _from;
        to = _to;
        id = _id;
    }
};

int n, m, i;
Point P[maxN];
double ang[maxN];
set< pii > S;
Node *work[maxN];

Point mid;
int act;

bool valid[maxN];

bool good(int id1, int id2, int id3) {
    return P[id3].diff(P[id1]).cross(P[id2].diff(P[id1])) >= 0.00;
}

void add_point(int id) {
    int i;
    Node *now;
    Node *fr, *to;

    /*cerr << id << '\n';
    for (auto it : S)
        cerr << it.second << ' ';
    cerr << '\n'; */

    auto it = S.lower_bound(mp(ang[id], 0));
    if (it == S.end()) it = S.begin();

    fr = work[it->second];
    to = fr->to;

    work[id] = new Node(fr, to, id);
    if (!good(fr->id, id, to->id)) return;

    //! add new node
    act++;
    fr->to = work[id];
    to->from = work[id];
    valid[id] = true;
    S.insert(mp(ang[id], id));

    now = work[id]->to;
    while (true) {
        if (good(now->from->id, now->id, now->to->id)) break;
        now->from->to = now->to;
        now->to->from = now->from;

        auto it = S.lower_bound(mp(ang[now->id] - eps, now->id));
        S.erase(it);

        valid[now->id] = false;
        now = now->to;
        act--;
    }

    now = work[id]->from;
    while (true) {
        if (good(now->from->id, now->id, now->to->id)) break;
        now->from->to = now->to;
        now->to->from = now->from;

        auto it = S.lower_bound(mp(ang[now->id] - eps, now->id));
        S.erase(it);

        valid[now->id] = false;
        S.erase(mp(now->id, ang[now->id]));
        now = now->from;
        act--;
    }
}

int main()
{
    freopen("terenuri.in","r",stdin);
    freopen("terenuri.out","w",stdout);

    scanf("%d%d", &n, &m);
    n += m;
    m = n - m - 1;
    for (i = 1; i <= n; i++)
        P[i].read();

    if (!good(1, 2, 3)) swap(P[2], P[3]);

    mid = P[1] + P[2] + P[3];
    mid.x /= 3.00;
    mid.y /= 3.00;

    for (i = 1; i <= n; i++)
        ang[i] = atan2(P[i].y - mid.y, P[i].x - mid.x);

    //! add first 3 points
    work[1] = new Node(NULL, NULL, 1);
    work[3] = new Node(NULL, NULL, 3);
    work[2] = new Node(work[1], work[3], 2);

    work[1]->from = work[3];
    work[1]->to = work[2];

    work[3]->from = work[2];
    work[3]->to = work[1];

    S.clear();
    S.insert(mp(ang[1], 1));
    S.insert(mp(ang[2], 2));
    S.insert(mp(ang[3], 3));

    if (m < 3) printf("3\n");
    act = 3;

    valid[1] = valid[2] = valid[3] = true;

    for (i = 4; i <= n; i++) {
        add_point(i);
        if (i > m)  printf("%d\n", act);
    }

    return 0;
}
