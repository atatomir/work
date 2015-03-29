#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 111
#define maxS 100111

long n,m,i,x;
vector<long> list[maxN];
long l[maxN],r[maxN];
bool u[maxN];
bool change;

char s[maxS];

bool pairUp(long node){
    vector<long>::iterator it;
    if(u[node]) return false;
    u[node] = true;

    for(it=list[node].begin();it!=list[node].end();it++){
        if(!r[*it]){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }

    for(it=list[node].begin();it!=list[node].end();it++){
        if(pairUp(r[*it])){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }

    return false;
}

int main()
{
    freopen("senat.in","r",stdin);
    freopen("senat.out","w",stdout);

    scanf("%ld%ld\n",&m,&n);
    for(i=1;i<=n;i++){
        gets(s); long pos=0;
        while(s[pos]==' ') pos++;
        while(s[pos]!='\0'){
            while(s[pos]==' ') pos++;
            x=0;
            while(s[pos]>='0'&&s[pos]<='9'){
                x = x*10 + s[pos]-'0';
                pos++;
            }
            while(s[pos]==' ') pos++;

            list[i].push_back(x);
        }
    }

    change=1;
    while(change){
        change=0;
        memset(u,0,sizeof(u));
        for(i=1;i<=n;i++)
            if(!l[i]) change |= pairUp(i);
    }

    long cnt=0;
    for(i=1;i<=n;i++)
        if(l[i]) cnt++;

    if(cnt<n){
        printf("0");
    } else {
        for(i=1;i<=n;i++)
            printf("%ld\n",l[i]);
    }

    return 0;
}
