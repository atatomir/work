#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

#define maxN 50011

long n,i;
long long v[maxN],s;
vector<long> id[2];

long long act;
char ans[maxN];

int main()
{
    freopen("semne.in","r",stdin);
    freopen("semne.out","w",stdout);

    scanf("%ld %lld",&n,&s);
    id[0].resize(n); id[1].clear();
    for(i=1;i<=n;i++){
        scanf("%lld",&v[i]);
        act += v[i];
        id[0][i-1] = i;
    }

    while(s!=act){
        if(s < act){ //! scadem
            long pos = (rand()%id[0].size());
            long actId = id[0][pos];

            act -= v[actId]*2;
            id[1].push_back(actId);
            id[0][pos] = id[0][ id[0].size()-1 ]; id[0].pop_back();
        } else {  //! crestem
            long pos = (rand()%id[1].size());
            long actId = id[1][pos];

            act += v[actId]*2;
            id[0].push_back(actId);
            id[1][pos] = id[1][ id[1].size()-1 ]; id[1].pop_back();
        }
    }

    for(i=0;i<id[0].size();i++) ans[ id[0][i] ] = '+';
    for(i=0;i<id[1].size();i++) ans[ id[1][i] ] = '-';

    ans[0]=ans[n+1] = '\0';
    printf("%s",ans+1);


    return 0;
}
