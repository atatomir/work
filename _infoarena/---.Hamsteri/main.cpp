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

#define maxN 3024
#define maxQ 300011

class OutParser {
private:
    FILE *fout;
    char *buff;
    int sp;

    void write_ch(char ch) {
        if (sp == 50000) {
            fwrite(buff, 1, 50000, fout);
            sp = 0;
            buff[sp++] = ch;
        } else {
            buff[sp++] = ch;
        }
    }


public:
    OutParser(const char* name) {
        fout = fopen(name, "w");
        buff = new char[50000]();
        sp = 0;
    }
    ~OutParser() {
        fwrite(buff, 1, sp, fout);
        fclose(fout);
    }

    OutParser& operator << (int vu32) {
        if (vu32 <= 9) {
            write_ch(vu32 + '0');
        } else {
            (*this) << (vu32 / 10);
            write_ch(vu32 % 10 + '0');
        }
        return *this;
    }

    OutParser& operator << (long long vu64) {
        if (vu64 <= 9) {
            write_ch(vu64 + '0');
        } else {
            (*this) << (vu64 / 10);
            write_ch(vu64 % 10 + '0');
        }
        return *this;
    }

    OutParser& operator << (char ch) {
        write_ch(ch);
        return *this;
    }
    OutParser& operator << (const char *ch) {
        while (*ch) {
            write_ch(*ch);
            ++ch;
        }
        return *this;
    }
};

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
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

int n, q, i, j;
ll X[maxN];
ll dp[maxN][maxN];
ll pos, disc;



void comp_dp() {
    int i, j, pos;
    ll last;

    for (i = 1; i <= n; i++) dp[1][i] = X[i] - X[1];

    for (i = 2; i <= n; i++) {
        pos = 1;
        for (j = i; j <= n; j++) {
            last = max(X[j] - X[pos], dp[i - 1][pos - 1]);
            while (pos + 1 <= j && last >= max(X[j] - X[pos + 1], dp[i - 1][pos])) {
                pos++;
                last = max(X[j] - X[pos], dp[i - 1][pos - 1]);
            }

            dp[i][j] = max(X[j] - X[pos], dp[i - 1][pos - 1]);
        }
    }
}

int cb(int pos, ll val) {
    int ans = 0;

    for (int step = (1 << 11); step > 0; step >>= 1)
        if (ans + step <= pos)
            if (dp[ans + step][pos] > val)
                ans += step;

    return ans + 1;
}

int main()
{
    Buffer fin("hamster.in", 1 << 20);
    OutParser fout("hamster.out");

    fin >> n >> q;
    for (i = 1; i <= n; i++) fin >> X[i];

    comp_dp();
    for (i = 1; i <= q; i++) {
        fin >> pos >> disc;

        int ans = cb(pos, disc);
        fout << ans << '\n';
    }



    return 0;
}
