#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;
long n,i,b[100010],k,x;
char a[100010];
int main()
{
FILE*f;
f=fopen("compar.in","r");
ofstream g("compar.out");
a[1]=getc(f);
while ((a[n+1]=='>')||(a[n+1]=='<'))
        {
        n++;
        a[n+1]=getc(f);
        }
g<<n+1<<endl;
n++;
for (i=1; i<=n; i++)
    b[i]=i;
do
{
k=1;
for (i=1; i<n; i++)
        {
        if ((b[i]>b[i+1])&&(a[i]=='<'))
            {
            k=0;
            x=b[i];
            b[i]=b[i+1];
            b[i+1]=x;
            }
        if ((b[i]<b[i+1])&&(a[i]=='>'))
            {
            k=0;
            x=b[i];
            b[i]=b[i+1];
            b[i+1]=x;
            }
        }
}
while (k==0);
for (i=1; i<=n; i++)
    g<<b[i]<<' ';
fclose(f);
g.close();
return 0;
}
