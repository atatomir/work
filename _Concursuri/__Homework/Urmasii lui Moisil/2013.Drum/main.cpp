#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 511

const long defX[4]={-1,1,0,0};
const long defY[4]={0,0,-1,1};

long n,m,v,i,cnt,pos,posX,posY;
bool used[maxN][maxN];
bool star[maxN][maxN];

bool found=false;

void getStar(long x,long y){
    for(long i=0;i<4;i++){
        long xx=x+defX[i],yy=y+defY[i];
        if(star[xx][yy]) {
            star[x][y] = true;
            return;
        }
    }
}

void Lee(long x,long y){
    if(x==n) found = true;
    if(found) return;

    for(long i=0;i<4;i++){
        long xx=x+defX[i],yy=y+defY[i];
        if(!used[xx][yy]) continue;
        if(star[xx][yy]) continue;
        star[xx][yy]=true;
        Lee(xx,yy);
    }
}

int main()
{
    freopen("drum.in","r",stdin);
    freopen("drum.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&v);
    for(i=1;i<=m;i++) star[0][i] = true;

    for(i=1;i<=v;i++){
        scanf("%ld",&cnt);
        for(;cnt;cnt--){
            scanf("%ld",&pos);
            posX = (pos+m-1)/m;
            posY = pos - (posX-1)*m;

            used[posX][posY] = true;
            getStar(posX,posY);

            if(star[posX][posY]){
                Lee(posX,posY);
            }

            if(found){
                printf("%ld",i);
                return 0;
            }
        }
    }

    return 0;
}
