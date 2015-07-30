#include <iostream>
#include<fstream>
using namespace std;
int main()
{int a[201][201],b[201][201],t[201][201],nodi[100],vizit[100], nodj[100],v,u=0,m,n,g,k,p,lc,cc,i,j,lv[51],cv[51],rv[51],gal1[101],gal2[101],gac1[101],gac2[101],min=10000,mini=10000,dif,minl,minc,dif2,s[100],z[100],q=0;
ifstream f("cartite.in");
ofstream fout("cartite.out");
f>>p; // poate fi 1 sau 2
f>>m; f>>n; //diimensiuni zona
f>>lc; f>>cc; // linie cartita si coloana
f>>k; // nr de vulpi
for(i=1;i<=k;i++)
    {
        f>>lv[i];
        f>>cv[i];
        f>>rv[i];
    }// coloana linie si raza vulpe
f>>g; //nr de galerii
for(i=1;i<=g;i++)
    {
        f>>gal1[i];
        f>>gac1[i];
        b[gal1[i]][gac1[i]]=1;
        f>>gal2[i];
        f>>gac2[i];
        b[gal2[i]][gac2[i]]=1;
    }
for(i=1;i<=g;i++)
    {
        dif=gal1[i]-lc;
        if(dif<0)
            dif=dif*(-1);
        s[i]=dif;
        z[i]=1;
        if(dif<=min )
            {min=dif;
            minl=gal1[i];}
        dif=gal2[i]-lc;
        if(dif<0)
            dif=dif*(-1);
        if(s[i]>dif)
            {s[i]=dif;
            z[i]=2;}
        if(dif<=min )
            {min=dif;
            minl=gal2[i];}
    }
for(i=1;i<=g;i++)
    {
        if(s[i]==min)
            {
                if(z[i]==1)
                    {
                        dif2=gac1[i]-cc;
                        if(dif2<0)
                            dif2=dif2*(-1);
                        if(dif2<mini)
                            {
                                mini=dif2;
                                minc=gac1[i];
                            }
                    }
                else
                    {
                        dif2=gac2[i]-cc;
                        if(dif2<0)
                            dif2=dif2*(-1);
                        if(dif2<mini)
                            {
                                mini=dif2;
                                minc=gac2[i];
                            }
                    }


            }
    }
if(p==1)
fout<<minl<<' '<<minc<<' '<<min+mini; // cea mai apropiata coloana si linie

for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
            if(b[i][j]==1)
                {u++;
                b[i][j]=u;
                nodi[u]=i; nodj[u]=j;}


for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
            if(b[i][j]!=0)
                for(v=1;v<=g;v++)
                    if(i==gal1[v] && j==gac1[v])
                        {
                            t[b[i][j]][b[gal2[v]][gac2[v]]]=1;
                            t[b[gal2[v]][gac2[v]]][b[i][j]]=1;
                        }

if(p==2)
{fout<<nodi[1]<<nodj[1]<<endl;
vizit[1]=1;
for(i=1;i<=u;i++)
vizit[i]=0;
for(i=2;i<=u;i++)
    for(j=1;j<=u;j++)
        if(t[i][j]==1 && vizit[j]!=1)
            {fout<<nodi[j]<<nodj[j]<<endl; vizit[j]=1;}
}




fout.close();
f.close();
return 0;
}
