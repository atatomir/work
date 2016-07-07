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
#define ll long long

#define eps 1e-2
#define hash_table 100017

#define maxN 1577

const double Knuth = 0.6180339887;
const double tx1 = 113.321197;
const double tx2 = 179.311273;
const double PI = acos(-1);

bool is_equal(double a, double b) {
    return -eps < a - b && a - b < eps;
}

struct Point {
    double x, y;
};

struct Line {
    double a, b, c;

    void with(Point A, Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    void perp() {
        swap(a, b);
        if (is_equal(a, 0.00))
            b = -b;
        else
            a = -a;
    }

    void through(Point A) {
        c = -(a * A.x + b * A.y);
    }

    void redu() {
        if (is_equal(a, 0.00)) a = 0.00;
        if (is_equal(b, 0.00)) b = 0.00;

        if (is_equal(a, 0.00)) {
            c /= b;
            b = 1.00;
        } else {
            c /= a;
            b /= a;
            a = 1.00;
        }
    }

    bool operator==(const Line& who) {
        static double yy1, yy2;

        if (is_equal(b, 0.00)) {
            if (is_equal(who.b, 0.00) == false)
                return false;
            return is_equal(c, who.c);
        }

        yy1 = -(a * tx1 + c) / b;
        yy2 = -(who.a * tx1 + who.c) / who.b;
        if (!is_equal(yy1, yy2)) return false;

        yy1 = -(a * tx2 + c) / b;
        yy2 = -(who.a * tx2 + who.c) / who.b;
        return is_equal(yy1, yy2);
    }

    //! useless
    /*int get_hash(double x) {
        static double aux;
        aux = (Knuth * x);
        aux = (aux - floor(aux)) * hash_table;
        return floor(aux);
    }*/

    int hash_id() {
        static double yy1, yy2;

        if (!is_equal(b, 0.00)) {
            yy1 = -(a * tx1 + c) / b;
            yy2 = -(a * tx2 + c) / b;
        } else{
            yy1 = a;
            yy2 = c;
        }

        if (yy1 < 0) yy1 *= -1;
        if (yy2 < 0) yy2 *= -1;

        return (int)(floor(yy1 * Knuth + yy2)) % hash_table;
    }
};


int n, i, j;
Point P[maxN];
Point G;
Line aux;

int cnt;
vector< pair<Line, int> > Hash[hash_table];
vector<Line> assoc;

vector<int> medi, same;
unordered_map<int, int> how_many;

vector<Line> ans;



int get_id(Line aux) {
    int i, hsh;

    aux.redu();
    hsh = aux.hash_id();

    for (auto e : Hash[hsh])
        if (e.first == aux)
            return e.second;

    cnt++;
    Hash[hsh].pb(mp(aux, cnt));
    assoc.pb(aux);
    return cnt;
}



int main()
{
    freopen("dmg.in","r",stdin);
    freopen("dmg.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
        G.x += P[i].x;
        G.y += P[i].y;
    }

    G.x /= n;
    G.y /= n;
    cnt = -1;

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            aux.with(P[i], P[j]);
            if (is_equal(0.00, aux.a * G.x + aux.b * G.y + aux.c))
                same.pb( get_id(aux) );

            aux.perp();
            aux.through({ (P[i].x + P[j].x) / 2, (P[i].y + P[j].y) / 2 });
            if (is_equal(0.00, aux.a * G.x + aux.b * G.y + aux.c))
                medi.pb( get_id(aux) );
        }
    }

    sort(same.begin(), same.end());
    sort(medi.begin(), medi.end());

    if (same.size() == ((n - 1) * n) / 2)
        if (same[0] == same.back())
            ans.pb(assoc[0]);


    how_many.clear();
    for (auto e : same)
        how_many[e]++;


    for (i = 0; i < medi.size(); i = j) {
        for (j = i; j < medi.size(); j++)
            if (medi[i] != medi[j])
                break;

        int need = n - 2 * (j - i);
        need = ((need - 1) * need) / 2;

        if (how_many[medi[i]] >= need)
            ans.pb(assoc[medi[i]]);
    }


    cerr << ans.size();

    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%.8lf %.8lf %.8lf\n", e.a, e.b, e.c);

    return 0;
}
