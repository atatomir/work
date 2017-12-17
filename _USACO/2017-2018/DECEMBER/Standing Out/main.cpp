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

#define piii pair< pair<int, int>, int >
#define maxN 200111

class SuffixArray {
    public:
        void init(int *_s, int _n) {
            int i, j;

            s = _s;
            n = _n;

            max_log = 0;
            while ( (1 << max_log) < n ) max_log++;

            data = vector< vector<int> >(max_log + 3, vector<int>(n + 3));
            for (i = 1; i <= n; i++)
                data[0][i] = s[i];

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
        int *s;
        vector< vector<int> > data;
        vector<piii> aux;
        vector<int> order;
};

int n, i, j, k, pos, act;
string s;
int data[maxN], sz[maxN];
int prov[maxN], aux[maxN];
SuffixArray SA;
vector<int> ord;
ll ans[maxN];


int main()
{
    freopen("standingout.in","r",stdin);
    freopen("standingout.out","w",stdout);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> s; act = 0;
        for (auto e : s) {
            data[++pos] = e - 'a' + 1;
            prov[pos] = i;
            sz[pos] = s.size() - act;
            act++;
        }
        data[++pos] = 100 + i;
    }

    SA.init(data, pos);
    ord = SA.get_order();

    for (i = 0; i < ord.size(); i = j) {
        for (j = i; j < ord.size(); j++)
            if (prov[ord[i]] != prov[ord[j]])
                break;

        if (i != 0) {
            for (k = i; k < j; k++)
                aux[k] = SA.lcp(ord[i - 1], ord[k]);
        }

        if (j < ord.size()) {
            for (k = i; k < j; k++)
                aux[k] = max(aux[k], SA.lcp(ord[j], ord[k]));
        }

        for (k = i + 1; k < j; k++)
            aux[k] = max(aux[k], SA.lcp(ord[k - 1], ord[k]));

        for (k = i; k < j; k++) {
            ans[prov[ord[k]]] += sz[ord[k]] - aux[k];
        }
    }

    for (i = 1; i <= n; i++)
        cout << ans[i] << '\n';

    return 0;
}
