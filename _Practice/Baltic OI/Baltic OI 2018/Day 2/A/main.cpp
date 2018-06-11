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

const int maxN = 100011;

struct interv {
    int l, r, id;

    bool operator<(const interv& who)const {
        return l < who.l;
    }
};

int n, m, i;
interv data[maxN];
vector<interv> here[maxN], ord;
int cnt[maxN], sum[maxN];

bool sol[maxN], used[maxN];
bool done1[maxN], done2[maxN];

vector<int> at_start;


void no_sol() {
    printf("impossible");
    exit(0);
}

void subtask(int d1 = 0, int d2 = 0, int t1 = n, int t2 = n, int p1 = 0, int p2 = 0) {
    int i, j;

    for (i = 1; i <= m; i++) sol[i] = false;

    for (i = 1; i <= n; i++) {
        for (auto e : here[i]) {
            if (e.r < e.l) e.r = n;

            if (e.id == d1) {
                sol[e.id] = true;
                if (p1 + 1 < e.l) return;
                p1 = max(p1, e.r);
                continue;
            }

            if (e.id == d2) {
                if (p2 + 1 < e.l) return;
                p2 = max(p2, e.r);
                continue;
            }

            if ((p1 < p2 && p1 < t1) || (p2 >= t2)) {
                sol[e.id] = true;
                if (p1 + 1 < e.l) return;
                p1 = max(p1, e.r);
            } else {
                if (p2 + 1 < e.l) return;
                p2 = max(p2, e.r);
            }
        }
    }

    if (p1 < t1 || p2 < t2) no_sol();

    sol[d1] = true;
    for (i = 1; i <= m; i++) printf("%d", (sol[i] ? 1 : 0));
    exit(0);

}

int fnd(int pos) {
    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        if (data[i].l <= pos && pos <= data[i].r) return i;
        if (data[i].l <= pos && data[i].l > data[i].r) return i;
        if (pos <= data[i].r && data[i].l > data[i].r) return i;
    }

    return 0;
}

int set1(int id) {
    used[id] = true;
    int i;

    sol[id] = true;
    if (data[id].l <= data[id].r) {
        for (i = data[id].l; i <= data[id].r; i++) done1[i] = true, cnt[i]--;
    } else {
        for (i = data[id].l; i <= n; i++) done1[i] = true, cnt[i]--;
        for (i = 1; i <= data[id].r; i++) done1[i] = true, cnt[i]--;
    }
}

int set2(int id) {
    used[id] = true;
    int i;

    if (data[id].l <= data[id].r) {
        for (i = data[id].l; i <= data[id].r; i++) done2[i] = true, cnt[i]--;
    } else {
        for (i = data[id].l; i <= n; i++) done2[i] = true, cnt[i]--;
        for (i = 1; i <= data[id].r; i++) done2[i] = true, cnt[i]--;
    }
}

void small() {
    int i;

    bool any = true;
    while (any) {
        any = false;

        for (i = 1; i <= n; i++) {
            if (cnt[i] >= 2) continue;
            if (cnt[i] == 0) continue;

            if (done1[i] == false || done2[i] == false) {
                any = true;
                int id = fnd(i);

                if (done1[i] == false) {
                    set1(id);
                } else {
                    set2(id);
                }

                break;
            }
        }

        if (any) continue;

        for (i = 1; i <= n; i++) {
            if (cnt[i] >= 2) continue;
            if (cnt[i] == 0) continue;

            any = true;
            int id = fnd(i);

            if (done1[i] == false) {
                set1(id);
            } else {
                set2(id);
            }

            break;
        }

        if (any) continue;

        for (i = 1; i <= n; i++) {
            if (cnt[i] == 0) continue;

            any = true;
            int id = fnd(i);

            if (done1[i] == false) {
                set1(id);
            } else {
                set2(id);
            }

            break;
        }

    }

    for (i = 1; i <= n; i++)
        if (done1[i] == false)
            break;

    if (i <= n) no_sol();

    for (i = 1; i <= n; i++)
        if (done2[i] == false)
            break;

    if (i <= n) no_sol();

    for (i = 1; i <= m; i++)
        printf("%d", (sol[i] ? 1 : 0));
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &data[i].l, &data[i].r);
        data[i].id = i;
        here[data[i].l].pb(data[i]);
        ord.pb(data[i]);

        if (data[i].l <= data[i].r) {
            cnt[data[i].l]++;
            cnt[data[i].r + 1]--;
        } else {
            cnt[data[i].l]++;
            cnt[n + 1]--;

            cnt[1]++;
            cnt[data[i].r + 1]--;
        }
    }

    for (i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
        if (cnt[i] <= 1) no_sol();

        sum[i] = sum[i - 1];
        if (cnt[i] == 2) sum[i]++;
    }

    for (i = 1; i <= m; i++) {
        if (data[i].l > data[i].r || data[i].l == 1) at_start.pb(i);
    }

    if (n <= 1000) {
        small();
        return 0;
    }

    sort(ord.begin(), ord.end());

    for (i = 1; i < at_start.size(); i++) {
        int d1 = at_start[0];
        int d2 = at_start[i];
        int t1 = (data[d1].l == 1 ? n : data[d1].l - 1);
        int t2 = (data[d2].l == 1 ? n : data[d2].l - 1);
        int p1 = data[d1].r;
        int p2 = data[d2].r;

        subtask(d1, d2, t1, t2, p1, p2);
    }

    no_sol();


    return 0;
}
