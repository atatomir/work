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

struct upd {
    int pos;
    char a, b;
};

char s[maxN];
int n, i, j, m;
upd Q[maxN];

void execute(int pos, char c1, char c2) {
    char C1 = c1 + 'A' - 'a';
    char C2 = c2 + 'A' - 'a';

    for (int i = pos; i < m; i++) {
        if (s[i] == c1) s[i] = c2;
        else
        if (s[i] == c2) s[i] = c1;

        if (s[i] == C1) s[i] = C2;
        else
        if (s[i] == C2) s[i] = C1;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%[^\n]%d", s, &n);
    m = strlen(s);
    for (i = 1; i <= n; i++)
        scanf("%d %c %c", &Q[i].pos, &Q[i].a, &Q[i].b);

    for (i = n; i >= 1; i--)
        execute(Q[i].pos, Q[i].a, Q[i].b);

    for (i = 0; i < m; i++) printf("%c", s[i]);

    return 0;
}
