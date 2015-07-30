// prof. Carmen Popescu
// colegiul National "Gheorghe Lazar" Sibiu

#include <fstream>

using namespace std;

ifstream f("cub2.in");
ofstream g("cub2.out");

int pr[1000000],m=2;

int prim(int x)
{
    int i=1;
    if (x==1) return 0;
    if (x==2 || x==3)
        return 1;
    while (pr[i]<=x/2)
    {
        if (x%pr[i]==0)
            return 0;
        i++;
    }
    m++;
    pr[m]=x;
    return 1;
}

int main()
{
    int v,n,n2,k,x,y,z,p,i,j,f1=0,f2=0,f3=0,f4=0;
    m=2; pr[1]=2; pr[2]=3;
    f>>v;
    f>>n>>k;
    n2=n*n;
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
                k=prim(v);
                if (k) { f1++; f4++; }

                for (j=p+1; j<=n-p; j++)
                {
                    v++;
                    k=prim(v);
                    if (k) f1++;
                }
                // coltul dreapta sus
                v++;
                k=prim(v);
                if (k) { f1++; f2++; }

                for (i=p+1; i<=n-p; i++)
                {
                    v++;
                    k=prim(v);
                    if (k) f2++;
                }
                // coltul dreapta jos
                v++;
                k=prim(v);
                if (k) { f2++; f3++; }

                for (j=n-p; j>=p+1; j--)
                {
                    v++;
                    k=prim(v);
                    if (k) f3++;
                }
                // coltul stanga-jos
                v++;
                k=prim(v);
                if (k) { f3++; f4++; }

                for (i=n-p; i>=p+1; i--)
                {
                    v++;
                    k=prim(v);
                    if (k) f4++;
                }

                for (i=1; i<=n2-(4*n-4); i++)
                {
                    v++;
                    prim(v);
                }
            }
            else
            {
                p=1;
                for (i=1; i<=n2-(4*n-4); i++)
                {
                    v++;
                    prim(v);
                }


                for (i=p+1; i<=n-p; i++)
                {
                    v++;
                    k=prim(v);
                    if (k) f4++;
                }
                // coltul stanga jos
                v++;
                k=prim(v);
                if (k) { f4++; f3++; }

                for (j=p+1; j<=n-p; j++)
                {
                    v++;
                    k=prim(v);
                    if (k) f3++;
                }

                // coltul dreapta jos
                v++;
                k=prim(v);
                if (k) { f3++; f2++; }

                for (i=n-p; i>=p+1; i--)
                {
                    v++;
                    k=prim(v);
                    if (k) f2++;
                }

                // coltul dreapta sus
                v++;
                k=prim(v);
                if (k) {f2++; f1++; }

                for (j=n-p; j>=p+1; j--)
                {
                    v++;
                    k=prim(v);
                    if (k) f1++;
                }

                // coltul stanga sus
                v++;
                k=prim(v);
                if (k) { f1++; f4++; }
            }
        g<<f1<<"\n"<<f2<<"\n"<<f3<<"\n"<<f4<<"\n";
        g.close();

    }
    return 0;
}
