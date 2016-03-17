#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxDim 271
#define sigma 33

int n, i;
char ap[maxDim];
int vars[sigma];
char F[sigma][maxDim];

int dimi;
char aux[maxDim];
int cnt_par[sigma];

int gl_pos;

vector<int> expr;
stack<int> sign;

int last_pos;


bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

bool is_lett(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_upper(char c) {
    return 'A' <= c && c <= 'Z';
}

int get_num(char *from) {
    int ans = 0;
    int sgn = 1;
    int pos = 0;

    if (from[0] == '-') {
        sgn = -1;
        pos++;
    }

    while (is_digit(from[pos])) {
        ans = ans * 10 + from[pos] - '0';
        pos++;
    }

    return sgn * ans;
}

void get_variable() {
    int wh = aux[1] - 'a';
    dimi = strlen(aux + 1);

    vars[wh] = get_num(aux + 3);
}

void get_function() {
    int i;
    int wh = aux[1] - 'A';

    char maxi = 'a';
    for (i = 2; aux[i] != ')'; i++)
        if ('a' <= aux[i] && aux[i] <= 'z')
            maxi = aux[i];

    cnt_par[wh] = maxi - 'a' + 1;

    dimi = strlen(aux + i + 2);
    memcpy(F[wh] + 1, aux + i + 2, dimi);
}

int evaluate(int id, int pos, vector<int> local) {
    int i, dim;
    int last, act;
    char sign;

    dim = strlen(F[id] + 1);

    i = pos;
    sign = '+';
    last = 0;
    act = 1;

    while (i <= dim) {
        if (is_lett(F[id][i])) {
            act *= local[ F[id][i] - 'a' ];
            i++;

            continue;
        }

        if (is_digit(F[id][i])) {
            act *= get_num(F[id] + i);
            while (is_digit(F[id][i])) i++;

            continue;
        }

        if (F[id][i] == '+' || F[id][i] == '-') {
            if (sign == '+')
                last += act;
            else
                last -= act;

            act = 1;
            sign = F[id][i];
            i++;

            continue;
        }

        if (F[id][i] == '*') {
            //! nothing to be done
            i++;

            continue;
        }

        if (F[id][i] == '(') {
            act *= evaluate(id, i + 1, local);
            i = last_pos + 1;

            continue;
        }

        break;
    }

    last_pos = i;

    if (sign == '+')
        last += act;
    else
        last -= act;

    return last;
}

int solve() {
    int i;
    vector<int> local;

    local.clear();

    int id = ap[gl_pos] - 'A';
    gl_pos += 2;

    for (int par = 1; par <= cnt_par[id]; par++) {
        if (is_digit(ap[gl_pos])) {
            local.pb(get_num(ap + gl_pos));
            while (is_digit(ap[gl_pos])) gl_pos++;
            gl_pos++;

            continue;
        }

        if (is_lett(ap[gl_pos])) {
            int var = vars[ ap[gl_pos] - 'a' ];
            local.pb(var);
            gl_pos += 2;

            continue;
        }

        if (is_upper(ap[gl_pos])) {
            local.pb(solve());
            gl_pos++;

            continue;
        }
    }

    return evaluate(id, 1, local);
}




int main()
{
    freopen("apel.in","r",stdin);
    freopen("apel.out","w",stdout);

    scanf("%s\n", ap + 1);
    n = strlen(ap + 1);

    while(true) {
        memset(aux, 0, sizeof(aux));
        scanf("%s\n", aux + 1);

        if (aux[1] == '\0') break;
        if ('a' <= aux[1] && aux[1] <= 'z')
            get_variable();
        else
            get_function();
    }

    gl_pos = 1;
    printf("%d", solve());


    return 0;
}
