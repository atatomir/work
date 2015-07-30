#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("triunghi.in");
    ofstream g("triunghi.out");
    int v,n,k,i,j;
    f>>v;f>>n;f>>k;
    long a[47],aux;
    for(i=1;i<=n;i++)
        f>>a[i];
    for(i=1;i<=n-1;i++)
        for(j=i+1;j<=n;j++)
            if(a[j]<a[i])
                {aux=a[i];
                a[i]=a[j];
                a[j]=aux;}
    if(v==1)
        {long b[47];
        b[1]=a[1];b[2]=a[1];
        i=3;
        while(i<=k)
            {b[i]=b[i-1]+b[i-2]+1;
            i++;}
        for(i=1;i<=k;i++)
            g<<b[i]<<" ";
        }
    else
        {long b[48],nr;
        int l;
        for(i=1;i<=n;i++)
            b[i]=a[i];
        i=n;
        while(i<=k)
            {nr=b[2]-b[1]-1;
            for(j=2;j<=i-1;j++)
                if((b[j]+nr)>=b[j+1])
                    nr=b[j+1]-b[j]-1;
            b[i+1]=nr;
            int ok=0;
            while(ok==0)
                {ok=1;
                for(l=1;l<=i;l++)
                    if(b[l]>b[l+1])
                        {aux=b[l];
                        b[l]=b[l+1];
                        b[l+1]=aux;
                        ok=0;}}
            i++;}
       for(i=2;i<=k+1;i++)
         g<<b[i]<<" ";}
    return 0;
}
