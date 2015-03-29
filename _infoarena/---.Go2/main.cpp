#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

#define maxN 111
#define pb push_back
#define mod 1000000007

const long defX[4]={-1,1,0,0};
const long defY[4]={0,0,-1,1};

long n,m,i,j,p,cnt,xx,yy,pre;
char a[maxN][maxN];
vector<long> v[maxN][maxN];

bitset<maxN> eq[maxN*maxN],tmp;
long used,Answer;

void Trans(long sx,long sy,long dx,long dy){
    for(long i=0;i<v[sx][sy].size();i++) v[dx][dy].pb(v[sx][sy][i]);
}
void Comp(long dest,long sx,long sy){
    for(long i=0;i<v[sx][sy].size();i++){
        eq[dest][v[sx][sy][i]] = eq[dest][v[sx][sy][i]]^1;
    }
}
long myPow(long long a,long b){
    long long ans=1;
    while(b){
        if(b&1) ans = (ans*a)%mod;
        a = (a*a)%mod;
        b>>=1;
    }
    return (long)ans;
}

bool Gauss(){
    long i,j,k,l;

    i=j=1;
    while(i<=cnt&&j<pre){
        for(k=i;k<=cnt;k++)
            if(eq[k][j]==1) break;

        if(k>cnt) {j++;continue;}
        if(k!=i){ tmp = eq[i]; eq[i] = eq[k]; eq[k]=tmp; }

        for(k=i+1;k<=cnt;k++){
            if(eq[k][j]==0) continue;
            for(l=j;l<=pre;l++) eq[k][l] = eq[k][l]^eq[i][l];
        }

        i++;j++;
    }

    used = pre;
    for(i=cnt;i;i--){
        for(j=1;j<=pre;j++){
            if(eq[i][j]){
                if(j==pre) return false;
                Answer += used-j-1; used = j;

                break;
            }
        }
    }
    Answer += used-1;

    return true;
}

int main()
{
    freopen("go2.in","r",stdin);
    freopen("go2.out","w",stdout);

    scanf("%ld %ld\n",&n,&m);
    for(i=1;i<=n;i++) scanf("%s\n",a[i]+1);

    for(i=1;i<=m;i++) v[1][i].pb(i);
    for(i=2;i<=n;i++){
        for(j=1;j<=m;j++){
            Trans(i-1,j-1,i,j);
            Trans(i-1,j+1,i,j);
            Trans(i-2,j,i,j);

            sort(v[i][j].begin(),v[i][j].end());
            cnt = 0;
            for(p=0;p<v[i][j].size();p++){
                if(p==v[i][j].size()-1){
                    v[i][j][cnt++] = v[i][j][p];
                }else {
                    if(v[i][j][p]==v[i][j][p+1])
                        p++;
                    else
                        v[i][j][cnt++] = v[i][j][p];
                }
            }
            v[i][j].resize(cnt);
        }
    }

    cnt =0; pre = m+1;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cnt++;

            for(p=0;p<4;p++){
                xx = i + defX[p];
                yy = j + defY[p];

                if(a[xx][yy]=='1'){
                    eq[cnt][pre] = eq[cnt][pre]^1;
                } else
                if(a[xx][yy]=='?'){
                    Comp(cnt,xx,yy);
                }
            }
        }
    }

    if(!Gauss()){
        printf("0");
    } else {
        Answer = myPow(2,Answer);
        printf("%ld",Answer);
    }



    return 0;
}
