#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 200011
#define piii pair< pair<int, int>, int >
#define ll long long

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
            }
        }

        int lcp(int x, int y) {
            int ans = 0;

            for (int i = max_log; i >= 0; i--)
                if (data[i][x + ans] == data[i][y + ans])
                    ans += (1 << i);

            return ans;
        }

    private:
        int n, max_log;
        char *s;
        vector< vector<int> > data;
        vector<piii> aux;
};

//! --------------------------------------

int n, i, j;
char s[maxN];
SuffixArray work;
ll ans;

void play(int i , int j) {
    for (; i < j; i++, j--) {
            while (s[i] != s[j] && i + 1 < j - 1) {
                i++;
                j--;
                continue;
            }

            ll now = min(work.lcp(i, 2 * n + 2 - j), (j - i + 1) / 2);
            ans += (now * (now + 1)) / 2;
            j -= now;
            i += now;

    }
}

int main()
{
    freopen("revsecv.in","r",stdin);
    freopen("revsecv.out","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    s[n + 1] = '#';
    for (i = 1; i <= n; i++)
        s[2 * n + 2 - i] = s[i];

    work.init(s, 2 * n + 1);

    for (i = 2; i <= n; i++)
        play(1, i);
    for (i = 2; i <= n; i++)
        play(i, n);

    printf("%lld", ans);

    return 0;
}
