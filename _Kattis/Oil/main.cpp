#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2016
#define eps 1e-12

double PI = acos(-1);

struct Oil{
    int x1, x2, y;  
};

int n, i, xx1, xx2, yy;
Oil o[maxN];
int ans;

vector< pair<double, int> > work;

int solve(int x, int y) {
    int i, dim;
    int act = 0;
    int ans;
    
    work.clear();
    for (i = 1; i <= n; i++) {
        if (o[i].y == y) continue;
         
        dim = o[i].x2 - o[i].x1;
        double ang1 = atan2(1.00 * (o[i].y - y) , (1.00 * (o[i].x1 - x)));
        double ang2 = atan2(1.00 * (o[i].y - y) , (1.00 * (o[i].x2 - x)));
        
        //cerr << i << ' ' << ang1 << " " << ang2 << '\n';
        
        if (ang1 > ang2) swap(ang1, ang2);
        if (ang2 - ang1 > PI) swap(ang1, ang2);
        
        if (ang1 < -PI / 2) ang1 += PI;
        if (ang1 > PI / 2) ang1 -= PI;
        
        if (ang2 < -PI / 2) ang2 += PI;
        if (ang2 > PI / 2) ang2 -= PI;
        
        if (ang1 > ang2) act += dim;
        
        work.pb(mp(ang1 - eps, +dim));
        work.pb(mp(ang2 + eps, -dim));
    }
    
    ans = act;
    sort(work.begin(), work.end());
    
    //cerr << act << '\n';
    
    for (auto e : work) {
        act += e.second;
        ans = max(ans, act);
        
        //cerr << e.first << ' ' << e.second << '\n';
    }
    
    return ans;
}

int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &xx1, &xx2, &yy);
        o[i] = {xx1, xx2, yy};
        
        if (o[i].x1 > o[i].x2) swap(o[i].x1, o[i].x2);
    }
    
    
    for (i = 1; i <= n; i++) {
        ans = max(ans, solve(o[i].x1, o[i].y) + o[i].x2 - o[i].x1);
        ans = max(ans, solve(o[i].x2, o[i].y) + o[i].x2 - o[i].x1);  
    }
    
    printf("%d", ans);
    
    
    return 0;
}
