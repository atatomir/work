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
 

int main()
{
    freopen("*.in","r",stdin);
    freopen("*.out","w",stdout);




    return 0;
}
