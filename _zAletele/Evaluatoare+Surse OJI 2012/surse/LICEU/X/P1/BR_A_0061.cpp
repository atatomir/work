#include <fstream>

using namespace std;

#define NMAX 100001
#define SMAX 200000000

int s[NMAX], a[SMAX];

int main()
{
    int i,j,k,n,sum=0,contor=0,min,max;
    ifstream f("calcule.in");
    ofstream g("calcule.out");
    f>>n>>k;
    for(i=1;i<=n;i++)
    {
        f>>s[i];
    }
    cout<<"6";
    a[0]=0;
    a[s[1]]=1;
    for(i=1;i<=n;i++)
    {
        a[s[i]]++;
        if(s[i]%k==0) contor++;
        sum=s[i];
        for(j=i+1;j<=n;j++)
        {
            a[sum+s[j]]++;
            if((sum+s[j])%k==0) contor++;
            sum=sum+s[j];
        }
    }
    g<<'\n'<<contor%20011;
}
