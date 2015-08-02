#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("betasah.in");
    ofstream h("betasah.out");
    int v[100][100],poz[100],poz1[100];
    int i,j,N,D,K,j1,max=0,l,x,y,nr,o,p;
    f>>N>>D>>K;
    for (i=1;i<=D;i++)
        {f>>x>>y;
        v[x][y]=1;
        poz[i]=x;
        poz1[i]=y;}
    for (i=D+1;i<=K+D+1;i++)
        {f>>x>>y;
        v[x][y]=2;}
    j1=1;
    for (i=1;i<=N;i++)
       {nr=0;
       for (j=1;j<=j1;j++)
            if(v[i][j]==0||v[i][j]==1)
                nr++;
        if(nr>max)
            max=nr;
        if(j1!=N)
            j1++;
       }
    h<<max<<"\n";
    nr=0;
    for(l=1;l<=D;l++)
        {x=poz[l];
        y=poz1[l];
        for(i=1;i<=x;i++)
            if(v[x][i]!=1&&v[x][i]!=2&&v[x][i]!=3)
                {nr++;
                v[x][i]=3;}
        for(i=N;i>=y;i--)
            if(v[i][y]!=1&&v[i][y]!=2&&v[i][y]!=3)
                {nr++;
                v[i][y]=3;}
        o=x;
        for(i=y-1;i>=1;i--)
            {o--;
            if(v[o][i]!=1&&v[o][i]!=2&&v[o][i]!=3)
                {nr++;
                v[o][i]=3;
                }}
        o=x;
       /* for(i=y-1;i>=1&&o!=7;i++)
            {o++;
            if(v[o][i]!=1&&v[o][i]!=2&&v[o][i]!=3)
                {nr++;
                v[o][i]=3;
                o++;
                }}*/
        }
    cout<<nr;

return 0;
}
