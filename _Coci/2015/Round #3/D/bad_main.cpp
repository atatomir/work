#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define ll long long

int n, i, p, m;
char s[maxN];

vector<ll> pol;
char St[maxN];
int dim;

vector< pair<ll, ll> > use;

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

bool isSign(char c) {
    return c == '*' || c == '+' || c == '-';
}

ll getNumber() {
    int ini = i;
    int las = ini;
    ll ans = 0;

    while (isDigit(s[las + 1])) las++;

    for (int k = ini; k <= las; k++)
        ans = ans * 10 + s[k] - '0';

    i = las + 1;
    return ans % m;
}

void to_pol() {
    int newN = n + 1;
    s[0] = '(';
    s[newN] = ')';

    for (i = 0; i <= newN; ) {
        if (isDigit(s[i])) {
            pol.pb( getNumber() );
        }
        else
        if (s[i] == 'x') {
            pol.pb(-'x');
            i++;
        }
        else
        if (s[i] == '+' || s[i] == '-') {
            while (isSign(St[dim])) {
                pol.pb(-St[dim]);
                dim--;
            }

            St[++dim] = s[i];
            i++;
        }
        else
        if (s[i] == '*') {
            St[++dim] = s[i];
            i++;
        }
        else
        if (s[i] == '(') {
            St[++dim] = s[i];
            i++;
        } else
        if (s[i] == ')') {
            while (St[dim] != '(') {
                pol.pb(-St[dim]);
                dim--;
            }

            dim--;
            i++;
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s\n%d%d", s + 1, &p, &m);
    n = strlen(s + 1);

    to_pol();

    use.clear();
    for (auto el : pol) {
        if (el == -'x') {
            use.pb(mp(1, 0));
        }
        else
        if (el >= 0) {
            use.pb(mp(0, el));
        }
        else
        if (el == -'+') {
            auto e2 = use[ use.size() - 1 ]; use.pop_back();
            auto e1 = use[ use.size() - 1 ]; use.pop_back();

            e1.first += e2.first;
            e1.second += e2.second;
            use.pb(e1);
        }
        else
        if (el == -'-') {
            auto e2 = use[ use.size() - 1 ]; use.pop_back();
            auto e1 = use[ use.size() - 1 ]; use.pop_back();

            e1.first -= e2.first;
            e1.second -= e2.second;
            use.pb(e1);
        }
        else
        if (el == -'*') {
            auto e2 = use[ use.size() - 1 ]; use.pop_back();
            auto e1 = use[ use.size() - 1 ]; use.pop_back();

            pair<ll, ll> aux;

            aux.second = e1.second * e2.second;
            aux.first = e1.first * e2.second + e1.second * e2.first;
            use.pb(aux);
        }
    }

    if (use.size() != 1) {
        cerr << "Error";
        return 0;
    }

    ll a = use[0].first;
    ll b = use[0].second;

    //cerr << a << ' ' << b;

    long long now = 0;
    for (long long xx = 0; ; xx++) {
        now = xx * a + 1LL * b;
        if (now % m == p) {
            printf("%lld", xx);
            return 0;
        }
    }

    return 0;
}
