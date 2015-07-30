#include<stdio.h>
#include<vector>
using namespace std;
int p,xc,yc,n,m,i,j,nr,teren[205][205],xv,yv,av,xg,yg,lung,k,g,x1,x2,y1,y2;
vector <int> galerii[205][205];
void umple(int x, int y)
{
    int c[2][40005],s=0,d=0;
    c[0][0]=x;
    c[1][0]=y;
    while(s<=d)
    {
        if(teren[c[0][s]+1][c[1][s]]==0 && c[0][s]+1<=n)
            if(galerii[c[0][s]+1][c[1][s]].size()!=0)
            {
                xg=c[0][s]+1;
                yg=c[1][s];
                lung=teren[c[0][s]][c[1][s]]+1;
                return;
            }
            else
            if(c[0][s]+1!=xc || c[1][s]!=yc)
            {
                d++;
                c[0][d]=c[0][s]+1;
                c[1][d]=c[1][s];
                teren[c[0][d]][c[1][d]]=teren[c[0][s]][c[1][s]]+1;
            }
        if(teren[c[0][s]][c[1][s]+1]==0 && c[1][s]+1<=m)
            if(galerii[c[0][s]][c[1][s]+1].size()!=0)
            {
                xg=c[0][s];
                yg=c[1][s]+1;
                lung=teren[c[0][s]][c[1][s]]+1;
                return;
            }
            else
            if(c[0][s]!=xc || c[1][s]+1!=yc)
            {
                d++;
                c[0][d]=c[0][s];
                c[1][d]=c[1][s]+1;
                teren[c[0][d]][c[1][d]]=teren[c[0][s]][c[1][s]]+1;
            }
        if(teren[c[0][s]-1][c[1][s]]==0 && c[0][s]-1>=1)
            if(galerii[c[0][s]-1][c[1][s]].size()!=0)
            {
                xg=c[0][s]-1;
                yg=c[1][s];
                lung=teren[c[0][s]][c[1][s]]+1;
                return;
            }
            else
            if(c[0][s]-1!=xc || c[1][s]!=yc)
            {
                d++;
                c[0][d]=c[0][s]-1;
                c[1][d]=c[1][s];
                teren[c[0][d]][c[1][d]]=teren[c[0][s]][c[1][s]]+1;
            }
        if(teren[c[0][s]][c[1][s]-1]==0 && c[1][s]-1>=1)
            if(galerii[c[0][s]][c[1][s]-1].size()!=0)
            {
                xg=c[0][s];
                yg=c[1][s]-1;
                lung=teren[c[0][s]][c[1][s]]+1;
                return;
            }
            else
            if(c[0][s]!=xc || c[1][s]-1!=yc)
            {
                d++;
                c[0][d]=c[0][s];
                c[1][d]=c[1][s]-1;
                teren[c[0][d]][c[1][d]]=teren[c[0][s]][c[1][s]]+1;
            }
        s++;
    }
}
int main()
{
    freopen("cartite.in","r",stdin);
    freopen("cartite.out","w",stdout);
    scanf("%d",&p);
    scanf("%d %d",&n,&m);
    scanf("%d %d",&xc,&yc);
    scanf("%d",&k);
    for(i=0;i<k;i++)
    {
        scanf("%d %d %d",&xv,&yv,&av);
        if(av==0)
            teren[xv][yv]=-1;
        else
            if(av==1)
            {
                teren[xv][yv]=-1;
                if(xv+1<=n)
                    teren[xv+1][yv]=-1;
                if(yv+1<=m)
                    teren[xv][yv+1]=-1;
                if(xv-1>=1)
                    teren[xv-1][yv]=-1;
                if(yv-1>=1)
                    teren[xv][yv-1]=-1;
            }
            else
                if(av==2)
                {
                    teren[xv][yv]=-1;
                    if(xv+1<=n)
                        teren[xv+1][yv]=-1;
                    if(yv+1<=m)
                        teren[xv][yv+1]=-1;
                    if(xv-1>=1)
                        teren[xv-1][yv]=-1;
                    if(yv-1>=1)
                        teren[xv][yv-1]=-1;
                    if(xv+1<=n && yv+1<=m)
                        teren[xv+1][yv+1]=-1;
                    if(xv-1>=1 && yv+1<=m)
                        teren[xv-1][yv+1]=-1;
                    if(xv-1>=1 && yv-1>=1)
                        teren[xv-1][yv-1]=-1;
                    if(xv+1<=n && yv-1>=1)
                        teren[xv+1][yv-1]=-1;
                    if(xv+2<=n)
                        teren[xv+2][yv]=-1;
                    if(yv+2<=n)
                        teren[xv][yv+2]=-1;
                    if(xv-1>=1)
                        teren[xv-2][yv]=-1;
                    if(yv-1>=1)
                        teren[xv][yv-2]=-1;
                }
    }
    nr=1;
    scanf("%d",&g);
    for(i=1;i<=g;i++)
    {
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        galerii[x1][y1].push_back(nr);
        galerii[x2][y2].push_back(nr);
        nr++;
    }
    if(p==1)
    {
        umple(xc,yc);
        printf("%d %d %d",xg,yg,lung);
    }
    printf("\n");
    return 0;
}
