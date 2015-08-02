#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int n,i,j,b,sec=1,poz[10000],k,s,p,aux=0;
    ifstream f("clepsidru.in.txt");
    ofstream g("clepsidru.out.txt");
    f>>n;
    f>>b;
      for(i=1;i<=b;i++)
        {for(j=i;j<=b;j++)
            if(j==b)
                sec++;}
    g<<sec;
    /*f>>k;
    poz[1]=3;
    for(i=2;i<=n*2;i++)
        poz[i]=0;
    for(i=1;i<=k;i++)
    f>>s>>p;
        if(p==1)
            {for(j=0;j<=s;i++)
               {poz[1]--;
                poz[2]=0;
                if(j>=1)
                    poz[3]=1;
                if(j>=2)
                    poz[4]++;}}
        else
            {for(j=0;j<=k;j++)
                {poz[4]--;
                poz[3]=1;
                if(j>0)
                    poz[1]++;}}
    for(i=1;i<=4;i++)
        g<<poz[i];*/
    return 0;
}
