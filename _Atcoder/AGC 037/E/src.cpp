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

const int maxN = 10011;

ll n, k, cnt, act;
char s[maxN], best;
string answer;

void fullOf(char c) {
    for (int i = 1; i <= n; i++)
        printf("%c", c);
    exit(0);
}

void check(int l, int r) {
    ll mini = cnt * (1LL << (k - 1));
    ll rem = n - mini;

    string aux = "";
    for (int i = 1; i <= mini; i++) aux.pb(best);
    for (int i = 0; i < rem; i++) aux.pb(s[r - cnt - i]);
    if (aux < answer) answer = aux;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld\n%s", &n, &k, s + 1);
    best = s[1];
    for (int i = 1; i <= n; i++) { 
        s[2 * n - i + 1] = s[i];
        best = min(best, s[i]);
        answer.pb('z');
    }

    for (int i = 1; i <= 2 * n; i++) {
        if (s[i] == best) 
            cnt = max(cnt, ++act);
        else
            act = 0;
    }

    ll aux = cnt;
    for (int i = 1; i < k; i++) {
        aux <<= 1;
        if (aux >= n) fullOf(best);
    }

    act = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (s[i] == best)
            act++;
        else
            act = 0;

        if (act == cnt && i >= n)
            check(i - n + 1, i);
    }

    cout << answer;

    return 0;
}
