
#include<fstream>
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");

#define Max 705
#define MAX 1005

int main()
{int n,d,k,i,x[MAX],y[MAX],a[Max][Max],z[MAX],t[MAX],j,max,m=0,xx=0,q=0,r=0,p=0;
    f>>n>>d>>k;
    for(i=1;i<=d;i++)
       {
           f>>x[i]>>y[i];
           a[x[i]][y[i]]=2;
       }
    for(i=1;i<=k;i++)
       {
           f>>z[i]>>t[i];
           a[z[i]][t[i]]=3;
       }
    for(i=1;i<=n;i++)
          {
              for(j=1;j<=i;j++)
                 if(a[i][j]!=2&&a[i][j]!=3)
                 a[i][j]=0;
              for(j=i;j<=n;j++)
                 if(a[i][j]!=2&&a[i][j]!=3)
                 a[i][j]=1;
          }
    for(i=1;i<=n;i++)
    {
        max=0;
        for(j=1;j<=n;j++)
           if(a[i][j]==0||a[i][j]==2)
             max++;
        if(max>m)
          m=max;
    }
    g<<m+1<<endl;
    for(i=1;i<=n;i++)
       for(j=1;j<=n;j++)
              if(a[i][j]==2)
              {
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q-1][r]==0)
                        {
                            a[q-1][r]=4;
                            q--;
                            xx=0;
                        }
                       if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q+1][r]==0)
                        {
                            a[q+1][r]=4;
                            q++;
                            xx=0;
                        }
                    if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q][r-1]==0)
                        {
                            a[q][r-1]=4;
                            r--;
                            xx=0;
                        }
                        if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q][r+1]==0)
                        {
                            a[q][r+1]=4;
                            r++;
                            xx=0;
                        }
                        if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q-1][r-1]==0)
                        {
                            a[q-1][r-1]=4;
                            q--;
                            r--;
                            xx=0;
                        }
                        if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q+1][r+1]==0)
                        {
                            a[q+1][r+1]=4;
                            q++;
                            r++;
                            xx=0;
                        }
                        if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q-1][r+1]==0)
                        {
                            a[q-1][r+1]=4;
                            q--;
                            r++;
                            xx=0;
                        }
                      if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  q=i;
                  r=j;
                  do
                  {
                      xx=1;
                      if(a[q+1][r-1]==0)
                        {
                            a[q+1][r-1]=4;
                            q++;
                            r--;
                            xx=0;
                        }
                        if(q<0||r<0||q>n||r>n)
                         xx=1;
                  }
                  while(xx==0);
                  }
    for(i=1;i<=n;i++)
       for(j=1;j<=n;j++)
          if(a[i][j]==4)
            p++;
g<<p+4;
return 0;
}
