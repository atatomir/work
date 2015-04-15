#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 1024

long t,i,m,n,v[maxN],ans[maxN],x,y;
bool us[maxN][maxN];

inline void Invert(long i,long j){
    while(i<j) {swap(v[i],v[j]);i++;j--;}
}

bool solve(){
    long i,j;
    bool found;

    for(i=1;i<=n;i++){
        if(!us[v[i]][v[i+1]]) continue;

        found = false;
        for(j=i+2;j<=n;j++){
            if(!us[v[i]][v[j]] && !us[v[i+1]][v[j+1]]) {
                Invert(i+1,j);
                found = true; break;
            }
        }

        if(!found)
        for(j=1;j<=i-2;j++){
            if(!us[v[j]][v[i]] && !us[v[j+1]][v[i+1]]){
                Invert(j+1,i);
                found = true; break;
            }
        }

        if(!found) return false;
    }


    return true;
}

int main()
{
    freopen("amici.in","r",stdin);
    freopen("amici.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld%ld",&n,&m);
        memset(us,0,sizeof(us));
        for(i=1;i<=m;i++){
            scanf("%ld%ld",&x,&y);
            us[x][y]=us[y][x]=1;
        }

        for(i=1;i<=n;i++) v[i]=i; v[n+1]=1;
        if(!solve())
            printf("-1\n");
        else{
            for(i=1;i<=n;i++) ans[v[i]] = v[i+1];
            for(i=1;i<=n;i++) printf("%ld ",ans[i]);
            printf("\n");
        }

    }


    return 0;
}
