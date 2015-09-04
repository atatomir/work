#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 211
#define maxK 7
#define mod 30103
#define maxStates 300011

int n,k,i;
vector< vector<int> > States;
map< vector<int>, int> M;
vector<int> list[maxStates];
vector<int> aux;
int dp[2][maxStates];
int dp_s,dp_d;

int cnt;

void perm(int pas) {
    if (pas == k) {
        int limit = 1 << (k+1);
        vector<int> addNow;
        for (int conf = 0; conf < limit; conf++) {
            addNow.clear();
            for (int bit = 0; bit < k; bit++) {
                if ( (conf & (1 << bit)) != 0 ) addNow.pb(0);
                addNow.pb(aux[bit]);
            }
            if ( (conf & (1 << k)) != 0 ) addNow.pb(0);

            States.pb( addNow );
            M[addNow] = States.size()-1;
        }

        return;
    }

    int used = 0;
    for (auto auxi:aux) used |= 1 << auxi;
    for (int i = 1; i <= k; i++) {
        if ( (used & (1 << i)) != 0 ) continue;
        aux.push_back(i);
        perm(pas+1);
        aux.pop_back();
    }
}

bool Test(vector<int>& conf,int pos) {
    bool ok = true;

    if (pos != 0) ok &= conf[pos-1] != 0;
    if (pos != conf.size()) ok &= conf[pos] != 0;

    return ok;
}

void make_graph() {
    int i,j;

    for (i = 0; i < States.size(); i++) {
        vector<int> actState = States[i];

        for (j = 0; j <= actState.size();j++) {
            vector<int> now = actState;

            if (!Test(now,j)) continue;

            auto it = now.begin();
            for (int vv = j; vv > 0; vv--) it++;
            now.insert(it,k+1);

            for (int vv = 0; vv < now.size(); vv++)
                if (now[vv] != 0) now[vv]--;

            now.resize( unique(now.begin(),now.end()) - now.begin() );
            list[i].pb( M[now] );
        }

    }
}

int main()
{
    freopen("cabane.in","r",stdin);
    freopen("cabane.out","w",stdout);

    scanf("%d%d",&n,&k);

    for (i = 1; i <= k; i++) {
        aux.clear();
        aux.push_back(i);
        perm(1);
    }

    cerr << "There are " << States.size() << " states.\n";
    int expected = 1 << (k+1);
    for (i = 2; i <= k; i++) expected *= i;
    if (expected != States.size()) cerr << "Error : " << States.size() << "/" << expected;

    make_graph();

    dp_s = 0; dp_d = 1;
    for (i = 0; i < States.size(); i++) {
        if (States[i].size() != k)
            dp[dp_s][i] = 0;
        else
            dp[dp_s][i] = 1;
    }

    for (int pas = k+1; pas <= n; pas++) {
        memset(dp[dp_d],0,sizeof(dp[dp_d]));

        for (i = 0; i < States.size(); i++) {
            for (auto neigh : list[ i ]) {
                dp[dp_d][neigh] += dp[dp_s][i];
                if (dp[dp_d][neigh] >= mod) dp[dp_d][neigh] -= mod;
            }
        }

        swap(dp_s, dp_d);
    }

    int ans = 0;
    for (i = 0; i < States.size(); i++) {
        ans += dp[dp_s][i];
        if (ans >= mod) ans -= mod;
    }

    printf("%d",ans);
    cerr << "The answer is " << ans << '\n';

    return 0;
}

