#include <iostream>
#include<fstream>
using namespace std;
int main()
{unsigned int v[20][20],m,n,s,i,j,t,h,q,p,k,g,c,z,x,c1,c2,min;
signed y;
ifstream f("cartite.in.txt");
f>>p;f>>m;f>>n;

if(p==1)
{
for(i=1;i<=m;i++)
for(j=1;j<=n;j++)
v[i][j]=0;

f>>h;f>>t; //v[h][t] locatia cartitei ;
v[h][t]=2;

f>>k;
for(q=1;q<=k;q++)
{f>>i;f>>j;v[i][j]=1;f>>c;
 if(c==1)
    {
    for(z=1;z>=m;z++)
    for(x=1;x<=n;j++)
    {if((z==i-1) && (x==j))v[z][x]=1;
    if(z==i && x==j-1)v[z][x]=1;
    if(z==i+1 && x==j)v[z][x]=1;
    if(z==i && x==j+1)v[z][x]=1;
    }
    }

    if(c==2)
    {
    for(z=1;z>=m;z++)
    for(x=1;x<=n;j++)
    {if(z==i-1 && x==j)v[z][x]=1;
    if(z==i && x==j-1)v[z][x]=1;
    if(z==i+1 && x==j)v[z][x]=1;
    if(z==i && x==j+1)v[z][x]=1;
    if(z==i-2 && x==j)v[z][x]=1;
    if(z==i+2 && x==j)v[z][x]=1;
    if(z==i-1 && x==j-1)v[z][x]=1;
    if(z==i-1 && z==j+1)v[z][x]=1;
    if(z==i && x==j-2)v[z][x]=1;
    if(z==i && x==j+2)v[z][x]=1;
    if(z==i+1 && x==j-1)v[z][x]=1;
    if(z==i+1 && x==j+1)v[z][x]=1;
    }
    }
}


f>>g;
for(q=1;q<=g;q++)
{f>>i;f>>j;
if(v[i][j]!=1)v[i][j]=3;
f>>i;f>>j;
if(v[i][j]!=1)v[i][j]=3;
}

min=201;
for(i=1;i<=m;i++)
{for(j=1;j<=n;j++)
{if(v[i][j]!=1)
{y=j-t;y=(y*y)/y;
s=y+s;
y=i-h;y=(y*y)/y;
s=y+s;
if(s<min)
{min=s;
c1=i;
c2=j;
}
}
}
}
ofstream g("cartite.out.txt");
g<<c1<<" "<<c2<<" "<<s;

}
return 0;
}
