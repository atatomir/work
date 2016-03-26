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
#define Point pair<int, int>

#define maxN 2016

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 5);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();
            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }
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

Buffer fin("dsip.in", 1 << 22);

struct node {
    Point top;
    int x_min, x_max, y_min, y_max;
    int cnt;
    node* son[2];

    node(Point act) {
        top = act;
        x_min = x_max = top.first;
        y_max = y_min = top.second;
        cnt = 1;
        son[0] = son[1] = NULL;
    }
};

int n, m, i;
Point P[maxN];
node *Head;

Point dA, dB;
Point p1;
int ans_le, ans_ri;


Point diff(Point A, Point B) {
    B.first -= A.first;
    B.second -= A.second;

    return B;
}

int cross(Point A, Point B) {
    return A.first * B.second - A.second * B.first;
}

bool intersect(Point p2, Point p3) {
    p2.first -= dA.first;
    p2.second -= dA.second;
    p3.first -= dA.first;
    p3.second -= dA.second;

    return 1LL * cross(p1, p2) * cross(p1, p3) <= 0;
}

bool cmp2(const Point& a, const Point& b) {
    return a.second < b.second;
}

void update(node* act, node* aux) {
    act->x_min = min(act->x_min, aux->x_min);
    act->x_max = max(act->x_max, aux->x_max);

    act->y_min = min(act->y_min, aux->y_min);
    act->y_max = max(act->y_max, aux->y_max);

    act->cnt += aux->cnt;
}

node* init(int l, int r, bool by_x) {
    if (l > r) return NULL;
    if (l == r)
        return new node(P[l]);

    int mid = (l + r) >> 1;

    if (by_x)
        nth_element(P + l, P + mid, P + r + 1);
    else
        nth_element(P + l, P + mid, P + r + 1, cmp2);

    node *act = new node(P[mid]);
    act->son[0] = init(l, mid - 1, by_x ^ 1);
    act->son[1] = init(mid + 1, r, by_x ^ 1);

    if (act->son[0]) update(act, act->son[0]);
    if (act->son[1]) update(act, act->son[1]);

    return act;
}

void query(node* act) {
    int act_cross = cross(diff(dA, dB), diff(dA, act->top));

    bool is_divided = false;
    if (intersect(mp(act->x_min, act->y_min), mp(act->x_min, act->y_max))) is_divided = true;
    else
    if (intersect(mp(act->x_min, act->y_min), mp(act->x_max, act->y_min))) is_divided = true;
    else
    if (intersect(mp(act->x_max, act->y_max), mp(act->x_min, act->y_max))) is_divided = true;
    else
    if (intersect(mp(act->x_max, act->y_max), mp(act->x_max, act->y_min))) is_divided = true;

    if (is_divided) {
        //! in both parts

        if (act_cross < 0)
            ans_le++;
        if (act_cross > 0)
            ans_ri++;

        if (act->son[0]) query(act->son[0]);
        if (act->son[1]) query(act->son[1]);
    } else {
        //! all in one part

        if (act_cross < 0)
            ans_le += act->cnt;
        else
            ans_ri += act->cnt;

        if (act_cross == 0)
            cerr << "Error!";
    }
}


int main()
{
    //freopen("dsip.in","r",stdin);
    freopen("dsip.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++) fin >> P[i].first >> P[i].second;
    Head = init(1, n, true);

    //m = 10000;

    for (i = 1; i <= m; i++) {
        fin >> dA.first >> dA.second >> dB.first >> dB.second;
        ans_le = ans_ri = 0;

        p1 = diff(dA, dB);

        query(Head);
        if (ans_le > ans_ri) swap(ans_le, ans_ri);

        printf("%d %d\n", ans_le, ans_ri);
    }


    return 0;
}
