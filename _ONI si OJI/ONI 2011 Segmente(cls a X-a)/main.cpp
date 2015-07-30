#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<long,pair<long,long> > Segm;

#define pos first
#define left second.first
#define right second.second
#define mp make_pair

#define x1 xx1
#define x2 xx2
#define y1 yy1
#define y2 yy2

long n,i,j,x1,x2,y1,y2,m,t;
vector<Segm> O,V,tmp; // orizontal vetical

long cbL(long x){
    long i=0,j=V.size()-1,m;
    do{
        m = (i+j)/2;
        if(x <= V[m].pos)
            j = m-1;
        else
            i = m+1;
    } while(i<=j);
    return i;
}
long cbR(long x){
    long i=0,j=V.size()-1,m;
    do{
        m = (i+j)/2;
        if(x < V[m].pos)
            j = m-1;
        else
            i = m+1;
    } while(i<=j);
    return j;
}

bool isGood(long d){
    long i,j,k,pos1,pos2;

    for(i=0;i<O.size()-1;i++){
        for(j=i+1;j<O.size();j++){
            long cont = 0;
            pos1 = cbL(max(O[i].left,O[j].left)-d);
            pos2 = cbR(min(O[i].right,O[j].right)+d);
            for(k=pos1;k<=pos2;k++){
                if(V[k].left - d <= O[i].pos && V[k].right + d >= O[j].pos) {
                    cont++;
                    if(cont == 2) return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    freopen("segmente.in","r",stdin);
    freopen("segmente.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld %ld %ld",&x1,&y1,&x2,&y2);
        if(x1 == x2){
            if(y1 > y2) {t=y1;y1=y2;y2=t;}
            V.push_back(mp(x1,mp(y1,y2)));
        }else{
            if(x1 > x2) {t=x1;x1=x2;x2=t;}
            O.push_back(mp(y1,mp(x1,x2)));
        }
    }
    sort(V.begin(),V.end());
    sort(O.begin(),O.end());

    if(O.size() > V.size()){
        tmp = O; O = V; V = tmp;
    }

    i=1;j=1000000000;
    do{
        m = (i+j)/2;
        if(isGood(m))
            j = m-1;
        else
            i = m+1;
    } while(i<=j);

    printf("%ld",i);

    return 0;
}
