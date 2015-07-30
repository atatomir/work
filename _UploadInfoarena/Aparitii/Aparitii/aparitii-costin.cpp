#include <cstdio>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
#define nmax 2000100

FILE *f,*g;
string S,P,a;
int Z[2][nmax];
int ans[nmax];

void Z_algorithm(int z)
{
    int L,R,i,j,k,n = a.size(),ind,d;
    L = R = -1;


    for (i=1;i<n;i++)
    {
        if (i>R)
        {
            if (a[0] == a[i])
            {
                L = i;
                for (j=0,k=i,R=i-1;k<n && a[j] == a[k];j++,k++) Z[z][i]++,R++;
            }
            else
                Z[z][i] = 0;
        }
        else
        {
            ind = i-L;
            if (Z[z][ind]<R-i+1)
            {
                Z[z][i] = Z[z][ind];
            }
            else
            {
                Z[z][i] = R-i+1;

                L = i;
                d =Z[z][i];
                for(;R+1<n && a[R+1] == a[d];R++,d++) Z[z][i]++;
            }
        }
    }
}

int main()
{
    //freopen("aparitii.in","r",stdin);
    ifstream cin("aparitii2.in");
    freopen("aparitii2.out","w",stdout);



    cin>>S;
    cin>>P;

    a = P + S;
    Z_algorithm(0);

    std::reverse(P.begin(),P.end());
    std::reverse(S.begin(),S.end());
    a = P+S;
    Z_algorithm(1);


    for (int i=P.size();i+P.size()-1 < a.size();i++)
    {
        ans[min((int)P.size()/2,min(Z[0][i],Z[1][a.size()-i]))]++;
    }

    for (int i=P.size()/2;i>=1;i--)
        ans[i] += ans[i+1];

    for (int i=1;i<=P.size()/2;i++)
        cout<<ans[i]<<"\n";

    return 0;
}
