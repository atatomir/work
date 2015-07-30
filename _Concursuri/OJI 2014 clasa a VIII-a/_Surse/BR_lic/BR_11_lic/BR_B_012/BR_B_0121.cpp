#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

fstream f("cartite.in",ios::in);
fstream g("cartite.out",ios::out);

const int nmax=205,mmax=205,INF=0x3f3f3f3f;

//vector <int> a[nmax*mmax];

unsigned int minim,xminim,yminim,xc,yc,n,m,i,j,parc[nmax][mmax],ter[nmax][mmax],xv,yv,distgasit,porn,p,k,val,nrg,startgasit,x,y,xx,yy;
unsigned int nr1,nr2;
/*void traseu()
{
    queue <unsigned int> q;
    int viz[nmax*mmax];
    memset(viz,0,sizeof(viz));
    q.push(porn);
    viz[porn]=1;
    unsigned int barloage=0,nc;
    while (!q.empty())
    {
        nc=q.front();
        q.pop();
        barloage++;

    }
}*/

void latime()
{
   queue <unsigned int> lin;
   queue <unsigned int> col;
   queue <unsigned int> dist;
   lin.push(xc);col.push(yc);
   dist.push(0);
   parc[xc][yc]=1;
   unsigned int gasitbarlog=0,lc,cc,dc;
   while ((!lin.empty())&&(!gasitbarlog))
   {
       lc=lin.front();lin.pop();
       cc=col.front();col.pop();
       dc=dist.front();dist.pop();
       if (ter[lc][cc]==3)
       {
           if (dc<minim)
           {
               minim=dc;
               xminim=lc;yminim=cc;
               gasitbarlog=1;
           }
       }
       if ((lc<n)&&(ter[lc+1][cc]!=1)&&(parc[lc+1][cc]==0))
        {
            parc[lc+1][cc]=1;
            lin.push(lc+1);
            col.push(cc);
            dist.push(dc+1);
        }
        if ((lc>1)&&(ter[lc-1][cc]!=1)&&(parc[lc-1][cc]==0))
        {
            parc[lc-1][cc]=1;
            lin.push(lc-1);
            col.push(cc);
            dist.push(dc+1);
        }
        if ((cc<m)&&(ter[lc][cc+1]!=1)&&(parc[lc][cc+1]==0))
        {
            parc[lc][cc+1]=1;
            lin.push(lc);
            col.push(cc+1);
            dist.push(dc+1);
        }
        if ((cc>1)&&(ter[lc][cc-1]!=1)&&(parc[lc][cc-1]==0))
        {
            parc[lc][cc-1]=1;
            lin.push(lc);
            col.push(cc-1);
            dist.push(dc+1);
        }
   }
}

int main()
{
    f>>p;
    f>>n>>m;
    f>>xc>>yc;
    ter[xc][yc]=2;
    f>>k;
    for (i=1;i<=k;i++)
    {
        f>>xv>>yv>>val;
        ter[xv][yv]=1;
        if ((val==1)||(val==2))
        {
            if (xv<n) ter[xv+1][yv]=1;
            if (xv>1) ter[xv-1][yv]=1;
            if (yv<m) ter[xv][yv+1]=1;
            if (yv>1) ter[xv][yv-1]=1;
        }
        if (val==2)
        {
            if ((xv>1)&&(yv>1)) ter[xv-1][yv-1]=1;
            if ((xv>1)&&(yv<m)) ter[xv-1][yv+1]=1;
            if ((xv<n)&&(yv>1)) ter[xv+1][yv-1]=1;
            if ((xv<n)&&(yv<m)) ter[xv+1][yv+1]=1;
            if (xv>2) ter[xv-2][yv]=1;
            if (xv<n-1) ter[xv+2][yv]=1;
            if (yv>2) ter[xv][yv-2]=1;
            if (yv<m-1) ter[xv][yv+2]=1;
        }
    }
    f>>nrg;
    startgasit=0;
    distgasit=0;
    //nrb=0;
    for (i=1;i<=nrg;i++)
    {
        f>>x>>y>>xx>>yy;
        nr1=m*(x-1)+y;
        nr2=m*(xx-1)+yy;
        if (ter[x][y]!=1)
        {
           if (ter[x][y]!=2) ter[x][y]=3;
                    else
                    {
                        distgasit=1;
                        //dist=0;
                    }
            startgasit=1;
            porn=nr1;
        }
        if (ter[xx][yy]!=1)
        {
           if (ter[xx][yy]!=2) ter[xx][yy]=3;
                    else
                    {
                        distgasit=1;
                    }
            startgasit=1;
            porn=nr2;
        }
    }
    if (p==1) //pct a
    {
        if (distgasit)
        {
            g<<xc<<" "<<yc<<"0";
            f.close();g.close();
            return 0;
        }
        minim=INF;xminim=0;yminim=0;
        latime();
        g<<xminim<<" "<<yminim<<" "<<minim;
    }
    /*else //pct b
    {
        traseu();
    }*/
    f.close();g.close();
    return 0;
}
