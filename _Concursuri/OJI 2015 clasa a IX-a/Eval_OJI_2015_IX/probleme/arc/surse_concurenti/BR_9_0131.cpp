#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxN 10011

struct Secv{
    long col,nr;
    bool used;
};

long t,n,i,cnt,id,j;
long a[maxN];
Secv scv[maxN];

struct hElem{
    long id,control;
};
hElem mp(long idd,long ccontrol){
    hElem tmp;
    tmp.id = idd; tmp.control=ccontrol;
    return tmp;
}

struct cmp{
    bool operator()(const hElem& e1,const hElem& e2){
        long id1=e1.id,id2=e2.id;
        if(scv[id1].nr==scv[id2].nr) return id1>id2;
        return scv[id1].nr < scv[id2].nr;
    }
};

priority_queue<hElem,vector<hElem>,cmp> H;

int main()
{
    freopen("arc.in","r",stdin);
    freopen("arc.out","w",stdout);

    scanf("%ld",&t);
    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);

    i=1;
    while(i<=n){
        scv[++cnt].col = a[i];
        scv[cnt].nr = 0; scv[cnt].used=false;

        while(i<=n&&a[i]==scv[cnt].col){
            i++; scv[cnt].nr++;
        }
    }

    if(t==1){
        printf("%ld",cnt);
        return 0;
    } else {
        for(i=1;i<=n;i++) H.push(mp(i,scv[i].nr));
        scv[cnt+1].col = -1;
        while(!H.empty()){
            hElem act = H.top(); H.pop();
            long id = act.id;

            if(scv[id].used==true) continue;
            if(scv[id].nr != act.control) continue;
            if(scv[id].nr<3) continue;

            scv[id].used = true;
            i=id-1;j=id+1;
            while(scv[i].used) i--;
            while(scv[j].used) j++;

            while(scv[i].col==scv[j].col){
                long dim = scv[i].nr + scv[j].nr;
                if(dim<3){
                    scv[j].used = true;
                    scv[i].nr = dim; H.push(mp(i,scv[i].nr));
                    break;
                } else {
                    scv[i].used= true;
                    scv[j].used= true;
                    i--; j++;

                    while(scv[i].used) i--;
                    while(scv[j].used) j++;
                }
            }
        }

        long ans=0;
        for(i=1;i<=cnt;i++)
            if(scv[i].used==false) ans+=scv[i].nr;
        printf("%ld\n",ans);
        for(i=1;i<=cnt;i++){
            if(scv[i].used) continue;
            for(j=scv[i].nr;j;j--) printf("%ld\n",scv[i].col);
        }
    }


    return 0;
}
