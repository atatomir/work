#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111
#define inf (1e60)
#define eps 1e-9

int wh_edge[maxN];
struct Edge {
    int id;
    double value;

    bool operator<(const Edge& who)const {
        if (value >= who.value) swap(wh_edge[id], wh_edge[who.id]);

        return value < who.value;
    }
} Edges[maxN];

struct quadFuction {
    int a,b,c;
    int u,v;
    double value ;

    void read() {
        scanf("%d%d%d%d%d",&u,&v,&a,&b,&c);
        u++; v++;
    }
    void compute(int id, double x) {
        Edges[id].value = a * x * x + b * x + c;
        Edges[id].id = id;
    }

    vector<double> intersect(quadFuction& who) {
        double aa = a - who.a;
        double bb = b - who.b;
        double cc = c - who.c;

        if (aa == 0 && bb == 0) return {};
        if (aa != 0) { //! gr 2
            double delta = bb * bb - 4 * aa * cc;
            if (delta < 0) return {};
            delta = sqrt(delta);

            double x1 = (-bb - delta) / (2.00 * aa);
            double x2 = (-bb + delta) / (2.00 * aa);

            if (delta < 1e-9) return {x1};
            return {x1, x2};
        } else { //! gr 1
            return {-cc/bb};
        }
    }
};

class Forest {
    public:
        void init(int _dim,int *_dad) {
            dim = _dim;
            dad = _dad;
        }

        void reset() {
            for (int i = 1; i <= dim; i++) dad[i] = i;
        }

        bool Merge(int R1,int R2) {
            R1 = Find(R1);
            R2 = Find(R2);

            if(R1 == R2) return false;
            dad[R1] = R2;

            return true;
        }

    private:
        int *dad;
        int dim;

        int Find(int node) {
            if (dad[node] == node) return node;
            dad[node] = Find(dad[node]);
            return dad[node];
        }
};

int n,m,i,j;
quadFuction Func[maxN];
vector< pair<double, pair<int, int> > > events;
vector<int> changed;
double ans,ans_time;
double local;

Forest Work;
int forest_dad[maxN];

double aa = 0.00;
double bb = 0.00;
double cc = 0.00;
double search_t;

double fValue(double x) {
    return aa * x * x + bb * x + cc;
}

double MinSearch(double l, double r) {
    search_t = -bb/(2 * aa);
    if (search_t < l || search_t > r) {
        if (fValue(l) < fValue(r))
            search_t = l;
        else
            search_t = r;
    }

    return fValue(search_t);
}

double depend_time ;
bool depend_y(int a,int b) {
    if (Edges[wh_edge[a]].value >= Edges[wh_edge[b]].value) {
        swap(Edges[wh_edge[a]], Edges[wh_edge[b]]);
        swap(wh_edge[a], wh_edge[b]);

        return false;
    }

    return true;
}

int main()
{
    freopen("mst.in","r",stdin);
    freopen("mst.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i = 1; i <= m; i++) Func[i].read();

    events.clear();
    events.pb(mp(-inf, mp(0, 0))); events.pb(mp(inf, mp(0, 0)));
    for (i = 1; i <= m; i++){
        for (j = i+1; j <= m; j++) {
            vector<double> aux = Func[i].intersect(Func[j]);
            while (!aux.empty()) {
                events.pb( mp(aux[aux.size() - 1], mp(i, j)) );
                aux.pop_back();
            }
        }
    }

    sort(events.begin(), events.end());

    Work.init(n, forest_dad);
    ans_time =  inf;
    ans      =  inf;

    cerr << "Events : " << events.size() << '\n';

    int tt = events[0].first;
    for (i = 1; i <= m; i++) {
        Func[i].compute(i, tt);
        wh_edge[i] = i;
    }
    sort(Edges + 1, Edges + m + 1);

    for (i = 1; i < events.size(); i++) {
        double t1 = events[i-1].first;
        double t2 = events[i].first;
        double tt = (t1 + t2)/ 2.00;

        changed = {events[i].second.first, events[i].second.second};
        while (i + 1 < events.size()) {
            if (events[i+1].first - events[i].first > eps) break;

            i++;
            changed.pb( events[i].second.first );
            changed.pb( events[i].second.second );
        }

        sort(changed.begin(), changed.end());
        changed.resize( unique(changed.begin(), changed.end()) - changed.begin() );

        depend_time = t2 + eps;
        for (auto id : changed) {
            Edges[wh_edge[id]].value =   1.00 * Func[id].a * depend_time * depend_time
                                       + 1.00 * Func[id].b * depend_time
                                       + Func[id].c ;
        }
        //sort(changed.begin(), changed.end(), depend_y);

        //!------------------^ i have made the changes ^-------------------

        aa = 0.00;
        bb = 0.00;
        cc = 0.00;

        Work.reset(); local = 0;
        for (int actEdge = 1; actEdge <= m; actEdge++) {
            Edge now = Edges[actEdge];

            if (Work.Merge(Func[now.id].u, Func[now.id].v)) {
                aa += Func[now.id].a;
                bb += Func[now.id].b;
                cc += Func[now.id].c;
            }
        }

        /*  Now I have the quadFunction which determinate the total cost
         *  for interval [t1,t2]
         */

        local = MinSearch(t1, t2);
        if (ans > local) {
            ans = local;
            ans_time = search_t;
        }

        //! last change...
        sort(changed.begin(), changed.end(), depend_y);
    }

    printf("%.9lf %.9lf",ans_time,ans);

    return 0;
}
