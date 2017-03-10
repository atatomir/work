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

#define mod 666019
#define moddo 1000007
#define base 101
#define sigma 26

#define maxN 5555

ll pre[sigma + 10];
ll pre_sim[sigma + 10];

struct my_hash {
    ll a[4];
    ll hsh;

    my_hash() {
        a[0] = a[1] = a[2] = a[3] = hsh = 0;
    }

    void ini() {
        a[0] = a[1] = a[2] = a[3] = hsh = 0;
    }

    void add(int pos) {
        static int p1, p2;
        p1 = pos / 7;
        p2 = pos % 7;

        hsh += pre[pos];
        if (hsh >= moddo) hsh -= moddo;

        a[p1] += pre_sim[p2];
    }

    bool operator==(const my_hash& who) {
        if (a[0] == who.a[0])
            if (a[1] == who.a[1])
                if (a[2] == who.a[2])
                    if (a[3] == who.a[3])
                        return true;
        return false;
    }
};

int n, i, j, dim, cdim;
char s[maxN], c[maxN];
ll act;

vector< pair<my_hash, int> > data[moddo];
int dp[maxN];

pair<my_hash, int>& get_adress(const my_hash H) {
    for (auto &e : data[H.hsh]) {
        if (e.first == H)
            return e;
    }

    data[H.hsh].pb(mp(H, 0));
    return data[H.hsh].back();
}

int get_val(const my_hash H) {
    for (auto &e : data[H.hsh]) {
        if (e.first == H)
            return e.second;
    }

    return 0;
}

void add_word() {
    int i;
    my_hash act;

    for (i = 1; i <= cdim; i++) {
        act.add(c[i] - 'a');
    }

    pair<my_hash, int>& pp = get_adress(act);
    pp.second++;
}

int main()
{
    freopen("propozitie2.in","r",stdin);
    freopen("propozitie2.out","w",stdout);

    pre[0] = 1;
    pre_sim[0] = 1;
    for (i = 1; i < sigma + 1; i++) {
        pre[i] = (1LL * pre[i - 1] * base) % moddo;
        pre_sim[i] = pre_sim[i - 1] * base;
    }

    scanf("%s\n", s + 1);
    dim = strlen(s + 1);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", c + 1);
        cdim = strlen(c + 1);
        add_word();
        memset(c, 0, cdim + 3);
    }

    int i, j, pp;
    my_hash act;
    ll aux;

    dp[0] = 1;
    for (i = 1; i <= dim; i++) {
        act.ini();
        aux = 0;

        for (j = i; j > 0 && (i - j + 1 <= 100); j--) {
            act.add(s[j] - 'a');
            aux += (1LL * dp[j - 1] * get_val(act)) % mod;
        }

        dp[i] = aux % mod;
    }

    printf("%d", dp[dim]);



    return 0;
}
