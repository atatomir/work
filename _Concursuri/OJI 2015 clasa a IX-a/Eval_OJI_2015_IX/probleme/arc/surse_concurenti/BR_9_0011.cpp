#include <iostream>
#include <fstream>
using namespace std;
ifstream f ("arc.in");
ofstream g ("arc.out");
int main()
{int v[10000], x=0,z,n,secvente,a, y=1, nrap=1, s[20], ss=0, s3=0;
  f>>a;
  f>>n;

  secvente=1;

    while (x<=n-1)
    {f>>z;
    v[x]=z;
    x++;
    }
x=0;
if (a==1)
    {
        while (x+1<=n-1)
    {
        if (v[x]!=v[x+1])
        {
            secvente++;
        }
    x++;
    }
    g<<secvente;
}

else
    {while (x!=n)
    {y=1;
        while (y!=n)
       {
           if (v[x]==v[y])
            {nrap++;}
            y++;}
            if (nrap<=2)
            {

                s[ss++]=v[x];


            }
            nrap=1;
    x++;
    }
    if (ss==0)
    {
        g<<"0";
    }
    else
    {g<<ss<<endl;
    while (ss!=0)
    {
    g<<s[s3++]<<endl;
    ss--;
    }
    }


    }


    return 0;
}
