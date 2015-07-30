#include <fstream>
using namespace std;
int p,m,n,q1,q2,a[201][201],vx,vy,vr,xc,yc,i,j,k,ng,u[101][101],e1,e2,x,y;
int a1,a2,a3,a4;
short dx[]={0,1,-1,0},dy[]={1,0,0,-1},v[101][101],nv;
struct punct
{
    short x,y;
}w;
struct nod
{
    short x,y;
    nod* urm;
}*q,*h,*sf;
punct b[201];
int main()
{
    ifstream f("cartite.in");
    ofstream g("cartite.out");
    f>>p>>m>>n;
    f>>xc>>yc;
    f>>k;
    if(p==1)
    {
        punct *c=new punct[n*m+1];
        for(i=1;i<=k;i++)
        {
            for(j=1;j<=n;j++)
                a[0][j]=a[m+1][j]=-1;
            for(j=1;j<=m;j++)
                a[j][0]=a[j][n+1]=-1;
            f>>vx>>vy>>vr;
            if(vr==0)
                a[vx][vy]=-1;
            else if(vr==1)
                a[vx][vy]=a[vx-1][vy]=a[vx+1][vy]=a[vx][vy+1]=a[vx][vy-1]=-1;
            else if(vr==2)
            {
                a[vx][vy]=a[vx-1][vy]=a[vx+1][vy]=a[vx][vy+1]=a[vx][vy-1]=a[vx-1][vy-1]=a[vx-1][vy+1]=a[vx+1][vy+1]=a[vx+1][vy-1]=-1;
                a[vx+2][vy]=a[vx][vy+2]=-1;
                if(vy>1)    a[vx][vy-2]=-1;
                if(vx>1)    a[vx-2][vy]=-1;
            }
        }
        f>>ng;
        for(i=1;i<=ng;i++)
        {
            f>>a1>>a2>>a3>>a4;
            if(a[a1][a2]!=-1) a[a1][a2]=-2;
            if(a[a3][a4]!=-1) a[a3][a4]=-2;
        }
        if(a[xc][yc]==-2) g<<xc<<' '<<yc<<' '<<"0";
        else{
        q1=q2=1;
        c[1].x=xc;c[1].y=yc;
        a[xc][yc]=1;
        int q=1;
        while(q1<=q2&&q)
        {
            w=c[q1++];
            for(i=0;i<4;i++)
                if(a[w.x+dx[i]][w.y+dy[i]]==0)
                    {
                        q2++;
                        c[q2].x=w.x+dx[i];
                        c[q2].y=w.y+dy[i];
                        a[w.x+dx[i]][w.y+dy[i]]=a[w.x][w.y]+1;
                    }
                else if(a[w.x+dx[i]][w.y+dy[i]]==-2)
                {
                    q=0;
                    g<<w.x+dx[i]<<' '<<w.y+dy[i]<<' '<<a[w.x][w.y];
                }
        }
        }
        g<<'\n';
    }
    else
    {
        for(i=1;i<=k;i++) f>>vx>>vy>>vr;
        f>>ng;
        for(i=1;i<=ng;i++)
        {
            f>>a1>>a2>>a3>>a4;
            if(v[a1][a2]==0){v[a1][a2]=++nv;b[nv].x=a1;b[nv].y=a2;}
            if(v[a3][a4]==0){v[a3][a4]=++nv;b[nv].x=a3;b[nv].y=a4;}
            e1=v[a1][a2];e2=v[a3][a4];
            a[e1][++a[e1][0]]=e2;
            a[e2][++a[e2][0]]=e1;
        }
        q=new nod;q->x=b[1].x;q->y=b[1].y;q->urm=NULL;
        x=y=1;
        do
        {
            k=0;
            for(i=1;i<=a[x][0];i++)
                if(u[x][a[x][i]]==0)
                {
                    u[x][a[x][i]]=1;u[x][0]++;
                    for(j=1;j<=a[a[x][i]][0];j++)
                        if(a[a[x][i]][j]==x){u[a[x][i]][j]=1;j=ng;u[a[x][i]][0]++;}
                    h=new nod;h->x=x;h->y=a[x][i];h->urm=q;q=h;
                    x=a[x][i];
                    i=ng;
                    k=1;
                }

        }while(k&&x!=y);

       do{

            for(h=q;h&&k;h=h->urm)
            if(u[h->x][0]!=a[h->x][0])
               {y=h->x;k=0;sf=new nod;sf=h;h->urm=h;}
            x=y;
        do
        {
            k=0;
            for(i=1;i<=a[x][0];i++)
                if(u[x][a[x][i]]==0)
                {
                    u[x][a[x][i]]=1;u[x][0]++;
                    for(j=1;j<=a[a[x][i]][0];j++)
                        if(a[a[x][i]][j]==x){u[a[x][i]][j]=1;j=ng;u[a[x][i]][0]++;}
                    h=new nod;h->x=x;h->y=a[x][i];h->urm=sf->urm;sf->urm=h;
                    x=a[x][i];
                    i=ng;
                    k=1;
                }
        }while(k&&x!=y);
        k=1;
        }while(x!=y);
        for(h=q;h;h=h->urm) g<<b[h->y].x<<' '<<b[h->y].y<<'\n';
    }
    f.close();
    g.close();
return 0;}
