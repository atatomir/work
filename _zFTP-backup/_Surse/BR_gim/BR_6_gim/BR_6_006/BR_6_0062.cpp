#include <fstream>

using namespace std;
long n,x[100001],i,m,s;
int main()
{   ifstream f("munte.in");
    ofstream g("munte.out");
    f>>n;
    for(i=1;i<=n;i++)
     f>>x[i];
     //a) secvente munte
    for(i=1;i<=n;i++)
    {

        if(x[i]==5)
        m=1;
        if(x[i]>5)
        {
           while(n>5)
            {
            n=n/2;
            s=s+2;
            m=s;}
        }
    }
    g<<m<<'\n';
    f.close();
    g.close();
    return 0;
}
