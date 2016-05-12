#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 50011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 7);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            dest = 0;
            int ind = 1;
            if (data[pos] == '-') {
                ind = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= ind;
            return *this;
        }


    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};


struct node {
    node* son[2];
    int x, y;
    bool valid;
    bool by_x;
    int down;

    node() {}

    node(int _x, int _y) {
        son[0] = son[1] = NULL;
        x = _x; y = _y;
        valid = false;
        by_x = false;
        down = 0;
    }
};

int n, i;
pair<int, int> P[maxN], ord[maxN];
node* Head;
queue<node*> Q;

pair<int, int> orig;
int best;


int dist(pair<int, int> a, pair<int, int> b) {
    int xx = a.first - b.first;
    if (xx < 0) xx = -xx;

    int yy = a.second - b.second;
    if (yy < 0) yy = -yy;

    return xx + yy;
}

bool cmpY(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

node* build(int l, int r, bool by_x) {
    if (r < l) return NULL;

    node* ans;
    int mid = (l + r) >> 1;

    if (by_x) {
        nth_element(P + l, P + mid, P + r + 1);
        ans = new node(P[mid].first, P[mid].second);
        ans->by_x = true;

        ans->son[0] = build(l, mid - 1, by_x ^ true);
        ans->son[1] = build(mid + 1, r, by_x ^ true);
    } else {
        nth_element(P + l, P + mid, P + r + 1, cmpY);
        ans = new node(P[mid].first, P[mid].second);
        ans->by_x = false;

        ans->son[0] = build(l, mid - 1, by_x ^ true);
        ans->son[1] = build(mid + 1, r, by_x ^ true);
    }

    return ans;
}

void update(node* R, pair<int, int> p) {
    R->down++;
    if (R->x == p.first && R->y == p.second) {
        R->valid = true;
        return;
    }

    if (R->by_x) {
        if (p < mp(R->x, R->y))
            update(R->son[0], p);
        else
            update(R->son[1], p);
    } else {
        if (mp(p.second, p.first) < mp(R->y, R->x))
            update(R->son[0], p);
        else
            update(R->son[1], p);
    }
}

int query(pair<int, int> p) {
    int i;
    node* act;

    orig = p;
    best = maxN * 2;
    while (!Q.empty()) Q.pop();
    Q.push(Head);

    while (!Q.empty()) {
        act = Q.front(); Q.pop();
        if (act == NULL) continue;
        if (act->down == 0) continue;

        if (act->valid) best = min(best, dist(orig, mp(act->x, act->y)));

        if (act->by_x) {
            if (orig.first - best <= act->x)
                Q.push(act->son[0]);
            if(orig.first + best >= act->x)
                Q.push(act->son[1]);
        } else {
            if (orig.second - best <= act->y)
                Q.push(act->son[0]);
            if (orig.second + best >= act->y)
                Q.push(act->son[1]);
        }
    }

    return best;
}



int main()
{
    Buffer fin("mindist.in", 1 << 20);
    freopen("mindist.out", "w", stdout);

    fin >> n;
    for (i = 1; i <= n; i++) fin >> P[i].first >> P[i].second, ord[i] = P[i];

    Head = build(1, n, true);

    printf("0\n");
    update(Head, mp(ord[1].first, ord[1].second));

    for (i = 2; i <= n; i++) {
        printf("%d\n", query(mp(ord[i].first, ord[i].second)));
        update(Head, mp(ord[i].first, ord[i].second));
    }

    return 0;
}
