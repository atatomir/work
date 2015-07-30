#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct Echipa {
    char id[150];
    long p,goals;

    void init(){
        memset(id,0,sizeof(id));
        p=goals=0;
    }
};

long i,cnt,g1,g2,id1,id2;
Echipa E[5];
char e1[150],e2[150];

long getId1(){
    long l1,l2;
    for(long i=1;i<=cnt;i++){
        bool found = 1;
        l1 = strlen(E[i].id+1); l2 = strlen(e1+1);
        if(l1!=l2) continue;
        for(long j=1;j<=l1;j++)
            if(E[i].id[j]!=e1[j]) {found=false;break;}


        if(found) return i;
    }
    cnt++;
    for(long i=0;i<150;i++) E[cnt].id[i] = e1[i];
    return cnt;
}
long getId2(){
    long l1,l2;
    for(long i=1;i<=cnt;i++){
        bool found=1;
        l1 = strlen(E[i].id+1); l2 = strlen(e2+1);
        if(l1!=l2) continue;
        for(long j=1;j<=l1;j++)
            if(E[i].id[j]!=e2[j]) {found=false;break;}


        if(found)return i;
    }
    cnt++;
    for(long i=0;i<150;i++) E[cnt].id[i] = e2[i];
    return cnt;
}

bool cmp(const Echipa& a,const Echipa& b){
    if(a.p == b.p) {
        if(a.goals!=b.goals) return a.goals < b.goals;
        long pos = 1; while(a.id[pos]==b.id[pos]) pos++;
        return a.id[pos]<b.id[pos];
    }
    return a.p < b.p;
}

int main()
{
    //freopen("test.in","r",stdin);

    E[1].init();E[2].init();E[3].init();E[4].init();

    for(i=1;i<=6;i++){
        memset(e1,0,sizeof(e1));
        memset(e2,0,sizeof(e2));
        scanf("%s %s %ld %ld\n",e1+1,e2+1,&g1,&g2);
        id1 = getId1();
        id2 = getId2();

        //cerr << e1+1 << '!' << e2+1 << '\n';

        E[id1].goals += g1;
        E[id2].goals += g2;

        if(g1==g2){
            E[id1].p++;
            E[id2].p++;
        } else
        if(g1<g2){
            E[id2].p+=3;
        } else
            E[id1].p+=3;
    }

    sort(E+1,E+5,cmp);
    for(i=4;i;i--) printf("%s\n",E[i].id+1);

    return 0;
}
