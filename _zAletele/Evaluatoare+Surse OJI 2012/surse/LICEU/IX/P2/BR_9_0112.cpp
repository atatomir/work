#include<fstream>
using namespace std;
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");

#define MAX 1005

int main()
{
     int n,b,k,i,j,s[MAX],p[MAX],poz1[MAX],poz2[MAX];
    f>>n>>b;
    f>>k;
    for(i=1;i<=k;i++)
       f>>s[i]>>p[i];
    g<<(b-1)*n<<"\n";
    for(i=1;i<=p[i];i++)
    {
        if(i%2==1)
        {
            poz1[i]=b;
        poz2[i]=0;
       for(j=1;j<=s[i];j++)
          {
              poz1[i]--;
              if(j>1)
                poz2[i]=1;
          }
                g<<poz1[i]+1<<" "<<poz2[i]<<"\n";
        }
        poz1[i]=b+1-n;
        poz2[i]=0;
        if(i%2==0)
        {
           for(j=1;j<=s[i];j++)
           {
               if(j>1)
                 poz1[i]--;
               if(j>2)
                 poz2[i]++;
           }
           g<<poz1[i]-2<<" "<<poz2[i]+1<<"\n";
        }
    }
    return 0;
}
