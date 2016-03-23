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
#define ll long long

#define maxN 30
#define inf 1e18
#define maxPoints 555
#define pii pair<double, int>
#define eps 1e-7


struct Point {
    double x, y;

    Point() {}
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }

    void read() {
        scanf("%lf%lf", &x, &y);
    }

    Point operator-(Point who) {
        Point ans = *this;
        ans.x -= who.x;
        ans.y -= who.y;
        return ans;
    }

    bool operator<(const Point& who) const {
        if (x == who.x) return y < who.y;
        return x < who.x;
    }

    void operator+=(Point who) {
        x += who.x;
        y += who.y;
    }

    double dist(Point A) {
        return sqrt( (x - A.x) * (x - A.x) + (y - A.y) * (y - A.y) );
    }
};

typedef vector<Point> Poly;

double cross(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

struct Segment {
    Point A, B;

    Segment() {}

    Segment(Point _A, Point _B) {
        A = _A; B = _B;
    }

    bool intersects(Segment& who) {
        double v1 = cross(who.A - A, B - A) * cross(who.B - A, B - A);
        double v2 = cross(A - who.A, who.B - who.A) * cross(B - who.A, who.B - who.A);

        return (v1 < 0.00 && v2 < 0.00);
    }
};

struct cmp_heap {
    bool operator()(const pii& A, const pii& B) {
        return A > B;
    }
};




int n, i;
Point O, D;
Poly Origin;
Poly Obs[maxN];
vector<Segment> segms;
vector<Point> Points;

vector<int> list[maxPoints];
double dist[maxPoints][maxPoints];

double dijk[maxPoints];
priority_queue< pii, vector<pii>, cmp_heap > H;
bool deny[maxPoints];



Poly Hull(Poly work) {
    vector<Point> ans; ans.clear();
    int i, limit;

    sort(work.begin(), work.end());

    //! upper
    ans.pb(work[0]);
    ans.pb(work[1]);

    for (i = 2; i < (int)work.size(); i++) {
        while (ans.size() >= 2) {
            Point p1 = ans[ans.size() - 2];
            Point p2 = ans[ans.size() - 1];

            if (cross(p2 - p1, work[i] - p1) < 0.00) break;
            ans.pop_back();
        }
        ans.pb(work[i]);
    }


    limit = ans.size();
    for (i = work.size() - 2; i > 0; i--) {
        while((int)ans.size() > limit) {
            Point p1 = ans[ans.size() - 2];
            Point p2 = ans[ans.size() - 1];

            if (cross(p2 - p1, work[i] - p1) < 0.00) break;
            ans.pop_back();
        }
        ans.pb(work[i]);
    }

    ans.pop_back();

    return ans;
}

Poly read_poly() {
    int n, i;
    vector<Point> ans;

    scanf("%d", &n);
    ans.resize(n);

    for (i = 0; i < n; i++) ans[i].read();

    return ans;
}

Poly getObstacle(Point O, Poly Origin, Poly act) {
    Poly ans;
    ans.clear();

    for (Point p_orig : Origin)
        for (Point p_obs : act)
            ans.pb(Point( O.x + p_obs.x - p_orig.x, O.y + p_obs.y - p_orig.y ));

    return Hull(ans);
}

void add_segments_and_points(Poly act) {
    for (int i = 0; i < (int)act.size() - 1; i++) {
        //segms.pb(Segment( act[i], act[i + 1] ));

        //! add every edge in the graph
        list[Points.size() + i].pb(Points.size() + i + 1);
        list[Points.size() + i + 1].pb(Points.size() + i);
    }

    //! add the last edge in the graph
    list[Points.size()].pb(Points.size() + act.size() - 1);
    list[Points.size() + act.size() - 1].pb(Points.size());

    segms.pb(Segment(act[0], act[ act.size() - 1 ]));

    for (Point P : act)
        Points.pb(P);


    act.pb(act[0]);
    act.pb(act[1]);

    for (int i = 0; i + 2 < act.size(); i++)
        segms.pb( Segment(act[i], act[i + 2]) );
}

bool point_in_poly(Point A, Poly act) {
    //! inverse trigo

    act.pb(act[0]);
    for (int i = 0; i + 1 < act.size(); i++)
        if (cross(act[i + 1] - act[i], A - act[i]) >= 0.00)
            return false;

    return true;
}

void makeGraph() {
    int i, j;

    for (i = 0; i < (int)Points.size(); i++) {
        for (j = 0; j < (int)Points.size(); j++) {
            if (i == j) continue;

            dist[i][j] = Points[i].dist(Points[j]);

            Segment aux(Points[i], Points[j]);
            bool good = true;

            for (Segment S : segms) {
                if (aux.intersects(S)) {
                    good = false;
                    break;
                }
            }

            if (good)
                list[i].pb(j);
        }
    }


    //! deny points
    for (i = 0; i < Points.size(); i++) {
        for (int j = 1; j <= n; j++)
            if(point_in_poly(Points[i], Obs[j]))
                deny[i] = true;
    }
}

void solve() {
    int i;

    for (i = 0; i < (int)Points.size(); i++) dijk[i] = inf;
    dijk[0] = 0.00;
    H.push(mp(0.00, 0));


    while (!H.empty()) {
        pii act = H.top(); H.pop();

        if (act.first > dijk[act.second]) continue;

        for (int to : list[act.second]) {
            double act_dist = dijk[act.second] + dist[act.second][to];

            if (dijk[to] > act_dist && deny[to] == false) {
                dijk[to] = act_dist;
                H.push(mp(act_dist, to));
            }
        }
    }
}





int main()
{
    freopen("robot.in","r",stdin);
    freopen("robot.out","w",stdout);

    Origin = read_poly();

    O.x = O.y = inf;
    for (Point P : Origin) {
        O.x = min(O.x, P.x);
        O.y = min(O.y, P.y);
    }

    Points.pb(O);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        Obs[i] = read_poly();
        Obs[i] = getObstacle(O, Origin, Obs[i]);

        //! add segments, points ans poly edges
        add_segments_and_points(Obs[i]);
    }

    D.read();
    Points.pb(D);

    makeGraph();
    solve();

    int id_dest = Points.size() - 1;

    if (dijk[id_dest] >= inf) {
        printf("-1");
        return 0;
    }

    printf("%.2lf", dijk[id_dest]);
    cerr << dijk[id_dest];


    return 0;
}
