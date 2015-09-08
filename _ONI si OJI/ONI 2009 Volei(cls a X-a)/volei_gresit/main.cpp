#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 7
#define P Point

int n,i,xx,yy;
char gender;
double maxDist;
pair<int,int> Point[2][maxN]; //! 0-fete, 1-baieti
int count_[2];

int dp[1 << maxN][1 << maxN];
pair<int,int> prov[1 << maxN][1 << maxN];
bool computed[1 << maxN][1 << maxN];
int goodState_response;

vector< pair<int, int> > allPoints;
int ans;
pair<int, int> ans_states;
vector< pair<int, int> > left_;
pair<int,int> p_1,p_2,ans_p1,ans_p2;

bool goodState(int boys, int girls, vector<int>& g_aux) {
    vector<int> b_aux;

    b_aux.clear();
    g_aux.clear();

    for (int i = 1; i <= n; i++) {
        if ( (boys & (1 << (i-1))) != 0 )
            b_aux.pb(i);
    }
    for (int i = 1; i <= n; i++) {
        if ( (girls & (1 << (i-1))) != 0 )
            g_aux.pb(i);
    }

    if (b_aux.size() > 0) goodState_response = b_aux[0];
    return b_aux.size() == g_aux.size();
}

bool canChange(int boy, int girl) {
    double dist = sqrt( (Point[1][boy].first - Point[0][girl].first) * (Point[1][boy].first - Point[0][girl].first) +
                        (Point[1][boy].second - Point[0][girl].second) * (Point[1][boy].second - Point[0][girl].second) );
    return dist - maxDist <= 1e-11;
}

//! state_boy, state_girl
int compute(int state_1, int state_2) {
    if (computed[state_1][state_2]) return dp[state_1][state_2];
    computed[state_1][state_2] = true;

    vector<int> aux;
    if (!goodState(state_1, state_2, aux)) {
        dp[state_1][state_2] = maxN+1;
        return dp[state_1][state_2];
    }

    int bestBoy = goodState_response;
    dp[state_1][state_2] = maxN+1;

    int ss_1 = state_1 ^= 1 << (bestBoy - 1);
    int ss_2 ;
    for (auto bestGirl : aux) {
        if (!canChange(bestBoy , bestGirl)) continue;

        ss_2 = state_2 ^= 1 << (bestGirl - 1);
        int newCost = compute(ss_1, ss_2) + 1;

        if (newCost < dp[state_1][state_2]) {
            dp[state_1][state_2] = newCost;
            prov[state_1][state_2] = mp(bestBoy,bestGirl);
        }
    }

    return dp[state_1][state_2];
}

int getPosition(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3) {
    long long value = (p1.first * p2.second) - (p1.second * p2.first) +
                      (p2.first * p3.second) - (p2.second * p3.first) +
                      (p3.first * p1.second) - (p3.second * p1.first) ;
    if (value == 0) return 0;
    if (value > 0)  return 1;
    return -1;
}

//! state_boy, state_girl
void TestSolution(int conf_1,int conf_2) {
    if ( compute(conf_1,conf_2) >= ans ) return;
    ans = compute(conf_1,conf_2);
    ans_states = mp(conf_1,conf_2);

    ans_p1 = p_1;
    ans_p2 = p_2;
}

int main()
{
    freopen("volei.in","r",stdin);
    freopen("volei.out","w",stdout);

    scanf("%d%lf",&n,&maxDist);
    for (i = 1; i <= 2 * n; i++) {
        scanf("%d %d %c",&xx,&yy,&gender);
        allPoints.pb(mp(xx, yy));
        if (gender == 'B')
            Point[1][ ++count_[1] ] = mp(xx, yy);
        else
        if (gender == 'F')
            Point[0][ ++count_[0] ] = mp(xx, yy);
        else
            cerr << "Reading error . Alien kid .\n";
    }

    ans = maxN+1;
    for (auto p1 : allPoints) {
        for (auto p2 : allPoints) {
            if (p1 == p2) continue;
            int state_left = 0; //! girls
            int state_right = 0; //! boys
            left_.clear();
            p_1 = p1; p_2 = p2;

            for (i = 1; i <= n; i++) {
                if (getPosition(p1, p2, Point[0][i]) == 1)
                    state_left |= 1 << (i - 1);
                else
                if (getPosition(p1, p2, Point[0][i]) == 0)
                    left_.pb(mp(0,i));
            }

            for (i = 1; i <= n; i++) {
                if (getPosition(p1, p2, Point[1][i]) == -1)
                    state_right |= 1 << (i - 1);
                else
                if (getPosition(p1, p2, Point[1][i]) == 0)
                    left_.pb(mp(1,i));
            }

            //!-----------------------------------------

            for (int how = 0; how < 4; how++) {
                int ss_left = state_left;
                int ss_right = state_right;

                if (how & 1) {
                    if (left_[0].first == 0)
                        ss_left |= 1 << (left_[0].second - 1);
                    else
                        ss_right |= 1 << (left_[0].second - 1);
                }

                if (how & 2) {
                    if (left_[1].first == 0)
                        ss_left |= 1 << (left_[1].second - 1);
                    else
                        ss_right |= 1 << (left_[1].second - 1);
                }

                TestSolution(ss_right,ss_left);
            }
        }
    }

    if (ans >= maxN)
        cerr << "Solution not found.. " << ans << "\n";

    printf("%d\n",ans);
    if (ans >= maxN) return 0;

    pair<int,int> now = ans_states;
    for (i = 1; i <= ans; i++) {
        auto pp = prov[now.first][now.second];
        printf("%d %d %d %d\n", P[1][pp.first].first, P[1][pp.first].second ,
                                P[0][pp.second].first, P[0][pp.second].second);

        now.first ^= 1 << (pp.first - 1);
        now.second ^= 1 << (pp.second -1);
    }

    cerr << "Point one : " << ans_p1.first << ' ' << ans_p1.second << '\n';
    cerr << "Point one : " << ans_p2.first << ' ' << ans_p2.second << '\n';

    return 0;
}
