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

#define def 1000

struct state {
    int i;
    vector<int> data;

    void init() { data = vector<int>(def, 0); }

    void operator+=(state &who) {
        data.resize(max(data.size(), who.data.size()));

        for (i = 0; i < who.data.size(); i++)
            data[i] += who.data[i];
    }

    void operator-=(state &who) {
        data.resize(max(data.size(), who.data.size()));

        for (i = 0; i < who.data.size(); i++)
            data[i] -= who.data[i];
    }

    void operator>>=(int how) {
        for (i = how; i < data.size(); i++)
            data[i - how] = data[i];
        data.resize(max(0, (int)data.size() - how));
    }

    void operator<<=(int how) {
        data.resize(data.size() + how);
        for (i = data.size() - 1; i >= how; i--)
            data[i] = data[i - how];
        for (i = 0; i < how; i++) data[i] = 0;
    }

    state operator*(state who) {
        if (data.empty()) {
            state aux;
            aux.data = {0};
            return aux;
        }

        if (data.size() == 1 || who.data.size() == 1) {
            state a = *this;
            state b = who;

            if (a.data.size() < b.data.size()) swap(a, b);
            for (i = 0; i < a.data.size(); i++)
                a.data[i] *= b.data[0];

            return a;
        }

        int mid = data.size() / 2;

        state a0 = *this; a0 >>= mid;
        state a1 = *this; a1.data.resize(mid);

        state b0 = who; b0 >>= mid;
        state b1 = who; b1.data.resize(mid);

        state z1 = a0 * b0;
        state z3 = a1 * b1;

        state a01 = a0; a01 += a1;
        state b01 = b0; b01 += b1;
        state z2 = a01 * b01; z2 -= z1; z2 -= z3;

        state ans = z1; ans <<= mid;
        ans += z2; ans <<= mid;
        ans += z3;

        return ans;
    }
};


int t, ti;
int n, m, i, x;
state a, b, ans;


int main()
{
    freopen("bacterii2.in","r",stdin);
    freopen("bacterii2.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        a.init(); b.init();

        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%d", &x);
            a.data[x - 1]++;
        }

        scanf("%d", &m);
        for (i = 1; i <= m; i++) {
            scanf("%d", &x);
            b.data[x - 1]++;
        }

        ans = a * b;

        for (i = 0; i < ans.data.size(); i++)
            if (ans.data[i])
                printf("%d %d\n", i + 2, ans.data[i]);

        printf("\n");
    }


    return 0;
}
