#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111
#define maxK 35
#define INF 1000000000000000000.00

int n,k,i,j,aux;
double Limit;
double height[maxN];
double pos[maxN];
vector< pair<double,double> > tmp;

double dist[maxN][maxN];
double dp[maxK][maxN]; //! cate cabine, pozitia in dinamica
int prov[maxK][maxN];

vector<int> wh;

int main()
{
    freopen("munte2.in","r",stdin);
    freopen("munte2.out","w",stdout);

    scanf("%d%d%lf",&n,&k,&Limit);
    for (i = 1; i <= n; i++) {
        scanf("%lf %lf",&pos[i],&height[i]);
        tmp.pb(mp(pos[i],height[i]));
    }
    sort(tmp.begin(),tmp.end());
    for (i = 0; i < n; i++) {
        pos[i+1] = tmp[i].first;
        height[i+1] = tmp[i].second;
    }

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            dist[i][j] = sqrt( (height[i] - height[j]) * (height[i] - height[j]) +
                               (pos[i] - pos[j]) * (pos[i] - pos[j])             );

            double a = (height[j]-height[i]) / (pos[j]-pos[i]);
            double b = height[i] - a * pos[i];

            bool ok = true;
            for (aux = i + 1; aux < j; aux++){
                double actHeight = a * pos[aux] + b;
                if (actHeight <= height[aux]) {
                    ok = false;
                    break;
                }
            }

            if (!ok) dist[i][j] = INF;
        }
    }

    dp[1][1] = 0.00;
    for (i = 2; i <= n; i++) dp[1][i] = INF;

    for (int cabs = 2; cabs <= k; cabs++) {
        for (i = cabs; i <= n; i++) {
            dp[cabs][i] = INF;
            prov[cabs][i] = -1;

            for (aux = cabs-1; aux < i; aux++) {
                double act = dp[cabs-1][aux] + dist[aux][i];
                if (act < dp[cabs][i]) {
                    dp[cabs][i] = act;
                    prov[cabs][i] = aux;
                }
            }
        }
    }

    cerr << setprecision(4) << "The answer is ... " << dp[k][n];
    int answer = dp[k][n];
    dp[k][n] -= answer;
    if (dp[k][n] > 0.49999) answer++;
    cerr << "\nRounded : " << answer << '\n';

    int pos = n;
    wh.pb(pos);

    aux = k;
    while (pos != 1) {
        pos = prov[aux--][pos];
        wh.pb(pos);
    }

    printf("%d\n",answer);
    for (i = wh.size()-1; i >= 0; i--) printf("%d ",wh[i]);


    return 0;
}
