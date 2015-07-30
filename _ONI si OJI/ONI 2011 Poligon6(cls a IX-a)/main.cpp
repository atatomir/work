#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long n,i,j,x;
long B,R;
vector<double> P;
vector<long> Ans;

int main()
{
    freopen("poligon6.in","r",stdin);
    freopen("poligon6.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&R); R = R*R;

        for(j=1;2*j*j<=R;j++){
            B = R - j*j;
            if(long(sqrt(B))==sqrt(B)) P.push_back(1.00*j/sqrt(B));
        }
    }
    sort(P.begin(),P.end());

    i=0;
    while(i<P.size()){
        j=1;
        while(P[i] == P[i+j]) j++;
        Ans.push_back(j);
        i += j;
    }

    printf("%ld\n%ld\n",P.size()*2,Ans.size()*2);
    for(i=0;i<Ans.size();i++) printf("%ld ",Ans[i]);
    for(i=Ans.size()-1;i>=0;i--) printf("%ld ",Ans[i]);

    return 0;
}
