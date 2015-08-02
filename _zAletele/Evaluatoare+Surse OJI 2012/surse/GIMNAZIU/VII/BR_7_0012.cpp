#include <fstream>
#include <iostream>
using namespace std;
long long x;
long n,i,xi,b[20],y,y1,y2,aa1,aa2,a1[100],a2[100],maxo=-1,p,k,ki,u;
int a[100010][21],c[100010][20];
int main()
{
ifstream f("unific.in");
ofstream g("unific.out");
f>>n;
for (i=1; i<=n; i++)
    {
    f>>x;
    while (x>0)
        {
        a[i][0]++;
        a[i][a[i][0]]=x%10;
        b[x%10]++;
        c[i][x%10]++;
        x=x/10;
        }
    for (y=1; y<=a[i][0]/2; y++)
            {
            xi=a[i][y];
            a[i][y]=a[i][a[i][0]-y+1];
            a[i][a[i][0]-y+1]=xi;
            }
    }
for (i=0; i<10; i++)
    if (maxo<b[i])
        {
        maxo=b[i];
        p=i;
        }
g<<p<<endl;
do
{
k=1;
i=0;
    do
    {
    i++;
    ki=0;
    for (y=0; y<10; y++)
        if ((c[i][y]>0)&&(c[i+1][y]>0))
            ki=1;
    }
    while ((ki==0)&&(i<n-1));
if (ki==1)
    {
    k=0;
    //a1,a2
    aa1=0;
    aa2=0;
    for (y=1; y<=a[i][0]; y++)
        if (c[i+1][a[i][y]]==0)
          {
          aa1++;
          a1[aa1]=a[i][y];
          }
    y1=1;
    while ((a1[y1]==0)&&(a1[y1+1]==0)&&(y1<aa1))
        y1++;
    if ((a1[y1+1]>0)&&(a1[y1]==0))
        y1++;
    for (y=1; y<=a[i+1][0]; y++)
        if (c[i][a[i+1][y]]==0)
          {
          aa2++;
          a2[aa2]=a[i+1][y];
          }
    y2=1;
    while ((a2[y2]==0)&&(a2[y2+1]==0)&&(y2<aa2))
        y2++;
    if ((a2[y2+1]>0)&&(a2[y2]==0))
        y2++;
    a[i][0]=aa1-y1+1+aa2-y2+1;
    for (y=1; y<=aa1-y1+1; y++)
        a[i][y]=a1[y+y1-1];
    for (y=aa1-y1+2; y<=aa1-y1+1+aa2-y2+1; y++)
        a[i][y]=a2[y+y2-1-aa1+y1-1];
    if ((a[i][0]==2)&&(a[i][1]==0)&&(a[i][2]==0))
        a[i][0]--;
    for (y=0; y<10; y++)
        c[i][y]=0;
    for (y=1; y<=a[i][0]; y++)
        c[i][a[i][y]]++;
    if (a[i][0]==0)
        {
        for (y=i; y<n-1; y++)
                {
                a[y][0]=a[y+2][0];
                for (u=1; u<=a[y][0]; u++)
                        a[y][u]=a[y+2][u];
                for (u=0; u<10; u++)
                    c[y][u]=c[y+2][u];
                }
        n=n-2;
        }
        else
        {
        for (y=i+1; y<n; y++)
                {
                a[y][0]=a[y+1][0];
                for (u=1; u<=a[y][0]; u++)
                        a[y][u]=a[y+1][u];
                for (u=0; u<10; u++)
                    c[y][u]=c[y+1][u];
                }
        n--;
        }
    }
}
while (k==0);
g<<n<<endl;
for (i=1; i<=n; i++)
    {
    for (y=1; y<=a[i][0]; y++)
        g<<a[i][y];
    g<<' ';
    }
f.close(); g.close();
return 0;
}
