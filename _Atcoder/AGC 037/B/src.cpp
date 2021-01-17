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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 300011;
const ll mod = 998244353;

int n;
char s[maxN];
vector<int> R, G, B;
int tp[maxN];
int cnt[10];
ll answer;

int main()
{
    freopen("test.in","r",stdin);

    answer = 1;
    scanf("%d\n%s", &n, s);
    for (int i = 0; i < n * 3; i++) {
        if (s[i] == 'R')
            R.pb(i);
        if (s[i] == 'G')
            G.pb(i);
        if (s[i] == 'B')
            B.pb(i);
    }

    for (int i = 0; i < n; i++) {
        tp[min(R[i], min(G[i], B[i]))] = 1;
        tp[max(R[i], max(G[i], B[i]))] = 2;
    }

    cnt[0] = n;
    for (int i = 0; i < n * 3; i++) {
        if (tp[i] == 1) {
            answer = (answer * cnt[0]) % mod;
            cnt[0]--; cnt[1]++;
        } 

        if (tp[i] == 0) {
            answer = (answer * cnt[1]) % mod;
            cnt[1]--; cnt[2]++;
        }

        if (tp[i] == 2) {
            answer = (answer * cnt[2]) % mod;
            cnt[2]--; cnt[3]++;
        }
    }

    cout << answer;


    return 0;
}
