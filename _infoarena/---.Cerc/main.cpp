#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 211
#define alfa 0.000000012
#define eps 1e-7
#define noIntersection mp( mp(0.00,0.00) , mp(0.00,0.00) )

const double alfa_cos = cos(alfa);
const double alfa_sin = sin(alfa);

bool isEqual(double a,double b) {
    a = (a > b?a-b:b-a);
    return a <= eps;
}

struct Circle {
    double x,y,R;

    void read() {
        scanf("%lf%lf%lf",&x,&y,&R);

        //! Rotate
        double _x=x,_y=y;
        x = alfa_cos * _x - alfa_sin * _y;
        y = alfa_sin * _x + alfa_cos * _y;
    };

    bool operator<(const Circle& who)const {
        if ( !isEqual(x,who.x) ) return x < who.x;
        if ( !isEqual(y,who.y) ) return y < who.y;
        return R < who.R;
    }
    bool operator==(const Circle& who)const {
        if ( !isEqual(x,who.x) ) return false;
        if ( !isEqual(y,who.y) ) return false;
        return isEqual(R,who.R);
    }

    pair< pair<double,double> , pair<double,double> > getIntersection(const Circle& who) {
        if (isEqual(x,who.x) && isEqual(y,who.y))
            return noIntersection; //! vezi macro

        double xx = who.x - x;
        double yy = who.y - y;

        double C = R * R + xx * xx + yy * yy - who.R * who.R; //! my constant
        double a = 4.00 * yy * yy + 4.00 * xx * xx;
        double b = -4.00 * C * yy;
        double c = C * C - R * R * 4.00 * xx * xx;

        double delta = b * b - 4.00 * a * c ;

        //double aux = sqrt( (x-who.x)*(x-who.x) + (y-who.y)*(y-who.y) );
        //if (isEqual(aux,R+who.R)) delta = 0.00;

        if (delta < 0.00) return noIntersection;
        delta = sqrt(delta);

        //! for y1
        double y1 = (-b - delta)/(2 * a);
        double x1 = (C - 2 * y1 * yy)/(2 * xx);



        //! for y2
        double y2 = (-b + delta)/(2 * a);
        double x2 = (C - 2 * y2 * yy)/(2 * xx);

        return mp( mp(x1,y1), mp(x2,y2) );
    }
};

struct Point {
    double x,y;

    Point() {}
    Point(double _x,double _y) {
        x = _x; y = _y;
    }

    bool operator<(const Point& who)const {
        if (!isEqual(x,who.x)) return x < who.x;
        return y < who.y;
    }
    bool operator==(const Point& who)const {
        if (!isEqual(x,who.x)) return false;
        return isEqual(y,who.y);
    }
};

int n,i,j;
vector<Circle> C;
vector< Point > impPoints[maxN];
vector< Point > allNodes;

vector<int> list[maxN];
bool used[maxN];

int nodes,edges,components;

void dfs(int node) {
    used[node] = true;
    for (auto neigh:list[node]) {
        if (used[neigh]) continue;
        dfs(neigh);
    }
}

int main()
{
    freopen("cerc.in","r",stdin);
    freopen("cerc.out","w",stdout);

    scanf("%d",&n);
    C.resize(n);
    for (i = 0; i < n; i++) C[i].read();

    sort(C.begin(),C.end());
    C.resize( unique(C.begin(),C.end())-C.begin() );
    n = C.size();

    cerr << "There are " << n << " circles . \n";

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            auto ans = C[i].getIntersection(C[j]);
            if (ans.first  == mp(0.00,0.00) &&
                ans.second == mp(0.00,0.00)) continue;

            impPoints[i].pb( Point(ans.first.first, ans.first.second) );
            impPoints[i].pb( Point(ans.second.first, ans.second.second) );

            /**/
            allNodes.pb( Point(ans.first.first + C[i].x, ans.first.second + C[i].y) );
            allNodes.pb( Point(ans.second.first + C[i].x, ans.second.second + C[i].y) );

            /**/ ans = C[j].getIntersection(C[i]);
            impPoints[j].pb( Point(ans.first.first, ans.first.second) );
            impPoints[j].pb( Point(ans.second.first, ans.second.second) );

            list[i].pb(j);
            list[j].pb(i);
        }
    }

    for (i = 0; i < n; i++) {
        sort(impPoints[i].begin(),impPoints[i].end());
        impPoints[i].resize( unique(impPoints[i].begin(),impPoints[i].end())-impPoints[i].begin() );

        edges += impPoints[i].size();
    }

    cerr << "There are " << edges << " edges .\n";

    sort(allNodes.begin(),allNodes.end());
    allNodes.resize( unique(allNodes.begin(),allNodes.end()) - allNodes.begin() );
    nodes = allNodes.size();

    cerr << "There are " << nodes << " nodes .\n";

    for (i = 0; i < n; i++) {
        if (used[i]) continue;

        components++;
        dfs(i);
    }

    cerr << "There are " << components << " components .\n";

    printf("%d", edges - nodes + components );
    cerr << "Finally the answer is ... " << edges - nodes + components << '\n';

    cerr << "\nThank you ! I hope the answer is correct ! \n";

    return 0;
}
