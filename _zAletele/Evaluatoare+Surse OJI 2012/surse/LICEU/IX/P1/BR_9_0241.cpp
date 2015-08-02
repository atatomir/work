#include<iostream>
#include<fstream>
#define nmax 1000
#define pmax 100
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int main()
{int N[nmax],D[pmax],K[50],P,i,x[nmax],y[nmax],t[nmax],z[nmax],j,o=0,u=0;
for(i=1;i<=nmax;i++)
{f>>N[i];cout<<" ";
f>>D[i];cout<<" ";
f>>K[i];cout<<"\n";}
for(i=2;i<=N[i];i++)
for(j=2;j<=N[i];j++)
N[i]=(N[i]+(N[i+1]))/2;
for(i=1;i<=D[i];i++)
f>>x[i];f>>y[i];
for(i=1;i<=K[i];i++)
f>>z[i];f>>t[i];
for(i=1;i<=N[i];i++)
    if(x[i]==z[i]&&y[i]==t[i])
        g<<"nu sunt bune datele"<<"\n";
    if(x[i]==x[i+1])
        g<<"nu pot sta 2 dame aici"<<"\n";
for(i=1;i<=D[i];i++)
    while(x[i])
        if(x[i]!=z[i]&&y[i]!=t[i])
            {x[i]=x[i-1];
        o++;}
    while(x[i]<N[i])
        if(x[i]!=z[i]&&y[i]!=t[i])
        {
            x[i]=x[i+1];o++;
        }
    while(y[i])
        if(x[i]!=z[i]&&y[i]!=t[i])
            {y[i]=y[i-1];
            u++;}
    while(y[i]<N[i])
        if(x[i]!=z[i]&&y[i]!=t[i])
            {
                y[i]=y[i+1];u++;
            }
 P=u+o;g<<P;
    f.close();
    g.close();
    return 0;
}
