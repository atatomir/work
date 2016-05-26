// Profesor Gorea Claudiu-Cristian - 100 de puncte - O(N * M * D^2)
///Colegiul National "Al. Papiu Ilarian" Tg-Mures
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

struct intrus
{
    int info,x,y,id,vip;
} v[1000002];

ifstream fin ("intrus.in");
ofstream fout("intrus.out");

int a[1002][1002],viz[1000002];
int n,m,i,j,l,c,cerinta,d,suspect,maxid, lim,li,lf,ci,cf;
bool ciur[1000002];


int ordonare(intrus a, intrus b)
{
    if (a.vip<b.vip) return 0;

    if ((a.vip==b.vip) and (a.id<b.id)) return 0;

    if ((a.vip==b.vip) and (a.id==b.id) and ((a.x*m+a.y)>(b.x*m+b.y)) ) return 0;

    return 1;
}

int main()
{
    fin>>cerinta>>n>>m>>d;   ///cerinta,n,m lungimile
    maxid=0;
    suspect=0;
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
        {
            fin>>a[i][j];
            ///if(a[i][j])
                viz[a[i][j]]++;
            maxid=max(maxid, a[i][j]);
        }
    viz[0]=0;
    ///ciurul false initial
    ciur[0]=ciur[1]=true;
    for(i=1; i<=maxid; i++)
        if (ciur[i]==false)
            for(j=i+i; j<=maxid; j+=i)
                ciur[j]=true; /// nu mai e prim

    if (cerinta==1)
    {
        suspect=0;
        for(i=1; i<=maxid; i++)
            if (viz[i]>1) suspect+=viz[i];
        fout<<suspect<<'\n';
    }
    else
    {
        suspect=0;
        lim=(d-1)/2; ///d-impar
        for(i=1; i<=n; i++)
            for(j=1; j<=m; j++)
                if (viz[a[i][j]]>1) /// are id multiplicat
                {
                    suspect++;
                    v[suspect].info=a[i][j];
                    v[suspect].x=i;
                    v[suspect].y=j;
                    v[suspect].id=0;
                    li=max(i-lim,1);
                    lf=min(i+lim,n);
                    ci=max(j-lim,1);
                    cf=min(j+lim,m);
                    for(l=li; l<=lf; l++)
                        for(c=ci; c<=cf; c++)
                            if (ciur[a[l][c]]==false)
                            {
                                if (l!=i or c!=j) v[suspect].vip++,   v[suspect].id=max(v[suspect].id, a[l][c]);
                            }
                }
        sort(v+1,v+1+suspect,ordonare);
        if (suspect<1) fout<<-1<<endl;
        else
            for (i=1; i<=suspect; i++)
                fout<<v[i].info<<' '<<v[i].x<<' '<<v[i].y<<'\n';
    }


}
