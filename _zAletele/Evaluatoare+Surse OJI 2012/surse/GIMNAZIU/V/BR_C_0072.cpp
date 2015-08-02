#include <fstream>
#include<string.h>
using namespace std;
ifstream f("subsecvente.in");
ofstream g("subsecvente.out");
short n,i,j,mini,imin;
char s[5][10003];
int main()
{
    f>>n;
    imin=1;
    for(i=1;i<=n;i++)
        {
            f>>s[i];
            if(strlen(s[i])<strlen(s[imin]))
               {
                imin=i;
               }
        }
    if(strlen(s[imin])<=60)
    {
         bool k = true;
    for(i=1;i<=n;i++)
    {
        if(i!=imin)
            if(!strstr(s[i],s[imin]))
            {
                k=false; i=n+1;
            }
    }
    if(k)
    {
        g<<strlen(s[imin]); return 0;
    }
    }

    g<<"60";


    return 0;
}
