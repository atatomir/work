#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

#define maxN 1000005

struct QElem{
    char c;
    long pos;
    QElem operator()(char cl,long posl){
        c = cl; pos = pos;
        return *this;
    }
} elem;

long n,m,i,j,pos,qpos,md;
long maxi;
char s[maxN],ans[maxN],maxim;
deque<QElem> Q;

int main()
{
    freopen("trompeta.in","r",stdin);
    freopen("trompeta.out","w",stdout);

    scanf("%ld %ld\n",&n,&m); md = m; m = n-m;
    scanf("%s",&s);

    pos = 0; qpos = -1;
    for(i=0;i<md;i++){
        for(j=qpos+1;j<=pos+m;j++) {
            if(!Q.empty())
            while(Q.back().c < s[j]) {
                Q.pop_back();
                if(Q.empty()) break;
            }
            Q.push_back(elem(s[j],j));
        }
        qpos = pos+m;

        maxim = Q.front().c;
        maxi  = Q.front().pos;
                Q.pop_front();

        ans[i] = maxim;
        m -= maxi-pos;
        pos = maxi+1;
    }

    printf("%s",ans);

    return 0;
}
