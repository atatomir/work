#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct opp{
    long time,player,room;
    bool dead;
}e;

#define maxM 1000

long n,m,i,j,dead;
long cam[maxM];
vector<opp> V;

bool cmp(const opp& a,const opp& b){
    if(a.time == b.time) {
        if(a.dead == false && b.dead == true) return false;
        return true;
    }
    return a.time < b.time;
}

int main()
{
    freopen("joc10.in","r",stdin);
    freopen("joc10.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) scanf("%ld",&cam[j]);

        long timp = 0,dir;
        j = 1;
        while(cam[j] > 0 && cam[j] != 9999){
            long pen = cam[j]%10;
            dir = cam[j]/10;
            timp += pen+1;

            cam[j] = -1;
            j = dir;
        }
        if(cam[j] == -1) continue;

        e.time = timp; e.player = i; e.room = j;
        if(cam[j] == 0) e.dead = true; else e.dead = false;
        V.push_back(e);
    }
    sort(V.begin(),V.end(),cmp);

    for(i=0;i<V.size();i++){
        if(V[i].dead) dead++;
        else {
            e = V[i];
            printf("%ld %ld %ld %ld",e.player,e.room,e.time+1,dead);
            break;
        }
    }

    return 0;
}
