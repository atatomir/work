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
#define ll long long

#define maxN 100011

int defX[3] = {-1, 0, +1};
int defY[3] = {+1, +1, +1};

int n, i, j, xx, yy, posx, posy;
char s[12][maxN];

int dist[12][maxN], pr[12][maxN];
queue< pair<int, int> > Q;

vector<int> sol;
vector< pair<int, int> > ans;


int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n", &n);
    for (i = 1; i <= 10; i++) scanf("%s\n", s[i] + 1);
    for (i = 0; i <= n + 1; i++) s[0][i] = s[11][i] = 'X';
    for (i = 0; i <= 11; i++) s[i][0] = s[n + 1][i] = 'X';

    dist[10][1] = 1;
    Q.push(mp(10, 1));

    while (!Q.empty()) {
        auto act = Q.front(); Q.pop();
        if (act.second == n) {
            posx = act.first;
            posy = n;
            break;
        }

        for (i = 0; i < 3; i++) {
            if (i == 1 && act.first > 1 && act.first < 10) continue;

            xx = act.first + defX[i];
            yy = act.second + defY[i];

            if (dist[xx][yy] == 0 && s[xx][yy] == '.') {
                dist[xx][yy] = dist[act.first][act.second] + 1;
                pr[xx][yy] = i;
                Q.push(mp(xx, yy));
            }
        }
    }

    if (posx == 0){
        cerr << "error";
        printf("0");
        return 0;
    }

    while (posy != 1) {
        i = pr[posx][posy];

        posx -= defX[i];
        posy -= defY[i];

        if (i == 0 || (i == 1 && posx == 1))
            sol.pb(1);
        else
            sol.pb(0);
    }

    reverse(sol.begin(), sol.end());

    for (i = 0; i < sol.size(); i++) {
        if (sol[i] == 0) continue;

        for (j = i; j < sol.size(); j++)
            if (sol[j] == 0)
                break;

        ans.pb(mp(i, j - i));
        i = j - 1;
    }

    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d %d\n", e.first, e.second);


    return 0;
}
