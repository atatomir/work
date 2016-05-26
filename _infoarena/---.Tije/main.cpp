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

#define maxN 111
//#define DEBUG

class Buffer {
    public:
        void flush() {
            fwrite(&data[0], 1, pos, stdout);
            pos = 0;
        }

        Buffer(string name, int _dim) {
            freopen(name.c_str(), "w", stdout);
            dim = _dim;
            data.resize(dim + 17);
            pos = 0;
            flush();
        }

        Buffer& operator<<(char c) {
            data[pos++] = c;
            if (pos >= dim) flush();

            return *this;
        }

        Buffer& operator<<(int a) {
            aux.clear();
            while (a) {
                aux.pb('0' + a % 10);
                a /= 10;
            }

            reverse(aux.begin(), aux.end());
            for (char e : aux) data[pos++] = e;
            if (pos >= dim) flush();

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;
        vector<char> aux;
};

Buffer fout("tije.out", 1 << 20);

int n, m, i, j, step;
bool us[maxN];
vector<int> to_move;

#ifdef DEBUG
    vector<int> aux[maxN];
#endif

void move(int a, int b) {
    fout << a << ' ' << b << '\n';

    #ifdef DEBUG
        aux[b].pb(aux[a].back());
        aux[a].pop_back();

        for (int i = 1; i <= n; i++) {
            cerr << "(";
            for (auto e : aux[i]) cerr << e << ',';
            cerr << ")";
        }
        cerr << '\n';
    #endif // DEBUG
}

void top_to_pos(int st, int pos) {
    int aux = (st == 1 ? 2 : 1);

    if (pos == 1) return;

    move(aux, n + 1);
    move(st, aux);
    for (int i = 1; i < pos; i++) move(st, n + 1);
    move(aux, st);
    for (int i = 1; i < pos; i++) move(n + 1, st);
    move(n + 1, aux);
}

void solve(int bg) {
    int i;
    to_move.clear();

    for (; us[bg] == false; bg = (bg + step) % n) {
        if (bg == 0) {
            bg = n;
            if (us[bg]) break;
        }

        to_move.pb(bg);
        us[bg] = true;
    }

    move(to_move[0], n + 1);
    for (i = 1; i < to_move.size(); i++) move(to_move[i], to_move[i - 1]);
    move(n + 1, to_move.back());
}

int main()
{
    freopen("tije.in","r",stdin);

    scanf("%d", &n);
    if (n == 1) return 0;

    #ifdef DEBUG
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                aux[i].pb(i);
    #endif // DEBUG

    for (i = 1; i < n; i++) {
        memset(us, 0, sizeof(us));
        step = i;

        for (j = 1; j <= n; j++)
            if (!us[j])
                solve(j);

        for (j = 1; j <= n; j++)
            top_to_pos(j, n - i);
    }

    fout.flush();

    return 0;
}
