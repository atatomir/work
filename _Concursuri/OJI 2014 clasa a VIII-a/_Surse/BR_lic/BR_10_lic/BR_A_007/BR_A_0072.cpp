#include <iostream>
#include<fstream>
using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");

long long x;
int cnt=0;
long long a[47];
long long b[47];
int main()
{
    long long mn;
    int i=0;
    int v,n,k;
    f>>v>>n>>k;


        while(f>>x)
        {
            cnt++;
            b[cnt]=x;
           if(x<mn)
           {
               mn=x;
           }
        }

    a[1]=mn;
    a[2]=mn;
    if(v==1)
    {
        long long p=1;
        for(i=3;i<=k;i++)
                {
                    a[i]=a[i-1]+a[i-2]+p;
                    p=p*3+5;

                }
                        for(i=1;i<=k;i++)
                            {
                        g<<a[i]<<" ";

                            }
    }
long long p2=135;
int sch;
int aux;
if(v==2)
{
    do
    {
        sch=1;
        for(i=1;i<cnt;i++)
        {
            if(b[i]>b[i+1])
            {
                aux=b[i];
                b[i]=b[i+1];
                b[i+1]=aux;
                sch=0;
            }
        }
    }while(sch);
    for(i=cnt+1;i<=k;i++)
    {
       b[i]=b[i-1]+b[i-2]+p2;
       p2=p2*2+39;
    }
    for(i=1;i<=k;i++)
    {
        g<<b[i]<<" ";
    }

}




    f.close();
    g.close();
    return 0;
}
