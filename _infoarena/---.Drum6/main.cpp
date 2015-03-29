#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const long defX[2]={+1,0};
const long defY[2]={0,+1};

struct Point{
    long x,y;
};
Point mp(long xx,long yy){
    Point tmp;
    tmp.x = xx; tmp.y = yy;
    return tmp;
}

#define maxN 1011

long n,m,i,j,s,d,t;
char S[maxN][maxN];
vector<Point> act[2];
long prov[maxN][maxN];
bool used[maxN][maxN];
char minCh;

vector<char> ans;

void Answer(long x,long y){
    ans.push_back(S[x][y]);
    if(x+y==2) return;
    for(long i=0;i<2;i++){
        Point p ;
        p.x = x - defX[i];
        p.y = y - defY[i];

        if(used[p.x][p.y]) {Answer(p.x,p.y);return;}
    }

}

int main()
{
    freopen("drum6.in","r",stdin);
    freopen("drum6.out","w",stdout);

    scanf("%ld%ld\n",&n,&m);
    for(i=1;i<=n;i++) gets(S[i]+1);

    for(i=1;i<=n;i++) S[i][m+1]='z'+1;
    for(i=1;i<=m;i++) S[n+1][i]='z'+1;

    s=0;d=1;
    act[0].push_back(mp(1,1)); used[1][1]=true;
    for(t=n+m-2;t;t--){
        minCh = 'z'+1;
        for(i=0;i<act[s].size();i++){
            Point p = act[s][i];
            for(j=0;j<2;j++){
                Point newP=p;
                newP.x += defX[j];
                newP.y += defY[j];

                minCh = min(minCh,S[newP.x][newP.y]);
            }
        }
        for(i=0;i<act[s].size();i++){
            Point p = act[s][i];
            for(j=0;j<2;j++){
                Point newP=p;
                newP.x += defX[j];
                newP.y += defY[j];

                if(minCh==S[newP.x][newP.y]){
                    if(used[newP.x][newP.y]==false){
                        act[d].push_back(newP);
                        used[newP.x][newP.y] = true;
                    }
                }
            }
        }

        act[s].clear();
        s ^= 1; d^= 1;
    }

    Answer(n,m);
    for(i=ans.size()-1;i>=0;i--) printf("%c",ans[i]);

    return 0;
}
