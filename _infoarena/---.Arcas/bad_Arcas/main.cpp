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

#define lSon (node << 1)
#define rSon (lSon | 1)
#define pii pair<int, int>

#define maxN 100011
#define def 100000

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

Buffer fin("arcas.in", 1 << 22);


int id;

class aint {
    public:
        int dim;

        void init(int _dim, vector<int> *_data_one, vector<int> *_data_two) {
            dim = _dim;
            data_add = _data_one;
            data_rm = _data_two;
        }

        void add_target(int node, int l, int r, int x, int y1, int y2) {
            data_add[node].pb(y1);
            data_rm[node].pb(y2 + 1);

            if (l == r) return;

            int mid = (l + r) >> 1;
            if (x <= mid)
                add_target(lSon, l, mid, x, y1, y2);
            else
                add_target(rSon, mid + 1, r, x, y1, y2);
        }

        void arrange(int node, int l, int r) {
            sort(data_add[node].begin(), data_add[node].end());
            sort(data_rm[node].begin(), data_rm[node].end());

            if (l == r) return;

            int mid = (l + r) >> 1;
            arrange(lSon, l, mid);
            arrange(rSon, mid + 1, r);
        }

        int query(int node, int l, int r, int qL, int qR, int y) {
            if (qL <= l && r <= qR) {
                vector<int>::iterator it1 = upper_bound(data_add[node].begin(), data_add[node].end(), y);
                vector<int>::iterator it2 = upper_bound(data_rm[node].begin(), data_rm[node].end(), y);

                return (it1 - data_add[node].begin()) - (it2 - data_rm[node].begin()) ;
            }

            int ans = 0;
            int mid = (l + r) >> 1;

            if (qL <= mid)
                ans += query(lSon, l, mid, qL, qR, y);
            if (qR >  mid)
                ans += query(rSon, mid + 1, r, qL, qR, y);

            return ans;
        }

    private:
        vector<int> *data_add;
        vector<int> *data_rm;
};



int n, m, i;
int pos_x, pos_y1, pos_y2;
int pos_r, pos_y;

vector<int> aint_data1[maxN << 2];
vector<int> aint_data2[maxN << 2];
aint work;

int main()
{
    //freopen("arcas.in","r",stdin);
    freopen("arcas.out","w",stdout);

    work.init(def, aint_data1, aint_data2);

    fin >> n >> m;
    for (i = 1; i <= n; i++) {
        fin >> pos_x >> pos_y1 >> pos_y2;
        work.add_target(1, 1, def, pos_x, pos_y1 - pos_x, pos_y2 - pos_x);
    }

    work.arrange(1, 1, def);

    for (i = 1; i <= m; i++) {
        fin >> pos_x >> pos_y >> pos_r;
        printf("%d\n", work.query(1, 1, def, pos_x, pos_x + pos_r, pos_y - pos_x));
    }


    return 0;
}
