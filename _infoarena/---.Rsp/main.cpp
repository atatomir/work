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

#define maxN 100111
#define inf 1000000

struct state {
    int data[2][2];

    state() {
        data[0][0] = inf;
        data[0][1] = data[1][0] = 1;
        data[1][1] = 2;
    }

    state(int val) {
        data[0][0] = data[0][1] = data[1][0] = data[1][1] = inf;
    }
};

int t, ti;
int n, i;
char s[maxN];

stack<char> S;
vector<char> pol;

stack< state > work;

int sol;



void compute_pol() {
    int i;

    s[++n] = ')';
    pol.clear();
    S.push('(');

    for (i = 1; i <= n; i++) {
        if (s[i] == 'B') {
            pol.pb('B');
        }

        if (s[i] == 'S') {
            while (S.top() == 'P') pol.pb('P'), S.pop();
            while (S.top() == 'S') pol.pb('S'), S.pop();
            S.push('S');
        }

        if (s[i] == 'P') {
            while (S.top() == 'P') pol.pb('P'), S.pop();
            S.push('P');
        }

        if (s[i] == '(') {
            S.push('(');
        }

        if (s[i] == ')') {
            while (S.top() != '(') pol.pb(S.top()), S.pop();
            S.pop();
        }
    }
}

state solve() {
    int i;
    int b1, b2, b3;
    state a, b, act;

    while (!work.empty()) work.pop();
    for (auto ch : pol) {
        if (ch == 'B') {
            work.push(state());
        }

        if (ch == 'S') {
            a = work.top(); work.pop();
            b = work.top(); work.pop();
            swap(a, b);

            act = state(inf);

            for (b1 = 0; b1 < 2; b1++)
                for (b2 = 0; b2 < 2; b2++)
                    for (b3 = 0; b3 < 2; b3++)
                        act.data[b1][b3] = min(act.data[b1][b3], a.data[b1][b2] + b.data[b2][b3] - b2);

            work.push(act);
        }

        if (ch == 'P') {
            a = work.top(); work.pop();
            b = work.top(); work.pop();
            swap(a, b);

            act = state(inf);

            for (b1 = 0; b1 < 2; b1++)
                for (b2 = 0; b2 < 2; b2++)
                    act.data[b1][b2] = min(act.data[b1][b2], a.data[b1][b2] + b.data[b1][b2] - b1 - b2);

            work.push(act);
        }
    }

    return work.top();
}




int main()
{
    freopen("rsp.in","r",stdin);
    freopen("rsp.out","w",stdout);

    for (scanf("%d\n", &t), ti = 1; ti <= t; ti++) {
        memset(s, 0, sizeof(s));
        scanf("%s\n", s + 1);
        n = strlen(s + 1);

        compute_pol();
        state ans = solve();

        sol = inf;
        for (int b1 = 0; b1 < 2; b1++)
            for (int b2 = 0; b2 < 2; b2++)
                sol = min(sol, ans.data[b1][b2]);

        printf("%d\n", sol);
    }


    return 0;
}
