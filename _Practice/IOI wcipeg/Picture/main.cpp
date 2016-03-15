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

#define maxN 5011
#define maxVal 20011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define def 20002

class aint {
    public:
        int dim;

        void init(int _dim, int *_data, int *_blocked) {
            dim = _dim;
            data = _data;
            blocked = _blocked;
        }

        void update(int node, int l, int r, int qL, int qR, int v) {
            if (qL <= l && r <= qR) {
                blocked[node] += v;
                update_node(node, l, r);
                return ;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, v);
            if (qR > mid)
                update(rSon, mid + 1, r, qL, qR, v);

            update_node(node, l, r);
        }

        int query() {
            return data[1];
        }

    private:
        int *data;
        int *blocked;

        void update_node(int node, int l, int r) {
            if (blocked[node]) {
                data[node] = r - l + 1;
                return;
            }

            if (l == r)
                data[node] = 0;
            else
                data[node] = data[lSon] + data[rSon];
        }

        void init_tree(int node, int l, int r) {
            blocked[node] = 0;
            update_node(node, l, r);
            if (l == r) return;

            int mid = (l + r) >> 1;
            init_tree(lSon, l, mid);
            init_tree(rSon, mid + 1, r);
        }
};

struct rectangle {
    int x1, x2, y1, y2;

    void read() {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 += 10001;
        y1 += 10001;
        x2 += 10001;
        y2 += 10001;
    }
};

int n, i, j;
rectangle R[maxN];

int aint_data[maxVal << 2];
int aint_blocked[maxVal << 2];
aint work;

int ans;
vector< pair<int, int> > Events;

void process() {
    int i, before;

    work.init(def, aint_data, aint_blocked);
    Events.clear();

    for (i = 1; i <= n; i++) {
        auto now = R[i];

        Events.pb(mp(now.x1, -i));
        Events.pb(mp(now.x2, +i));
    }

    sort(Events.begin(), Events.end());

    for (i = 0; i < Events.size(); i = j) {
        j = i;

        //! add
        before = work.query();
        while (j < Events.size()) {
            auto ev = Events[j];

            if (ev.first != Events[i].first || ev.second > 0) break;
            ev.second *= -1;

            work.update(1, 1, work.dim, R[ev.second].y1, R[ev.second].y2 - 1, +1);
            j++;
        }

        ans += work.query() - before;


        //! remove
        before = work.query();
        while (j < Events.size()) {
            auto ev = Events[j];

            if (ev.first != Events[i].first) break;

            work.update(1, 1, work.dim, R[ev.second].y1, R[ev.second].y2 - 1, -1);
            j++;
        }

        ans += -work.query() + before;

    }

}

int main()
{
    freopen("picture.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) R[i].read();

    //! for one part
    process();

    //! for other part
    for (i = 1; i <= n; i++) {
        swap(R[i].x1, R[i].y1);
        swap(R[i].x2, R[i].y2);
    }
    process();

    printf("%d", ans);



    return 0;
}
