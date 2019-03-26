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

const int maxN = 288;

int n, k, i, j;
int v[maxN];

int sol[maxN];
bool found[maxN];

int main()
{
    freopen("sir42.in","r",stdin);
    freopen("sir42.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        if (v[i] != -1) v[i]++;
    }

    if (v[1] == -1) {
        for (i = 1; i <= n; i++)
            printf("0");
        return 0;
    }
     
    for (i = 1; i < n; i++) {
        if (v[i + 1] == -1) {
            found[i] = true;
            sol[i] = 1;
            for (j = v[i]; j <= n; j++) found[j] = true;
            sol[v[i]] = 1;

            break;
        }

        if (v[i] == v[i + 1]) {
            found[i] = true;
            sol[i] = 0;
        } else {
            found[i] = true;
            sol[i] = 1;
        }

        for (j = v[i]; j <= v[i + 1]; j++)
            found[j] = true;
        sol[v[i]] = sol[v[i + 1]] = true;
    }

    for (i = 1; i <= n && v[i] != -1; i++) {
        int need = k;

        for (j = i; j <= v[i]; j++)
            if (found[j])
                if (sol[j])
                    need--;


        for (j = i; j <= v[i] && need > 0; j++) {
            if (found[j]) {
                //! nothing
            } else {
                found[j] = true;
                sol[j] = 1;
                need--;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        if (v[i] == -1) continue;
        
        int act = 0;
        for (j = i; j <= v[i]; j++)
            act += sol[j];

        if (act != k)
            cerr << i << ' ' << act << '\n';
    }

    for (i = 1; i <= n; i++)
        printf("%d", sol[i]);


    return 0;
}
