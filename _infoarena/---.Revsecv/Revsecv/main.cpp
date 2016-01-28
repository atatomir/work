#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define piii pair< pair<int, int>, int >

class SuffixArray {
    public:
        void init(char *_s, int _n) {
            int i, j;

            s = _s;
            n = _n;

            max_log = 0;
            while ( (1 << max_log) < n ) max_log++;

            data = vector< vector<int> >(max_log + 3, vector<int>(n + 3));
            for (i = 1; i <= n; i++)
                data[0][i] = s[i] - 'a';

            for (i = 1; i <= max_log; i++) {
                aux.clear();
                int dim = 1 << (i - 1);

                for (j = 1; j <= n; j++) {
                    if (j + dim > n)
                        aux.pb(mp(mp(data[i - 1][j], -1), j));
                    else
                        aux.pb(mp(mp(data[i - 1][j], data[i - 1][j + dim]), j));
                }

                sort(aux.begin(), aux.end());
                data[i][ aux[0].second ] = 0;
                for (j = 1; j < aux.size(); j++) {
                    if (aux[j - 1].first == aux[j].first)
                        data[i][ aux[j].second ] = data[i][ aux[j - 1].second ];
                    else
                        data[i][ aux[j].second ] = data[i][ aux[j - 1].second ] + 1;
                }

                if (i == max_log) {
                    order.clear();
                    for (auto e : aux)
                        order.pb(e.second);
                }
            }
        }

        int lcp(int x, int y) {
            int ans = 0;

            for (int i = max_log; i >= 0; i--)
                if (x + ans <= n && y + ans <= n)
                    if (data[i][x + ans] == data[i][y + ans])
                        ans += (1 << i);

            return ans;
        }

        vector<int> get_order() {
            return order;
        }

    private:
        int n, max_log;
        char *s;
        vector< vector<int> > data;
        vector<piii> aux;
        vector<int> order;
};

//! -----------------------------------------

#define maxN 200011

int n, i;
char s[maxN];
SuffixArray work;
vector<int> order;

int dim;
int lcps[maxN];
int _left[maxN];
int _right[maxN];
int how_left[maxN];
int how_right[maxN];

stack< pair<int, int> > S;
map< pair<int, int>, bool > M;

char pal[maxN];
int dp[maxN];

ll ans;

//! ------------------------------------------

void compute_left() {
    int i;

    while (!S.empty()) S.pop();
    S.push(mp(0, lcps[0]));

    for (i = 1; i < dim; i++) {
        while (S.top().second >= lcps[i]) S.pop();
        _left[i] = S.top().first;
        S.push(mp(i, lcps[i]));
    }
}

void compute_right() {
    int i;

    while (!S.empty()) S.pop();
    S.push(mp(dim, lcps[dim]));

    for (i = dim - 1; i > 0; i--) {
        while (S.top().second >= lcps[i]) S.pop();
        _right[i] = S.top().first;
        S.push(mp(i, lcps[i]));
    }
}

int how_many_left(int x, int y) {
    return how_left[y] - how_left[x - 1];
}

int how_many_right(int x, int y) {
    return how_right[y] - how_right[x - 1];
}

void remove_palind() {
    int i;

    dim = 0;

    pal[++dim] = '@';
    for (i = 1; i <= n; i++) {
        pal[++dim] = s[i];
        pal[++dim] = '.';
    }

    pal[dim] = '#';

    //! -------- Manacher -------------
    int C = 0;
    int last = 0;

    for (i = 1; i <= dim; i++) {
        if (i <= last)
            dp[i] = min(dp[2 * C - i], last - i + 1);
        else
            dp[i] = 1;

        while (pal[ i + dp[i] ] == pal[i - dp[i]]) dp[i]++;

        if (i + dp[i] - 1 > last) {
            last = i + dp[i] - 1;
            C = i;
        }
    }

    for (i = 2; i < dim; i++) {
        if (i & 1) { //! palindrom par
            int aux = dp[i] / 2;
            ans -= 1LL * aux * aux;
        } else { //! palindrom impar
            int aux = (dp[i] + 1) / 2;
            ans -= 1LL * aux * aux;
        }
    }
}

int main()
{
    freopen("revsecv.in","r",stdin);
    freopen("revsecv.out","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);
    s[n + 1] = '@';
    for (i = 1; i <= n; i++)
        s[2 * n + 1 - i + 1] = s[i];

    work.init(s, 2 * n + 1);
    order = work.get_order();

    dim = 2 * n + 1;
    for (i = 1; i < order.size(); i++)
        lcps[i] = work.lcp( order[i - 1], order[i] );
    lcps[0] = lcps[dim] = -1;

    compute_left();
    compute_right();

    for (i = 1; i <= dim; i++) {
        how_left[i] = how_left[i - 1] + (order[i - 1] <= n);
        how_right[i] = how_right[i - 1] + (order[i - 1] > n + 1);
    }

    M.clear();
    for (i = 1; i < dim; i++) {
        int now_left = _left[i];
        int now_right = _right[i];

        if (M[mp(now_left, now_right)] == true) continue;
        M[mp(now_left, now_right)] = true;

        int part_one = how_many_left(now_left + 1, now_right);
        int part_two = how_many_right(now_left + 1, now_right);
        int now_lcp = lcps[i];
        int lim_lcp = max(lcps[now_left], lcps[now_right]);
        lim_lcp = max(lim_lcp, 0);

        ans += 1LL * part_one * part_two * (now_lcp - lim_lcp);
    }

    remove_palind();

    printf("%lld", ans / 2);

    return 0;
}
