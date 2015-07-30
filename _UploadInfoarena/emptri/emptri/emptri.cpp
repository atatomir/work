#include <fstream>
#define MAXN 1000002
#define tip int
using namespace std;
ifstream f("emptri.in");
ofstream g("emptri.out");
tip n,i,j,m,k,fi[MAXN];
long long sol;
int main()
{
    f>>n;
    sol=1;
    for(i=2;i<=n;i+=2)
        fi[i]=2;
    for(i=3;i*i<=n;i+=2)
    if(!fi[i])
    {
        fi[i]=i;
        for(j=i*i;j<=n;j+=2*i)
            fi[j]=i;
    }
    for(;i<=n;i+=2)
        if(!fi[i])
            fi[i]=i;
    for(i=2;i<=n;i++)
    {
        if(fi[i]==i){fi[i]=i-1;sol+=2LL*(i-1);continue;}
        k=fi[i];j=i;m=1;
        while(j%k==0){j/=k;m*=k;}
        if(j==1)fi[i]=(k-1)*(m/k);
        else fi[i]=fi[m]*fi[j];
       	sol+=2LL*fi[i];
    }
    g<<sol;
    return 0;
}
