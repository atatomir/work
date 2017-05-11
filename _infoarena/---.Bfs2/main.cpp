#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int n, m, q, i;
int B[maxN], F[maxN];
ll sB[maxN], sF[maxN];
ll S;

char tp;
int p1, p2;

vector<int> badB, badF;
bool is_badB[maxN], is_badF[maxN];
bool in_vectB[maxN], in_vectF[maxN];

ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

bool checkB(int x) {
    if (x == 0) return true;
    bool ans = true;

    int pos = upper_bound(sF + 1, sF + m + 1, sB[x] + S) - sF - 1;
    if (abss(sB[x] - sF[pos]) > S) ans = false;
    if (abss(sB[x + 1] - sF[pos]) > S && x + 1 <= n) ans = false;

    if (ans) {
        is_badB[x] = false;
    } else {
        is_badB[x] = true;

        if (!in_vectB[x]) in_vectB[x] = true, badB.pb(x);
        if (!in_vectF[pos] && pos != 0) in_vectF[pos] = true, badF.pb(pos);
    }

    return ans;
}

bool checkF(int x) {
    if (x == 0) return true;
    bool ans = true;

    int pos = upper_bound(sB + 1, sB + n + 1, sF[x] + S) - sB - 1;
    if (abss(sF[x] - sB[pos]) > S) ans = false;
    if (abss(sF[x + 1] - sB[pos]) > S && x + 1 <= m) ans = false;

    if (ans) {
        is_badF[x] = false;
    } else {
        is_badF[x] = true;

        if (!in_vectF[x]) in_vectF[x] = true, badF.pb(x);
        if (!in_vectB[pos] && pos != 0) in_vectB[pos] = true, badB.pb(pos);
    }

    return ans;
}

bool all_good() {
    while (!badB.empty()) {
        int x = badB.back();
        if (!checkB(x)) break;
        badB.pop_back();
        in_vectB[x] = false;
    }

    while (!badF.empty()) {
        int x = badF.back();
        if (!checkF(x)) break;
        badF.pop_back();
        in_vectF[x] = false;
    }

    return badB.empty() && badF.empty();
}

int main() {
    freopen("bfs2.in", "r", stdin);
    freopen("bfs2.out", "w", stdout);

    cin >> n >> m >> S;
    for (i = 1; i <= n; i++) cin >> B[i], sB[i] = sB[i - 1] + B[i];
    for (i = 1; i <= m; i++) cin >> F[i], sF[i] = sF[i - 1] + F[i];
    cin >> q;
    for (i = 1; i <= q; i++) {
        cin >> tp >> p1 >> p2;
        if (p1 > p2) swap(p1, p2);

        if (tp == 'B') {
            swap(B[p1], B[p2]);
            sB[p1] = sB[p1 - 1] + B[p1];
            checkB(p1 - 1);
            checkB(p1);
        }

        if (tp == 'F') {
            swap(F[p1], F[p2]);
            sF[p1] = sF[p1 - 1] + F[p1];
            checkF(p1 - 1);
            checkF(p1);
        }

        if (all_good())
            cout << "1\n";
        else
            cout << "0\n";
    }


    return 0;
}
