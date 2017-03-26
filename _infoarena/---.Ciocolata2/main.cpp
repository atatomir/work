#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 75

int defX[4] = {0, 0, -1, 1};
int defY[4] = {-1, 1, 0, 0};

class Buffer {
    public:
        Buffer(string name, int _dim) {
            if (name != "")
                freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
            T sign = +1;
            dest = 0;

            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            if (data[pos] == '-') {
                sign = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sign;
            return *this;
        }


    private:
        int pos, dim;
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

class Writer {
  public:
    Writer(const char *name):
        m_stream(name) {
        memset(m_buffer, 0, sizeof(m_buffer));
        m_pos = 0;
    }

    Writer& operator<<(int a) {
        int many = 0;
        do {
            digit_buffer[many++] = a % 10 + '0';
            a /= 10;
        } while (a > 0);
        for (int i = many - 1; i >= 0; --i)
            putchar(digit_buffer[i]);
        return *this;
    }

    Writer& operator<<(const char *s) {
        for (; *s; ++s)
            putchar(*s);
        return *this;
    }

    ~Writer() {
        m_stream.write(m_buffer, m_pos);
    }

  private:
    void putchar(char c) {
        m_buffer[m_pos++] = c;
        if (m_pos == kBufferSize) {
            m_stream.write(m_buffer, m_pos);
            m_pos = 0;
        }
    }

    static const int kBufferSize = 32768;
    ofstream m_stream;
    char m_buffer[kBufferSize];
    char digit_buffer[30];
    int m_pos;
} fout("ciocolata2.out");

Buffer fin("ciocolata2.in", 1 << 20);

int n, m, k, i, cnt1, cnt2, need;
int id[maxN][maxN];
pair<int, int> pos[2][maxN * maxN];

vector<int> list[maxN * maxN];
bool us[maxN * maxN];
vector<int> backup;
int l[maxN * maxN], r[maxN * maxN], rez[maxN * maxN];
bool dead[2][maxN * maxN];

vector< pair<int, int> > to_add, to_rm;
vector<int> ord;

bool in[maxN * maxN];


void pre() {
    int i, j, p, xx, yy;

    cnt1 = cnt2 = 0;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if ((i + j) % 2 == 0) {
                id[i][j] = ++cnt1;
                pos[0][cnt1] = mp(i, j);
            } else {
                id[i][j] = ++cnt2;
                pos[1][cnt2] = mp(i, j);
            }
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if ((i + j) % 2 == 1) continue;

            for (p = 0; p < 4; p++) {
                xx = i + defX[p];
                yy = j + defY[p];

                if (id[xx][yy])
                    list[id[i][j]].pb(id[xx][yy]);
            }
        }
    }

    backup.reserve(n * m);
    for (i = 1; i <= cnt1; i++)
        ord.pb(i), in[i] = true;
}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;
    backup.pb(node);

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (dead[1][list[node][i]]) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--;
            continue;
        }

        if (r[to] == 0) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    for (auto to : list[node]) {
        if (pairUp(r[to])) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    return false;
}

void pair_them() {
    int i;
    bool ok = true;

    int aux = 0;
    for (i = 0; i < ord.size(); i++) {
        in[ord[i]] = false;
        if (dead[0][ ord[i] ] == false && l[ ord[i] ] == 0) {
            ord[aux++] = ord[i];
            in[ord[i]] = true;
        }
    }
    ord.resize(aux);

    while (ok) {
        ok = false;

        for (auto e : backup)
            us[e] = false;
        backup.clear();

        for (auto i : ord)
            if (!dead[0][i] && l[i] == 0)
                ok |= pairUp(i);
    }
}

bool get_difs() {
    int i, combs;

    combs = 0;
    if (need & 1)
        return false;

    to_add.clear();
    to_rm.clear();

    for (i = 1; i <= cnt1; i++) {
        if (l[i] != 0) combs++;
        if (l[i] == rez[i]) continue;

        to_rm.pb(mp(i, rez[i]));
        if (l[i] != 0)
            to_add.pb(mp(i, l[i]));
    }

    if (combs * 2 != need)
        return false;

    return true;
}

void do_step() {
    int i, x, y;
    int qq;

    memcpy(rez, l, sizeof(l));

    fin >> qq;
    for (i = 1; i <= qq; i++) {
        fin >> x >> y;
        need--;

        if ((x + y) % 2 == 0) {
            dead[0][id[x][y]] = true;

            r[ l[id[x][y]] ] = 0;
            l[ id[x][y] ] = 0;
        } else {
            dead[1][id[x][y]] = true;

            if (!in[ r[id[x][y]] ]) {
                in[ r[id[x][y]] ] = true;
                ord.pb(r[id[x][y]]);
            }

            l[ r[id[x][y]] ] = 0;
            r[ id[x][y] ] = 0;
        }
    }

    pair_them();
    if (!get_difs()) {
        fout << "-1";
        exit(0);
    }

    fout << to_rm.size() << "\n";
    for (auto e : to_rm)
        fout << pos[0][e.first].first << " " << pos[0][e.first].second << " " << pos[1][e.second].first << " " << pos[1][e.second].second << "\n";

    fout << to_add.size() << "\n";
    for (auto e : to_add)
        fout << pos[0][e.first].first << " " << pos[0][e.first].second << " " << pos[1][e.second].first << " " << pos[1][e.second].second << "\n";

}

int main()
{

    fin >> n >> m >> k; need = n * m;
    pre();

    pair_them();
    fout << need / 2 << "\n";
    for (i = 1; i <= cnt1; i++)
        fout << pos[0][i].first << " " << pos[0][i].second << " " << pos[1][l[i]].first << " " << pos[1][l[i]].second << "\n";

    for (i = 1; i <= k; i++)
        do_step();

    return 0;
}
