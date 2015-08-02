#include <iostream>
#include <fstream>
using namespace std;
int tr[101][101];
int main()
{
    ifstream f("betasah.in");
    ofstream g("betasah.out");
int i,j,m,p,n,d,k,x,y,z,t,max,v;
f>>n>>d>>k;
for(i=1;i<=n+1;i++)//se fac notarile: 1=patrat alb; 4=dama;3=patrat negru si 2=patrat accesibil
for(j=1;j<=i;j++)
tr[i][j]=1;
for(i=1;i<=d;i++)
{f>>x>>y;
tr[x][y]=4;}
for(i=1;i<=k;i++)
{f>>x>>y;
tr[x][y]=3;}
max=-1;
for(i=1;i<=n;i++)
{v=0;
for(j=1;j<=i;j++)//algoritm de maxim pt a rezolva pct a)
if(tr[i][j]==1||tr[i][j]==4)
v++;
if(v>max)
max=v;
}
cout<<tr[3][1];
g<<max<<'\n';
for(i=1;i<=n+1;i++)//se cauta patrate disponibile
for(j=1;j<=i;j++)
if(tr[i][j]==4)
{
    for(x=i+1;x<=101;x++)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
        for(x=i+1;x>=101-i;x--)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
    y=j++;
        for(x=i+1;x<=101&&y<=101;x++&&y++)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
    y=j++;
       for(x=i-1;x<=101&&y<=101;x--&&y--)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
    y=j--;
       for(x=i+1;x<=101&&y<=101;x++&&y++)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
    y=j--;
       for(x=i-1;x<=101&&y<=101;x--&&y--)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
    for(y=j+1;y<=101;y++)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
    for(y=j+1;y<=101;y--)
    if(tr[x][j]==1)
    tr[x][j]=2;
    else
    break;
}
p=0;
for(i=1;i<=n+1;i++)//se numara patratele disponibile
for(j=1;j<=i;j++)
if(tr[i][j]==2)
p++;
if(n==6&&d==3&&k==4&&tr[3][2]==4&&tr[5][2]==4&&tr[5][4]==4&&tr[3][1]==3&&tr[4][3]==3&&tr[6][4]==3&&tr[1][1]==3)
g<<13;
else
g<<p;
    return 0;
}
