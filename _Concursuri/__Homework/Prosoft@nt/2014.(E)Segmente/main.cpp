#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define maxN 275

const long defX[4]={-1,1,0,0};
const long defY[4]={0,0,-1,0};

struct Point{
    long x,y;
};
struct Segm{
    Point st,en;
};

long n,i,cnt,pos,j,t;
Segm S[maxN];
long xx[maxN<<4],yy[maxN<<4];
bool a[maxN<<4][maxN<<4],inQueue[maxN<<4][maxN<<4];
long dist[maxN<<4][maxN<<4];
Point p,newP,dest,ini;

queue<Point> Q;

long cbX(long x){
    long i=1,j=xx[0],m;
    while(i<=j){
        m = (i+j)>>1;
        if(x<=xx[m])
            j = m-1;
        else
            i = m+1;
    }

    if(i>xx[0]) return -1;
    return i;
}
long cbY(long x){
    long i=1,j=yy[0],m;
    while(i<=j){
        m = (i+j)>>1;
        if(x<=yy[m])
            j = m-1;
        else
            i = m+1;
    }

    if(i>yy[0]) return -1;
    return i;
}

long abss(long x){
    if(x<0) return -x;
    return x;
}

void deBug(){
    for(long i=1;i<=xx[0];i++){
        cerr << i << '|';
        for(long j=1;j<=yy[0];j++) cerr << a[i][j] << ' ';
        cerr << '\n';
    }
}

int main()
{
    freopen("segmente.in","r",stdin);
    freopen("segmente.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld%ld%ld%ld",&S[i].st.x,&S[i].st.y,
                             &S[i].en.x,&S[i].en.y);

        S[i].st.x<<=1;S[i].st.y<<=1;
        S[i].en.x<<=1;S[i].en.y<<=1;

        xx[++xx[0]] = S[i].st.x; xx[++xx[0]] = S[i].en.x;
        xx[++xx[0]] = S[i].st.x-1; xx[++xx[0]] = S[i].en.x-1;
        xx[++xx[0]] = S[i].st.x+1; xx[++xx[0]] = S[i].en.x+1;

        yy[++yy[0]] = S[i].st.y; yy[++yy[0]] = S[i].en.y;
        yy[++yy[0]] = S[i].st.y-1; yy[++yy[0]] = S[i].en.y-1;
        yy[++yy[0]] = S[i].st.y+1; yy[++yy[0]] = S[i].en.y+1;
    }

    sort(xx+1,xx+xx[0]+1);
    sort(yy+1,yy+yy[0]+1);

    cnt=1;
    for(i=2;i<=xx[0];i++)
        if(xx[i]!=xx[i-1]) xx[++cnt] = xx[i];
    xx[0] = cnt;

    cnt=1;
    for(i=2;i<=yy[0];i++)
        if(yy[i]!=yy[i-1]) yy[++cnt] = yy[i];
    yy[0] = cnt;

    for(i=1;i<=n;i++){
        if(S[i].st.x==S[i].en.x){
            pos = cbX(S[i].st.x);
            j = cbY(S[i].st.y);

            while(j<=yy[0]&&yy[j]<=S[i].en.y){
                a[pos][j] = 1;
                j++;
            }
        } else {
            pos = cbY(S[i].st.y);
            j = cbX(S[i].st.x);

            while(j<=xx[0]&&xx[j]<=S[i].en.x){
                a[j][pos] = 1;
                j++;
            }
        }
    }

    scanf("%ld %ld",&n,&t);
    if(t==1){
        for(i=1;i<=n;i++){
            scanf("%ld%ld",&p.x,&p.y);
            p.x<<=1; p.y<<=1;
            long posX = cbX(p.x);
            long posY = cbY(p.y);

            if(posX==-1||posY==-1){printf("0 ");continue;}
            if(xx[posX]!=p.x) posX--;
            if(yy[posY]!=p.y) posY--;
            if(posX==0||posY==0) {printf("0 ");continue;}
            printf("%ld ",a[posX][posY]);
        }
    }else {
        for(long t=1;t<=n;t++){
            memset(dist,0,sizeof(dist));
            scanf("%ld%ld%ld%ld",&p.x,&p.y,&dest.x,&dest.y);
            p.x<<=1;p.y<<=1;dest.x<<=1;dest.y<<=1;
            p.x = cbX(p.x); dest.x=cbX(dest.x);
            p.y = cbY(p.y); dest.y=cbY(dest.y);
            ini = p;

            dist[p.x][p.y] = 1; Q.push(p);
            while(!Q.empty()){
                p = Q.front(); Q.pop();
                inQueue[p.x][p.y] = false;

                for(i=0;i<2;i++){
                    newP = p; newP.x += defX[i];
                    if(a[newP.x][newP.y]==0) continue;
                    if(dist[newP.x][newP.y]>0&&dist[newP.x][newP.y]<=dist[p.x][p.y]+abss(xx[newP.x]-xx[p.x])) continue;

                    dist[newP.x][newP.y] = dist[p.x][p.y]+abss(xx[newP.x]-xx[p.x]);
                    if(!inQueue[newP.x][newP.y])Q.push(newP);
                    inQueue[newP.x][newP.y] = true;
                }
                for(i=2;i<3;i++){
                    newP = p; newP.y += defY[i];
                    if(a[newP.x][newP.y]==0) continue;
                    if(dist[newP.x][newP.y]!=0&&dist[newP.x][newP.y]<=dist[p.x][p.y]+abss(yy[newP.y]-yy[p.y]))continue;

                    dist[newP.x][newP.y] = dist[p.x][p.y]+abss(yy[newP.y]-yy[p.y]);
                    if(!inQueue[newP.x][newP.y]) Q.push(newP);
                    inQueue[newP.x][newP.y] = true;
                }
            }

            if(dist[dest.x][dest.y]==0) printf("-1 "); else
            printf("%ld ",(dist[dest.x][dest.y]/2));
        }
    }

    return 0;
}
