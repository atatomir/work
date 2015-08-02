#include <fstream>

using namespace std;

fstream f("fractii2.in",ios::in);
fstream g("fractii2.out",ios::out);

const long long nr=100003;

int p,n,i,nr1;
long long a,b,y;

int main()
{
    f>>p;
    f>>n;
    if (p==1)
    {
        for (i=1;i<n;i++) g<<i<<" ";
        g<<n-1;
    }
    else
    {
        if ((n==2)||(n==3)) g<<"1";
            else
            {
                a=1;b=1;
                nr1=4;
                while (nr1<=n)
                {
                    y=(a+b)%nr;
                    a=b;
                    b=y;
                    nr1++;
                }
                g<<b;
            }
    }
    f.close();g.close();
    return 0;
}
