#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int d=0,i,v1,n,k,j,aux=0,z,min=300000000,v[47],s[47];
    ifstream f("triunghi.in");
    ofstream g("triunghi.out");
    f>>v1>>n>>k;
    if(v1==1)
        {for(i=1;i<=n;i++)
            f>>v[i];
        for(i=1;i<=n;i++)
            if(v[i]<=min)
                min=v[i];
        s[1]=min;
        s[2]=min;
        i=1;
        while(i<=k)
            {d=s[i]+s[i+1];
            s[i+2]=d+1;
            i++;
            d=0;}
        for(i=1;i<=k;i++)
            g<<s[i]<<' ';}
    if(v1==2)
        {for(i=1;i<=n;i++)
            f>>v[i];
        for(i=1;i<=n;i++)
            for(j=i;j<=n;j++)
                if(v[i]>v[j])
                   {aux=v[j];
                   v[j]=v[i];
                   v[i]=aux;}
        z=n;
        while(z<k)
            {for(i=1;i<=z;i++)
                d=d+v[i];
            z++;
            v[z]=d;}
        for(i=1;i<=z;i++)
            g<<v[i]<<' ';


       }


    return 0;
}
