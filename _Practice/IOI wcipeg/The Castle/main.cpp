#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG @atatomir
#define maxN 55

const long defX[4]={0,-1,0,1};
const long defY[4]={-1,0,1,0};

long n,m,i,j,hh;
long id[maxN][maxN],same[maxN][maxN];
long how[maxN][maxN];

long cntRooms,bestRoom;
long maxDimRooms,mdX,mdY;
char dir;

void dfsCnt(long x,long y){
    how[x][y]=-1; hh++;
    for(long i=0;i<4;i++){
        long bit = 1<<i;
        if(id[x][y]&bit) continue;

        long xx = x + defX[i];
        long yy = y + defY[i];
        if(how[xx][yy]==-1) continue;
        dfsCnt(xx,yy);
    }
}

void dfsFill(long x,long y){
    how[x][y]=hh;
    same[x][y]=cntRooms;
    for(long i=0;i<4;i++){
        long bit = 1<<i;
        if(id[x][y]&bit) continue;

        long xx = x + defX[i];
        long yy = y + defY[i];
        if(how[xx][yy]!=-1) continue;
        dfsFill(xx,yy);
    }
}

void doIt(long val,long x,long y,char ch){
    maxDimRooms = val;
    mdX = x; mdY = y;
    dir = ch;
}
void setIt(long val,long x,long y,char ch){
    if(val > maxDimRooms){
        doIt(val,x,y,ch);
    } else
    if(val == maxDimRooms){
        if(x!=mdX || y != mdY) return;
        if(dir == 'E' && ch == 'N') doIt(val,x,y,ch);
    }
}

void testAns(long x,long y){
    if(id[x][y]&2){ //! N
        if(same[x][y]!=same[x-1][y] && x!=1){
            long calc = how[x][y]+how[x-1][y];
            setIt(calc,x,y,'N');
        }
    }
    if(id[x][y]&4){ //! E
        if(same[x][y]!=same[x][y+1] && y!=m){
            long calc = how[x][y]+how[x][y+1];
            setIt(calc,x,y,'E');
        }
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld",&m,&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%ld",&id[i][j]);

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(how[i][j]) continue;
            hh=0; dfsCnt(i,j);
            dfsFill(i,j);
            cntRooms++; bestRoom=max(bestRoom,hh);
        }
    }

    for(j=1;j<=m;j++)
        for(i=n;i;i--)
            testAns(i,j);

    printf("%ld\n%ld\n%ld\n%ld %ld %c",cntRooms,bestRoom,maxDimRooms,mdX,mdY,dir);

    return 0;
}
