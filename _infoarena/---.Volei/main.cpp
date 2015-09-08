#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 15

int n,i,xx,yy;
double distLimit;
char gender;
int state;

vector< pair<int,int> > Point;
vector<int> list[1 << maxN];
bool isDestination[1 << maxN];
int prov[1 << maxN];
int dist[1 << maxN];

queue<int> Q;
vector< pair<int, int> > solution;

bool canChange(int boy, int girl) {
    double dist = sqrt( (Point[boy].first - Point[girl].first) * (Point[boy].first - Point[girl].first) +
                        (Point[boy].second - Point[girl].second) * (Point[boy].second - Point[girl].second) );
    return dist - distLimit <= 1e-11;
}
int getPosition(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3) {
    long long value = (p1.first * p2.second) - (p1.second * p2.first) +
                      (p2.first * p3.second) - (p2.second * p3.first) +
                      (p3.first * p1.second) - (p3.second * p1.first) ;
    if (value == 0) return 0;
    if (value > 0)  return 1;
    return -1;
}

pair<int, int> getDifferences(int conf_1,int conf_2) {
    int v1 = -1;
    int v2 = -1;

    for (int i = 0; i < n; i++) {
        if ( ((conf_1 & (1 << i)) > 0) ^ ((conf_2 & (1 << i)) > 0) == 1){
            if (v1 == -1)
                v1 = i;
            else
                v2 = i;
        }
    }

    return mp(v1, v2);
}

int main()
{
    freopen("volei.in","r",stdin);
    freopen("volei.out","w",stdout);

    scanf("%d%lf",&n,&distLimit);
    n <<= 1;
    for (i = 0; i < n; i++) {
        scanf("%d %d %c\n",&xx,&yy,&gender);
        Point.pb( mp(xx, yy) );
        if (gender == 'B') state |= 1 << i;
    }

    int limit = 1 << n;
    vector<int> girls;
    vector<int> boys;
    for (int conf = 1; conf < limit; conf++) {
        girls.clear();
        boys.clear();

        for (i = 0; i < n; i++) {
            if (conf & (1 << i))
                boys.pb(i);
            else
                girls.pb(i);
        }

        if (boys.size() != girls.size()) continue;
        for (int b_ind = 0; b_ind < boys.size(); b_ind++) {
            int b_bit = boys[ b_ind ];
            for (int g_ind = 0; g_ind < girls.size(); g_ind++) {
                int g_bit = girls[ g_ind ];

                if (!canChange(b_bit, g_bit)) continue;
                list[conf].pb(conf ^ (1 << b_bit) ^ (1 << g_bit));
            }
        }
    }

    vector<int> onLine;
    for (auto p1 : Point) {
        for (auto p2 : Point) {
            if (p1 == p2) continue;
            onLine.clear();
            int actState = 0;
            int how = 0;

            for (i = 0; i < n; i++) {
                if (getPosition(p1, p2, Point[i]) == 1)
                    actState |= 1 << i, how++;
                if (getPosition(p1, p2, Point[i]) == 0)
                    onLine.pb(i);
            }

            if (2 * how == n) isDestination[actState] = true;

            actState ^= 1 << onLine[0]; how++;
            if (2 * how == n) isDestination[actState] = true;

            actState ^= 1 << onLine[1]; how++;
            if (2 * how == n) isDestination[actState] = true;

            actState ^= 1 << onLine[0]; how--;
            if (2 * how == n) isDestination[actState] = true;

        }
    }

    prov[state] = state;
    Q.push(state);
    int ans = 0;

    while(!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (isDestination[node]) {
            ans = node;
            break;
        }

        for (auto wh : list[node]) {
            if (prov[wh] != 0) continue;

            prov[wh] = node;
            Q.push(wh);
            dist[wh] = dist[node] + 1;
        }
    }

    if (ans == 0) {
        cerr << "No solution ...";
        printf("No solution...");
        return 0;
    }

    printf("%d\n",dist[ans]);
    while (prov[ans] != ans) {
        solution.pb( getDifferences(prov[ans], ans) );
        ans = prov[ans];
    }
    for (i = solution.size() - 1; i >= 0; i--) {
        auto aux = solution[i];
        printf("%d %d " ,Point[aux.first].first,Point[aux.first].second);
        printf("%d %d\n",Point[aux.second].first,Point[aux.second].second);
    }


    return 0;
}
