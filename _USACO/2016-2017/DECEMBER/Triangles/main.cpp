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

#define maxN 333
const int dim = 1000005;

int n, i, j, k, cnt;
pair<ll, ll> P[maxN];
vector<int> aux;

int pre[maxN][maxN];
int aib[dim + 11];
int ans[maxN];




int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int v) {
    while (pos <= dim) {
        aib[pos] += v;
        pos += zrs(pos);
    }
}

int sum(int x) {
    int ans = 0;

    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }

    return ans;
}


void solve(int F) {
    int i;
    pair<ll, ll> A, B;

    sort(aux.begin(), aux.end(), [&](int a, int b)->bool const {
        A = P[a];
        B = P[b];

        A.first -= P[F].first;
        A.second -= P[F].second;

        B.first -= P[F].first;
        B.second -= P[F].second;

        return A.second * B.first < A.first * B.second;
    });

    for (auto e : aux) {
        pre[F][e] = sum(P[e].first - 1);
        pre[e][F] = pre[F][e];

        add(P[e].first, +1);
    }

    for (auto e : aux)
        add(P[e].first, -1);
}

inline ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

ll det(const pair<ll, ll> A, pair<ll, ll> B, pair<ll, ll> C) {
    B.first -= A.first;
    B.second -= A.second;

    C.first -= A.first;
    C.second -= A.second;

    return B.first * C.second - B.second * C.first;
}

bool in_triangle(int a, int b, int c, int d) {
    return abss(det(P[a], P[b], P[d])) + abss(det(P[b], P[c], P[d])) + abss(det(P[c], P[a], P[d])) == abss(det(P[a], P[b], P[c]));
}

int main()
{
    freopen("triangles.in","r",stdin);
    freopen("triangles.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &P[i].first, &P[i].second);
        P[i].first += 1;
        P[i].second += 1;
    }
    sort(P + 1, P + n + 1);

    for (i = 1; i <= n; i++) {
        aux.clear();

        for (j = i + 1; j <= n; j++)
            if (P[i].first != P[j].first)
                aux.pb(j);

        solve(i);
    }

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            for (k = j + 1; k <= n; k++) {

                if (P[i].first == P[j].first) {
                    ans[ -pre[i][k] + pre[j][k] ]++;
                    continue;
                }

                if (P[j].first == P[k].first) {
                    ans[ pre[i][k] - pre[i][j] ]++;
                    continue;
                }

                if (det(P[i], P[j], P[k]) > 0) {
                    cnt = -pre[i][j] - pre[j][k] + pre[i][k] - 1;
                    if (P[j - 1].first == P[j].first) cnt--;
                    ans[cnt]++;
                } else {
                    cnt = pre[i][j] + pre[j][k] - pre[i][k];
                    if (P[j - 1].first == P[j].first)
                        cnt++;
                    ans[cnt]++;
                }

            }
        }
    }

    for (i = 0; i <= n - 3; i++)
        printf("%d\n", ans[i]);


    return 0;
}
