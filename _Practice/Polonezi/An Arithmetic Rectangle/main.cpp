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

#define maxN 52

class Buffer {
    public:
        Buffer(int _dim) {
            dim = _dim;
            data.resize(dim + 7);
            refill();
        }

        bool is_dot() {
            while (!is_digit(data[pos]) && data[pos] != '-' && data[pos] != '.')
                if (++pos == dim)
                    refill();

            if (data[pos] != '.') return false;

            if (++pos == dim)
                refill();
            return true;
        }

        void read(int &dest) {
            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            int sgn = 1;
            if (data[pos] == '-') {
                sgn = -1;
                if (++pos == dim)
                    refill();
            }

            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sgn;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

struct rat {
    ll up, down;

    rat mk(ll a, ll b) {
        static rat ans;

        ans.up = a; ans.down = b;
        return ans;
    }

    void simp() {
        ll x = abs(up);
        ll y = abs(down);

        if (x < y) swap(x, y);
        while (y) {
            x %= y;
            swap(x, y);
        }

        up /= x; down /= x;

        if (down < 0) {
            up *= -1;
            down *= -1;
        }
    }

    rat operator*(const rat who) {
        static rat ans;

        ans = mk(up * who.up, down * who.down);
        ans.simp();

        return ans;
    }

    rat operator/(const rat who) {
        static rat ans;

        ans = mk(up * who.down, down * who.up);
        ans.simp();

        return ans;
    }

    rat operator+(const rat who) {
        static rat ans;

        ans = mk(up * who.down + who.up * down, down * who.down);
        ans.simp();

        return ans;
    }

    rat operator-(const rat who) {
        static rat ans;

        ans = mk(up * who.down - who.up * down, down * who.down);
        ans.simp();

        return ans;
    }

    void print() {
        simp();

        if (down == 1)
            printf("%lld ", up);
        else
            printf("%lld/%lld ", up, down);
    }

};

rat mk(ll a, ll b) {
    static rat ans;

    ans.up = a; ans.down = b;
    return ans;
}



int t, ti;
int n, m, i, j, x, id, rez;

vector< vector< rat > > data;
vector< rat > aux, act;
rat ans[maxN * maxN];


void rm_gauss() {
    int i, j, k, l;
    int ec = data.size();
    rat val;

    i = j = 0;
    while (i < ec && j < rez) {
        for (k = i; k < ec; k++)
            if (data[k][j].up != 0)
                break;

        if (k == ec) {
            j++;
            continue;
        }

        swap(data[i], data[k]);
        for (k = i + 1; k < ec; k++) {
            if (data[k][j].up == 0) continue;

            val = data[k][j] / data[i][j];
            for (l = j; l <= rez; l++)
                data[k][l] = data[k][l] - (data[i][l] * val);
        }

        i++; j++;
    }
}

bool solve() {
    int i, j, k;
    rat act;

    for (i = data.size() - 1; i >= 0; i--) {
        for (j = 0; j < rez && data[i][j].up == 0; j++);

        if (j == rez) {
            if (data[i][rez].up != 0) return false;
            continue;
        }

        act = data[i][rez];
        for (k = j + 1; k < rez; k++)
            act = act - (ans[k] * data[i][k]);

        ans[j] = act / data[i][j];
    }

    return true;
}



int main()
{
    freopen("test.in","r",stdin);
    Buffer fin(1 << 20);

    fin.read(t);
    for (ti = 1; ti <= t; ti++) {
        fin.read(n);
        fin.read(m);

        aux.resize(n * m + 2);
        for (i = 0; i < aux.size(); i++) aux[i] = mk(0, 1);
        data.clear();

        id = -1; rez = n * m;
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                id++;

                if (!fin.is_dot()) {
                    fin.read(x);

                    act = aux;
                    act[id] = mk(1, 1);
                    act[rez] = mk(x, 1);

                    data.pb(act);
                }

                if (i >= 3) {
                    act = aux;
                    act[id] = mk(1, 1);
                    act[id - m] = mk(-2, 1);
                    act[id - 2 * m] = mk(1, 1);

                    data.pb(act);
                }

                if (j >= 3) {
                    act = aux;
                    act[id] = mk(1, 1);
                    act[id - 1] = mk(-2, 1);
                    act[id - 2] = mk(1, 1);

                    data.pb(act);
                }
            }
        }

        for (i = 0; i <= n * m; i++) ans[i] = mk(0, 1);

        rm_gauss();
        if (!solve()) {
            printf("No solution.\n");
        } else {
            for (i = 1; i <= n; i++) {
                for (j = 1; j <= m; j++)
                    ans[ (i - 1) * m + (j - 1) ].print();
                printf("\n");
            }
        }
    }


    return 0;
}
