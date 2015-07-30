// prof. Carmen Popescu
// colegiul National "Gheorghe Lazar" Sibiu

#include <fstream>
#include <bitset>

using namespace std;

ifstream f("cub2.in");
ofstream g("cub2.out");

int m=2;
bitset<8000005> pr;

void prim(int n)
{
    int i=1,j;
    for (i=1;i<=n;i++)
        pr[i]=true;
    pr[1]=false;
    for (i=2;i<=n/2;i++)
        if (pr[i])
        {
            j=i+i;
            while (j<=n)
            {
                pr[j]=false;
                j+=i;
            }
        }
}

int main()
{
    int v,n,n2,k,z,p,i,j,f1=0,f2=0,f3=0,f4=0;
    m=2; pr[1]=2; pr[2]=3;
    f>>v;
    f>>n>>k;
    n2=n*n;
    prim(n2*n);
    if (v==1)
    {
        z=1;
        v=0;
        while (k-v>n2)
        {
            z++;
            v=v+n2;
        }
        if (z%2==1)
        {
            for (p=1;;p++)
            {
                for (j=p;j<=n-p+1;j++)
                {
                    v++;
                    if (v==k)
                    {
                        g<<p<<" "<<j<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
                for (i=p+1;i<=n-p+1;i++)
                {
                    v++;
                    if (v==k)
                    {
                        g<<i<<" "<<n-p+1<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
                for (j=n-p;j>=p;j--)
                {
                    v++;
                    if (v==k)
                    {
                        g<<n-p+1<<" "<<j<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
                for (i=n-p;i>=p+1;i--)
                {
                    v++;
                    if (v==k)
                    {
                        g<<i<<" "<<p<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
            }
        }
        else
        {
            v=v+n2+1;
            for (p=1;;p++)
            {
                for (j=p;j<=n-p+1;j++)
                {
                    v--;
                    if (v==k)
                    {
                        g<<p<<" "<<j<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
                for (i=p+1;i<=n-p+1;i++)
                {
                    v--;
                    if (v==k)
                    {
                        g<<i<<" "<<n-p+1<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
                for (j=n-p;j>=p;j--)
                {
                    v--;
                    if (v==k)
                    {
                        g<<n-p+1<<" "<<j<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
                for (i=n-p;i>=p+1;i--)
                {
                    v--;
                    if (v==k)
                    {
                        g<<i<<" "<<p<<" "<<z<<"\n";
                        g.close();
                        return 0;
                    }
                }
            }

        }
    }
    else
    {
        for (z=1;z<=n;z++)
            if (z%2==1)
            {
                p=1; v=(z-1)*n2;

                // coltul st-sus
                v++;
                if (pr[v]) { f1++; f4++; }

                for (j=p+1; j<=n-p; j++)
                {
                    v++;
                    if (pr[v]) f1++;
                }
                // coltul dreapta sus
                v++;
                if (pr[v]) { f1++; f2++; }

                for (i=p+1; i<=n-p; i++)
                {
                    v++;
                    if (pr[v]) f2++;
                }
                // coltul dreapta jos
                v++;
                if (pr[v]) { f2++; f3++; }

                for (j=n-p; j>=p+1; j--)
                {
                    v++;
                    if (pr[v]) f3++;
                }
                // coltul stanga-jos
                v++;
                if (pr[v]) { f3++; f4++; }

                for (i=n-p; i>=p+1; i--)
                {
                    v++;
                    if (pr[v]) f4++;
                }

                v=v+n2-(4*n-4);
            }
            else
            {
                p=1;
                v=v+n2-(4*n-4);
                for (i=p+1; i<=n-p; i++)
                {
                    v++;
                    if (pr[v]) f4++;
                }
                // coltul stanga jos
                v++;
                if (pr[v]) { f4++; f3++; }

                for (j=p+1; j<=n-p; j++)
                {
                    v++;
                    if (pr[v]) f3++;
                }

                // coltul dreapta jos
                v++;
                if (pr[v]) { f3++; f2++; }

                for (i=n-p; i>=p+1; i--)
                {
                    v++;
                    if (pr[v]) f2++;
                }

                // coltul dreapta sus
                v++;
                if (pr[v]) {f2++; f1++; }

                for (j=n-p; j>=p+1; j--)
                {
                    v++;
                    if (pr[v]) f1++;
                }

                // coltul stanga sus
                v++;
                if (pr[v]) { f1++; f4++; }
            }
        g<<f1<<"\n"<<f2<<"\n"<<f3<<"\n"<<f4<<"\n";
        g.close();

    }
    return 0;
}
