#include <fstream>
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int main()
{
    int n,max1=0,t,k,d,z=0,v[100][100]={0},i,j,p1,p2;
    f>>n; f>>d; f>>k;
    for(i=1;i<=d;i++)
    {
        f>>p1; f>>p2;
        v[p1][p2]=1100;

    }
    for(i=1;i<=k;i++)
    {
        f>>p1; f>>p2;
        v[p1][p2]=1200;
    }

    t=0;
    for(i=1;i<=n;i++)
    {

        z=0;
        t++;
        for(j=1;j<=t;j++)
        {
            if (v[i][j]!=1200)
            {
              z++;
            }


        }
       if(z>max1)
         max1=z;
    }

    g<<max1;

f.close();
g.close();
    return 0;
}
