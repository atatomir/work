#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 355
#define mod 1000000007

int cnt;
ll aux[103][103];

struct matrix {
    ll data[103][103];

    void init() {
        memset(data, 0, sizeof(data));
        for (int i = 1; i <= cnt; i++)
            data[i][i] = 1;
    }

    void operator*=(matrix who) {
        int i, j, k;
        memcpy(aux, data, sizeof(data));
        memset(data, 0, sizeof(data));

        for (i = 1; i <= cnt; i++) {
            for (j = 1; j <= cnt; j++) {
                if (aux[i][j] == 0) continue;

                for (k = 1; k <= cnt; k++) {
                    data[i][k] += aux[i][j] * who.data[j][k];
                }
            }
        }

        for (i = 1; i <= cnt; i++)
            for (j = 1; j <= cnt; j++)
                data[i][j] %= mod;
    }
};

int n, i;
char code[maxN][maxN];
int dim[maxN];
map<string, int> M;

ll work[103];
int glob_ln;
matrix toto;

bool is_char(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

void get_vars(char* data, int sz) {
    int i;
    string aux;

    for (i = 1; i <= sz; i++) {
        if (!is_char(data[i]))
            continue;

        aux.clear();
        while (is_char(data[i])) {
            aux.pb(data[i]);
            i++;
        }

        if (M[aux] == 0)
            M[aux] = ++cnt;
    }
}

matrix poww(matrix a, int b) {
    matrix ans = a;
    b--;

    while (b > 0) {
        if (b & 1) ans *= a;
        b >>= 1;
        a *= a;
    }

    return ans;
}

int get_var(char* data, int pos, int& sol) {
    string aux = "";
    while (is_char(data[pos])) {
        aux.pb(data[pos]);
        pos++;
    }

    sol = M[aux];
    return pos;
}

int get_number(char* data, int pos, int& sol) {
    sol = 0;

    while (!is_digit(data[pos])) pos++;

    while (is_digit(data[pos])) {
        sol = (sol * 10 + data[pos] - '0');
        pos++;
    }

    return pos;
}

matrix solve(int ln, int times) {
    int pos, i;
    matrix act;

    act.init();

    while (ln <= n) {
        pos = 1;
        while (code[ln][pos] == ' ' && pos <= dim[ln]) pos++;
        if (pos > dim[ln]) continue;

        if (code[ln][pos] == '}') {
            glob_ln = ln;
            return poww(act, times);
        }

        if (is_char(code[ln][pos]) || code[ln][pos] == 'R') {
            // atribuire
            int to_attr, actid;

            if (code[ln][pos] != 'R')
                pos = get_var(code[ln], pos, to_attr);
            else
                to_attr = -1;

            memset(work, 0, sizeof(work));
            while (pos <= dim[ln]) {
                while (pos <= dim[ln] && !is_digit(code[ln][pos]) && !is_char(code[ln][pos])) pos++;
                if (pos > dim[ln]) continue;

                if (is_char(code[ln][pos])) {
                    pos = get_var(code[ln], pos, actid);
                    for (i = 1; i <= cnt; i++) {
                        work[i] += act.data[actid][i];
                        if (work[i] >= mod)
                            work[i] -= mod;
                    }
                } else {
                    pos = get_number(code[ln], pos, actid);
                    work[cnt] += actid;
                    if (work[cnt] >= mod)
                        work[cnt] -= mod;
                }
            }

            if (to_attr != -1) {
                memcpy(act.data[to_attr], work, sizeof(work));
            } else {
                printf("%d", work[cnt]);
                exit(0);
            }

        } else {
            // ciclu
            int next_times;
            pos = get_number(code[ln], pos, next_times);

            matrix toto = act;
            act = solve(ln + 1, next_times);
            act *= toto;
            ln = glob_ln;
        }

        ln++;
    }

    glob_ln = ln;
    return poww(act, times);
}

int main()
{
    freopen("cowbasic.in","r",stdin);
    freopen("cowbasic.out","w",stdout);

    while (!feof(stdin)) {
        n++;
        gets(code[n] + 1);
        dim[n] = strlen(code[n] + 1);

        get_vars(code[n], dim[n]);
    }

    while (code[n][1] != 'R') n--;

    cnt++;
    matrix ans = solve(1, 1);


    return 0;
}
