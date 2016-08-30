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
#define inf 1000000000

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

#define maxN (1024 * 1024 + 11)

int n, N, i, j, len, lim, new_v, pos;
int v[maxN], del[maxN];


int main()
{
    Buffer fin("viteze.in", 1 << 20);
    OutParser fout("viteze.out");

    fin >> n;
    for (i = 1; i <= n; i++)
        fin >> v[i];
    for (i = 1; i <= n; i++)
        fin >> del[i];
    v[1] = min(v[1], del[1]);

    for (N = 1; N < n; N <<= 1);
    for (i = n + 1; i <= N; i++) del[i] = inf;

    for (len = 1; 2 * len <= N; len <<= 1) {
        for (i = 1; i <= N; i += 2 * len) {
            lim = i + 2 * len - 1;

            for (j = i + len - 1; j < lim && v[j] + del[j + 1] < v[j + 1]; j++)
                v[j + 1] = v[j] + del[j + 1];
            for (j = i + len; j > i && v[j] + del[j] < v[j - 1]; j--)
                v[j - 1] = v[j] + del[j];
        }
    }

    for (i = 1; i <= n; i++)
        fout << v[i] << ' ';


    return 0;
}
