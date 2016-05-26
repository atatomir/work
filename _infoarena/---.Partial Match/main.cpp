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

#define maxN 100011

class SuffixArray {
    public:
        void init(int _n, char *from) {
            n = _n;

            /* compute llog */
            for (llog = 0; (1 << llog) <= n; llog++);
            data = vector< vector<int> >(llog + 1, vector<int>(n + 7, 0));

            /* add initial state */
            for (i = 1; i <= n; i++) data[0][i] = from[i] - 'a';

            /* compute other levels */
            for (i = 1; i < llog; i++) {
                aux.clear();
                sdim = 1 << (i - 1);

                for (j = 1; j <= n; j++) {
                    if (j + sdim <= n)
                        aux.pb({data[i - 1][j], data[i - 1][j + sdim], j});
                    else
                        aux.pb({data[i - 1][j], -1, j});
                }

                sort(aux.begin(), aux.end());
                data[i][ aux[0].id ] = 0;
                for (j = 1; j < (int)aux.size(); j++) {
                    if (aux[j] == aux[j - 1])
                        data[i][ aux[j].id ] = data[i][ aux[j - 1].id ];
                    else
                        data[i][ aux[j].id ] = j;
                }
            }
        }

        int lcp(int p1, int p2) {
            int ans = 0;

            for (i = llog - 1; i >= 0 && p1 <= n && p2 <= n; i--)
                if (data[i][p1] == data[i][p2])
                    ans += (1 << i), p1 += (1 << i), p2 += (1 << i);

            return ans;
        }

    private:
        struct triple {
            int a, b, id;

            bool operator<(const triple& who)const {
                if (a == who.a) return b < who.b;
                return a < who.a;
            }

            bool operator==(const triple& who) {
                return a == who.a && b == who.b;
            }
        };

        int n, llog, i, j, sdim;
        vector< vector<int> > data;
        vector< triple > aux;

};

int n, m, k, i, p1, p2, wild;
char A[maxN], B[maxN];

char sa_data[maxN << 1];
SuffixArray SA;

vector<int> ans;

int main()
{
    freopen("partialmatch.in","r",stdin);
    freopen("partialmatch.out","w",stdout);

    scanf("%s\n%s\n%d", B + 1, A + 1, &k);
    n = strlen(A + 1);
    m = strlen(B + 1);

    memcpy(sa_data + 1, A + 1, n);
    sa_data[n + 1] = '?';
    memcpy(sa_data + n + 1 + 1, B + 1, m);
    SA.init(n + m + 1, sa_data);

    for (i = 1; i + m - 1 <= n; i++) {
        p1 = i;
        p2 = n + 1 + 1;
        wild = k;

        /* kangaroo */
        while (wild >= 0 && p2 <= n + m + 2) {
            int match = SA.lcp(p1, p2);

            p1 += match;
            p2 += match;

            if (p2 == n + m + 2) break;

            p1++; p2++;
            wild--;
        }

        if (wild >= 0 && p2 == n + m + 2) ans.pb(i - 1);
    }

    printf("%d\n", ans.size());
    for (int e : ans) printf("%d\n", e);


    return 0;
}
