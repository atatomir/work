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

#define maxN 455
#define maxM 501111
#define inf 1000000

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);
            reFill();
        }

        Buffer& operator>>(int &dest) {
            while (!isDigit(data[pos])) {
                if (++pos == dim) reFill();
            }
            dest = 0;
            while(isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};

Buffer fin("ajutor.in", 1 << 20);

struct Point {
    int x, y;
    int query;

    bool operator<(const Point& who)const {
        return x < who.x;
    }
    void read(int _q) {
        fin >> x >> y;
        query = _q;
    }
};

int n, m, i;
Point p[maxM];
set< pair<int, int> > work;
int ans[maxM];

int abss(int x) {
    if (x > 0) return x;
    return -x;
}

int dist(pair<int, int> a, pair<int, int> b) {
    return abss(a.first - b.first) + abss(a.second - b.second);
}

bool better(const pair<int, int>& a, const pair<int, int>& b) {
    return abss(a.first - b.first) <= abss(a.second - b.second);

    //! dist pe y e mai mica ca cea pe x
    //! atentie ca perechea e (y, x)
}


void semi_solve() {
    int i;

    work.clear();
    work.insert(mp(-inf, 0));
    work.insert(mp(+inf, 0));
    for (i = 1; i <= n; i++) {
        if (p[i].query == 0) { //! update
            auto right = work.upper_bound( mp(p[i].y, p[i].x) );
            auto left = right; left--;

            auto now = mp(p[i].y, p[i].x) ;

            while (better(now, *left)) left--;
            while (better(now, *right)) right++;

            left++;
            work.erase(left, right);

            work.insert(now);
        } else { //! query
            auto act = work.lower_bound( mp(p[i].y, p[i].x) );
            auto ant = act; ant--;

            int aux = min(dist(mp(p[i].x, p[i].y), mp(act->second, act->first)),
                          dist(mp(p[i].x, p[i].y), mp(ant->second, ant->first)) );
            ans[p[i].query] = min(ans[p[i].query], aux);
        }
    }

}


int main()
{
    //Buffer fin("ajutor.in", 1 << 20);
    freopen("ajutor.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++) p[i].read(0);
    for (i = 1; i <= m; i++) p[n + i].read(i);

    n += m;
    sort(p + 1, p + n + 1);
    for (i = 1; i <= m; i++) ans[i] = inf;

    semi_solve();
    reverse(p + 1, p + n + 1);
    semi_solve();

    for (i = 1; i <= m; i++) printf("%d\n", ans[i]);

    return 0;
}
