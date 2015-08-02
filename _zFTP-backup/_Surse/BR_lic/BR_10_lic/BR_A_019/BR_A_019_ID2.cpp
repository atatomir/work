#include <iostream>
#include <fstream>

using namespace std;
int varianta,n,k,xk;
long long S[47],rez[47];

ifstream in("triunghi.in");
ofstream out("triunghi.out");

void show()
{
    int i;
    for(i=1;i<=xk ;i++)
        out<<rez[i]<<" ";

}

int valid(long long x)
{
    int i,j,l=0;
    for(i = 1;i<=xk;i++)
        for(j=1;j<=xk;j++)
            if(i!=j)
            {
                if(rez[i]+rez[j]>=x && rez[i]+x>=rez[j] && rez[j]+x>=rez[i])
                    l++;
            }

    if(l==(xk*(xk-1))/2)
        return 0;
    return 1;
}

void backt()
{
    long long i=1;
    while(i!=0)
    {
        if(xk==k)
        {
            show();
            i=0;
        }else
        if(valid(i))
            {xk++;rez[xk]=i;i++;}
        else
           {
               rez[xk]=0;
               xk--;
            }



    }
}

int main()
{
    in>>varianta>>n>>k;
    int i;
    for(i=1;i<=n;i++)
        in>>S[i];
    int j;
    long long aux;
    for(i=1;i<=n-1;i++)
        for(j=i+1;j<=n;j++)
            if(S[j]<S[i])
            {
                aux = S[i];
                S[i] = S[j];
                S[j] = aux;
            }
    switch (varianta)
    {
        case 1:
            rez[1] = rez[2] = S[1];
            xk=3;
            backt();
            //show();
        break;

        case 2:

        break;
    }

}
