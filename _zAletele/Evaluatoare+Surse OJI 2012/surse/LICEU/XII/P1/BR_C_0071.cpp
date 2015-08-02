#include <fstream>
#include<math.h>

using namespace std;
ifstream f("biperm.in");
ofstream g("biperm.out");
int valid(short i, short x[3][10001], int n)
{
    int aux=x[1][i];
    x[1][i]=x[0][i];
    x[0][i]=aux;
    for(int i=2;i<=n;i++)
        for(int j=i-1;j>=1;j--)
            if(x[0][j]==x[0][i] || x[1][j]==x[1][i])
                return 0;
    return 1;
}
int main()
{short n,i,j,a[3][10001],exista[10002]={0},exista2[10002]={0},mini=0,unde[2][10002],aux;
    f>>n;
    for(i=0;i<=1;i++)
        for(j=1;j<=n;j++)
        {
             f>>a[i][j];
        }
    for(i=1;i<=n;i++)
        if(exista[a[0][i]]==0)
            {
                exista[a[0][i]]=1;
                unde[0][a[0][i]]=i;
            }
        else
        {
            mini++;
            exista[a[0][i]]=2;
            unde[1][a[0][i]]=i;
        }



    g<<pow(2,mini);////habar n-am
    g<<mini<<"\n";//nr minim de mutari
    for(i=1;i<=n;i++)
    {

            if(valid(unde[0][i],a,n)==1)
            {


                aux=a[0][i]; a[0][i]=a[1][i]; a[1][i]=aux;
            }
            else if(valid(unde[1][i],a,n)==1)
            {

                aux=a[1][i]; a[1][i]=a[0][i];
                a[0][i]=aux;
            }

    }
    for(i=0;i<=1;i++)
    {
        for(j=1;j<=n;j++)
            g<<a[i][j]<<" ";
        g<<"\n";
    }

    return 0;
}
