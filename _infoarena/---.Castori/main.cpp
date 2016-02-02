#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 25011
#define pii pair<int, int>
#define eps 1e-9
#define lSon (node << 1)
#define rSon (lSon | 1)

class aint {
    public:
        int n;

        void init(int _n, int *_cnt, int *_data) {
            n = _n;
            cnt = _cnt;
            data = _data;
        }

        void update(int node, int l, int r, int qL, int qR, int val) {
            if (qL <= l && r <= qR) {
                cnt[node] += val;
                data[node] += val;
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, val);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR, val);

            data[node] = max(data[lSon], data[rSon]) + cnt[node];
        }

        int get_head() {
            return data[1];
        }

    private:
        int *cnt;
        int *data;
};

struct Square {
    double x1, y1, x2, y2;

    void get_from(pii aux, double d) {
        double a, b;

        a = aux.first;
        b = aux.second + d + eps;

        x1 = a - b;
        y1 = a + b;

        a = aux.first;
        b = aux.second - d - eps;

        x2 = a - b;
        y2 = a + b;

        swap(y1, y2);

        /*
        cerr << "New square :\n";
        cerr << setprecision(2) << x1 << ' ' << y1 << '\n';
        cerr << x2 << ' ' << y2 << '\n';
        cerr << "-------------\n";
        */
    }
};

int n, k, i;
pii Point[maxN];
Square S[maxN];

vector< pair<double, int> > nor;
vector< pair<double, int> > Event;

aint work;
int aint_data[maxN << 2];
int aint_cnt[maxN << 2];

void modif(int who, int pos) {
    if (who < 0)
        S[-who].y1 = pos;
    else
        S[+who].y2 = pos;
}

bool is_good(double d) {
    nor.clear();

    for (i = 1; i <= n; i++) {
        S[i].get_from(Point[i], d / 2.00);

        nor.pb(mp(S[i].y1, -i));
        nor.pb(mp(S[i].y2, +i));
    }

    sort(nor.begin(), nor.end());

    int last = 0;
    modif(nor[0].second, 1);
    for (i = 1; i < nor.size(); i++) {
        if (nor[i].first - nor[last].first > eps)
            last = i;
        modif(nor[i].second, last + 1);
    }

    //! ----- add events ---------------
    Event.clear();
    for (i = 1; i <= n; i++) {
        Event.pb(mp(S[i].x1, -i)); //! add
        Event.pb(mp(S[i].x2, +i)); //! remove
    }

    sort(Event.begin(), Event.end());

    memset(aint_cnt, 0, sizeof(aint_cnt));
    memset(aint_data, 0, sizeof(aint_data));
    work.init(nor.size() + 10, aint_cnt, aint_data);

    for (auto e : Event) {
        int id = e.second;

        if (id < 0) { //! add
            id = -id;

            work.update(1, 1, work.n, S[id].y1, S[id].y2 - 1, +1);
        } else { //! remove
            work.update(1, 1, work.n, S[id].y1, S[id].y2 - 1, -1);
        }

        if (work.get_head() >= k) return true;
    }

    return false;
}

int main()
{
    freopen("castori.in","r",stdin);
    freopen("castori.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)
        scanf("%d%d", &Point[i].first, &Point[i].second);

    int ans = -1;
    for (int step = 1 << 30; step > 0; step >>= 1)
        if (!is_good(ans + step))
            ans += step;

    printf("%d", ans + 1);

    return 0;
}
