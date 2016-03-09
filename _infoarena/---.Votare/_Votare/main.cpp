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

#define maxN 100011
#define inf (1LL << 60)
#define mini_inf 1 << 30

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 10);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();

            int diff = 1;
            if (data[pos] == '-') {
                diff = -1;
                if (++pos == dim)
                    refill();
            }

            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= diff;
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }

        bool is_digit(char c) {
            return ('0' <= c && c <= '9') || c == '-';
        }
};

Buffer fin("votare.in", 1 << 20);

struct node {
    node *lSon, *rSon;
    int x, y;
    bool cnt;
    bool by_x; //! divide by x or by y

    int worth;
    int x_min, x_max, y_min, y_max;

    node(int _x, int _y, bool _by_x) {
        lSon = rSon = NULL;
        x = _x; y = _y;
        cnt = 0;
        by_x = _by_x;
        worth = 0;
    }
};

struct op {
    int type, x, y;

    void read() {
        fin >> type >> x >> y;
    }
};

int n, m, i, x, y;
op todo[maxN];
vector< pair<int, int> > Points;
node* Head;

queue<node*> Q;

int region_x;
int region_y;
ll dist;
ll real_dist;

bool by_y_sort(const pair<int, int>& a, const pair<int, int>& b) {
    if(a.second != b.second)
        return a.second < b.second;
    return a.first < b.first;
}

node* build_tree(int l, int r, bool by_x, int _x_min, int _y_min, int _x_max, int _y_max) {
    if (l > r)
        return NULL;
    if (l == r) {
        node* act = new node(Points[l].first, Points[l].second, by_x);

        act->x_min = _x_min;
        act->y_min = _y_min;
        act->x_max = _x_max;
        act->y_max = _y_max;

        return act;
    }


    //! select middle and split value
    int mid = (l + r) >> 1;
    if(by_x)
        nth_element(Points.begin() + l, Points.begin() + mid, Points.begin() + r + 1);
    else
        nth_element(Points.begin() + l, Points.begin() + mid, Points.begin() + r + 1, by_y_sort);

    node* act = new node(Points[mid].first, Points[mid].second, by_x);

    act->x_min = _x_min;
    act->y_min = _y_min;
    act->x_max = _x_max;
    act->y_max = _y_max;

    if (by_x) {
        act->lSon = build_tree(l, mid - 1, by_x ^ 1, _x_min, _y_min, Points[mid].first, _y_max);
        act->rSon = build_tree(mid + 1, r, by_x ^ 1, Points[mid].first, _y_min, _x_max, _y_max);
    } else {
        act->lSon = build_tree(l, mid - 1, by_x ^ 1, _x_min, _y_min, _x_max, Points[mid].second);
        act->rSon = build_tree(mid + 1, r, by_x ^ 1, _x_min, Points[mid].second, _x_max, _y_max);
    }

    return act;
}

node* find_node(node* act, int x, int y, int v) {
    if (act == NULL) return NULL;

    act->worth += v;
    if (act->x == x && act->y == y) return act;

    if (act->by_x) {
        if ( mp(x, y) < mp(act->x, act->y) )
            return find_node(act->lSon, x, y, v);
        else
            return find_node(act->rSon, x, y, v);
    } else {
        if ( mp(y, x) < mp(act->y, act->x) )
            return find_node(act->lSon, x, y, v);
        else
            return find_node(act->rSon, x, y, v);
    }
}

bool in_rectangle(node* act) {
    /*if (act->x_min <= region_x && act->x_max >= region_x)
        if (act->y_min <= region_y && act->y_max >= region_y)
            return true;
    */

    pair<int, int> a = mp(act->x_min, act->x_max);
    pair<int, int> b = mp(region_x - real_dist, region_x + real_dist);

    if (a > b) swap(a, b);
    if (a.second <= b.first) return false;

    a = mp(act->y_min, act->y_max);
    b = mp(region_y - real_dist, region_y + real_dist);

    if (a > b) swap(a, b);
    if (a.second <= b.first) return false;


    return true;
}

void query(node *act) {
    int i, j, x, y;

    while (!Q.empty()) Q.pop();
    Q.push(act);

    while (!Q.empty()) {
        act = Q.front(); Q.pop();
        if (act == NULL) continue;
        if (act->worth == 0) continue;

        //! if this node is valid
        if (act->cnt > 0) {
            ll now_dist = 1LL * (region_x - act->x) * (region_x - act->x) +
                          1LL * (region_y - act->y) * (region_y - act->y) ;
            if (now_dist < dist) {
                dist = now_dist;
                real_dist = 1 + sqrt(dist);
            }
        }


        if (act->lSon)
            if (in_rectangle(act->lSon))
                Q.push(act->lSon);
        if (act->rSon)
            if (in_rectangle(act->rSon))
                Q.push(act->rSon);

    }
}

int main()
{
    //freopen("votare.in","r",stdin);
    freopen("votare.out","w",stdout);

    fin >> m;
    for (i = 1; i <= m; i++) {
        todo[i].read();

        if (todo[i].type != 0) continue;
        Points.pb(mp(todo[i].x, todo[i].y));
    }

    sort(Points.begin(), Points.end());
    Points.resize(unique(Points.begin(), Points.end()) - Points.begin());
    n = Points.size();

    Head = build_tree(0, n - 1, true, -mini_inf, -mini_inf, mini_inf, mini_inf); //! first time by x

    for (i = 1; i <= m; i++) {
        x = todo[i].x;
        y = todo[i].y;

        if (todo[i].type == 0) { //! add
            node* aux = find_node(Head, x, y, 0);
            if (aux->cnt == false) find_node(Head, x, y, +1);
            aux->cnt = true;
        }

        if (todo[i].type == 1) { //! remove
            node* aux = find_node(Head, x, y, 0);
            if (aux != NULL) {
                if (aux->cnt == true) find_node(Head, x, y, -1);
                aux->cnt = false;
            }
        }

        if (todo[i].type == 2) { //! query
            dist = inf;
            real_dist = sqrt(dist) + 1;
            region_x = x;
            region_y = y;

            query(Head);

            if (dist == inf) dist = -1;
            printf("%lld\n", dist);
        }
    }

    return 0;
}
