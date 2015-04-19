#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

#define maxK 1024
#define INF 10000000000.000;

struct Point{
    double x,y,how;
    long prov;
    void get(){scanf("%lf %lf",&x,&y);}
    double getDist(Point& who){
        double ans = sqrt((x-who.x)*(x-who.x) + (y-who.y)*(y-who.y));
        return ans;
    }
};

long n,m,k,i,actPos;
Point P[maxK];
double How,act;
bool us[maxK];
vector<long> list[maxK];
long howProv,nFinal;

void dfs(long node,double act){
    if(node == nFinal) {
        printf("%.8lf",act/2.00);
    }

    for(long i=0;i<list[node].size();i++){
        dfs(list[node][i],max(act,P[list[node][i]].how));
    }

}

int main()
{
    freopen("hallway.in","r",stdin);
    freopen("hallway.out","w",stdout);

    scanf("%ld %ld%ld",&n,&m,&k);
    for(i=1;i<=k;i++){
        P[i].get();
        P[i].how = 1.00*m-P[i].y;
        P[i].prov = 0;
    }
    How = 1.00*m; howProv = 0;

    for(;true;){
        act = INF; actPos = -1;
        for(i=1;i<=k;i++){
            if(us[i]) continue;
            if(P[i].how < act){
                act = P[i].how;
                actPos = i;
            }
        }

        if(How < act){
            nFinal = howProv;
            dfs(0,How);

            return 0;
        } else {
            us[actPos]=true;
            list[P[actPos].prov].push_back(actPos);
            for(i=1;i<=k;i++){
                if(us[i]) continue;
                if(P[i].how > P[i].getDist(P[actPos])){
                    P[i].how = min(P[i].how,P[i].getDist(P[actPos]));
                    P[i].prov = actPos;
                }
            }
            if(How>P[actPos].y){
                How = P[actPos].y;
                howProv = actPos;
            }
        }
    }

    return 0;
}
