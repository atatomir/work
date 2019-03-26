#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

const double eps = 1e-7;
const int maxN = 100011;

int n, p, i, j, need;
pair<int, int> P[maxN]; 
vector< pair<int, int> > aux;

void possib() {
    printf("possible");
    exit(0);
}


int gcd(int x, int y) {
    if (x < y) swap(x, y);
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

pair<int, int> modif(int y, int x) {
    if (y < 0) {
        y = -y;
        x = -x;
    }

    int d = gcd(y, abs(x));
    return mp(y / d, x / d);
}

void check(int node) {
    int i;
    aux.clear();

    for (i = 1; i <= n; i++)
        if (P[i].first != P[node].first)
            aux.pb(modif(P[i].second - P[node].second, P[i].first - P[node].first));

    sort(aux.begin(), aux.end());
    for (i = 0; i + need - 2 < aux.size(); i++)
        if (aux[i] == aux[i + need - 2])
            possib();
}

int rand15 () {
    return rand() & 32767;
}

int rand30() {
    return (rand15() << 15) | rand15();
}

int main()
{
    //freopen("test.in","r",stdin);
    srand(time(NULL));

    scanf("%d%d", &n, &p);
    need = (n * p + 99) / 100;

    if (need == 1) possib();

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);
    }


    sort(P + 1, P + n + 1);
    for (i = 1; i + need - 1 <= n; i++)
        if (P[i].first == P[i + need - 1].first)
            possib();

    random_shuffle(P + 1, P + n + 1);

    for (int step = 50; step > 0; step--)  {
        int node = (rand30() % n) + 1;
        check(node);
    }

    printf("impossible");

    return 0;
}
