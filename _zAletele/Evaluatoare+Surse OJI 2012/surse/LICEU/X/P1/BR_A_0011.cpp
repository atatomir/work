#include <iostream>
#include <fstream>

using namespace std;
int i,n,c,a[100000];
int v[100000];
int sol[100000];
int z=0;
int s=0;
void back(int k,int poz)
{
    if(k>=0 && k<=n)
    {
        if(sol[poz-1]<a[k] && !v[k])
        {
            s+=a[k];
            sol[poz]=a[k];
            v[k]=1;
            back(k+1,poz+1);
            v[k]=0;
            s-=a[k];
            back(k+1,poz);
        }
        else
        {
            back(k+1,poz);
        }
        if(k==n )
            if(s%c==0)
            {
                z++;
            }
    }
}
int main()
{
    ifstream f("calcule.in");
    ofstream g("calcule.out");
    sol[0]=0;
    f>>n>>c;
    for(i=0;i<n;i++)
    {
        f>>a[i];
        v[i]=0;
    }
    back(0,1);
    g<<endl<<z-c;
    return 0;
}
