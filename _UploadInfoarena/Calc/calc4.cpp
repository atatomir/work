///prof.Gorea Claudiu-Cristian
///Colegiul National Al. Papiu Ilarian Tg-Mures
///complexitate 2^N = 50p
#include <fstream>

using namespace std;
#define modulo 1000000007
ifstream fin ("calc.in");
ofstream fout("calc.out");
int p,n,i,j,l,fib[100002], a[100002],b[100002],sol,imp,ok,k0;
char c;
int main()
{
    fin>>p;
    fin>>n;
    if (p==1)
    {
        fib[1]=1;
        fib[2]=2;
        for(i=3;i<=n;i++)
            fib[i]=(fib[i-1]+fib[i-2])%modulo;
        fout<<fib[n];   fout<<endl;
    }
    else
    {
        ///cerinta 2;
        for(i=1;i<=n;i++)
        {
            fin>>c;
            a[i]=c-'0';
            b[i]=a[i];
        }
        sol=0;
        while(sol==0)
        {
            ///scaderea din a
            if(a[n]==1) a[n]--, imp=0;
                else a[n]=1, imp=1;
            if (imp==1)
            {
                i=n-1;
                while(a[i]==0 && i>=1)
                {
                    a[i]=1;  i--;
                }
                if (i>0)  a[i]--;
                    else sol=-1; ///nu mai am din ce sa scad... -1 ca solutie
            }
            ok=1; ///presupun secventa ok...
            i=1;
            while(i<=n && ok)
            {
                k0=0;
                while(a[i]==0 && i<=n)    i++, k0++;

                if (k0%2==1) ok=0; ///secventa impara de 0-uri

                while(a[i]==1 && i<=n)    i++;
            }
            if (sol==0 && ok==1) sol=1;
        }
        if (sol==-1) fout<<"-1\n";
            else {
                    for(i=1;i<=n;i++)
                        fout<<a[i];
                    fout<<endl;
                }
        ///ziua urmatoare.............
        sol=0;
        while(sol==0)
        {
            b[n]++;
            i=n;
            while(b[i]==2)
            {
                b[i]=0;
                b[i-1]++;
                i--;
            }
            if (b[0]>0) sol=-1; ///nu mai am ce aduna....
            else
            {
                ok=1; ///presupun secventa ok...
                i=1;
                while(i<=n && ok)
                {
                    k0=0;
                    while(b[i]==0 && i<=n)    i++, k0++;

                    if (k0%2==1) ok=0; ///secventa impara de 0-uri

                    while(b[i]==1 && i<=n)    i++;
                }
                if (ok) sol=1;
            }
        }
        if (sol==-1) fout<<"-1\n";
            else {
                    for(i=1;i<=n;i++)
                        fout<<b[i];
                    fout<<endl;
                }
    }
    return 0;
}
