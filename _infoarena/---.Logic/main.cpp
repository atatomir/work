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

#define maxDim 311

bool is_letter(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_operation(char c) {
    return c == '|' || c == '&' || c == '^' || c == '~';
}

int n, i, j, k, dim, cnt, state;
char s[maxDim];
string a, b;
string pol_a, pol_b;
int id[maxDim];
stack<char> S;
stack<int> aux;

int first_use[333];

void get_string(string &ans) {
    int i;

    ans.clear();
    memset(s, 0, sizeof(s));

    scanf("%s\n", s);
    dim = strlen(s);
    for (i = 0; i < dim; i++) {
        if (is_letter(s[i])) {
            if (id[ s[i] - 'a' ] == 0) id[ s[i] - 'a' ] = ++cnt;
            s[i] = id[ s[i] - 'a' ] + 'a' - 1;
        }

        ans.pb(s[i]);
    }
}

void _transform(string &dest, string &src) {
    while (!S.empty()) S.pop();
    dest.clear();

    for (auto e : src) {
        if (e == '(') {
            S.push('(');
            continue;
        }

        if (e == ')') {
            while (S.top() != '(') {
                dest.pb(S.top());
                S.pop();
            }
            S.pop();
            continue;
        }

        if (is_operation(e) && e != '~') {
            while (!S.empty()) {
                char c = S.top();

                if (e == '(') break;
                if ( first_use[S.top()] < first_use[e] ) break;

                dest.pb(S.top());
                S.pop();
            }
            S.push(e);

            continue;
        }

        if (e == '~') {
            S.push('~');
            continue;
        }

        //! it is a letter
        dest.pb(e);
    }

    while (!S.empty()) {
        dest.pb(S.top());
        S.pop();
    }
}

int vals(int x) {
    return ((state & (1 << x)) != 0 ? 1 : 0);
}

int evaluate(string &who) {
    int a, b;
    while (!aux.empty()) aux.pop();

    for (auto e : who) {
        if (is_letter(e)) {
            aux.push(vals( e - 'a' ));
            continue;
        }

        a = aux.top(); aux.pop();

        if (e == '~') {
            a ^= 1;
            aux.push(a);

            continue;
        }

        b = aux.top(); aux.pop();

        if (e == '|') aux.push(a | b);
        if (e == '&') aux.push(a & b);
        if (e == '^') aux.push(a ^ b);
    }

    return aux.top();
}

int main()
{
    freopen("logic.in","r",stdin);
    freopen("logic.out","w",stdout);

    first_use['&'] = 3;
    first_use['^'] = 2;
    first_use['|'] = 1;
    first_use['~'] = 4;

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        memset(id, 0, sizeof(id));
        cnt = 0;
        get_string(a);
        get_string(b);


        _transform(pol_a, a);
        _transform(pol_b, b);

        int lim = cnt;
        int pow_lim = 1 << lim;

        bool good = true;

        for (state = 0; state < pow_lim; state++) {
            if (evaluate(pol_a) != evaluate(pol_b)) {
                good = false;
                break;
            }
        }

        if (good)
            printf("egale\n");
        else
            printf("diferite\n");
    }



    return 0;
}
