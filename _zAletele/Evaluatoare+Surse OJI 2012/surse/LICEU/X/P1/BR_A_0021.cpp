#include <iostream>
#include<fstream>

using namespace std;
int a[100],n,g=2,min[100],minim=100;

int deter ()
{
    int ee,e;
    for (e=g;e<=n;e++)
        {
           // cout<<min[e]<<' ';
            if (min[e]<minim && min[e]!=0)
            {
                minim=min[e];
                ee=e;
            }
        }
    return ee;
}
int minimf (int i,int j,int *min)
{
    min[j]=a[j]-a[i];
    return min[j];
}

int main()
{
    int i,j,k=0;
    ifstream f("calcule.in");
    f>>n;
    for (i=1;i<=n;i++)
        f>>a[i];
    for (i=1;i<=n;i++)
    {
        minim=100;
        if (a[i]!=0)
        {
            for (j=g;j<=n;j++)
            {
                min[j]=0;
                if (a[i]<a[j])
                {
                    min[j]=minimf(i,j,min);
                }
            }
        }
        b[k++]=a[deter ()];


    }

}
