#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 1000011
#define maxK 55
#define mod 107391
#define base 26
#define maxL 2555

class myHash{
    public:
        vector<long> C[mod];
        void init(){
            for(long i=0;i<mod;i++) C[i].clear();
        }
        void add(long val,long pos){
            C[val].push_back(pos);
        }
}Hash;

long n,m,l,k,i,j,dim,ans;
char s[maxN],a[maxL];
long act,powS;

long makeHash(long pos){
    long dest = pos+dim;
    long ans = 0;
    while(pos<dest){
        ans = (ans*base + a[pos]-'a')%mod;
        pos++;
    }
    return ans;
}

bool check(long pos){
    long dest = pos+l,i=1;
    long kk = k;
    if(pos<1 || dest>n+1) return false;

    while(pos<dest){
        if(a[i] != s[pos]){
            kk--;
            if(!kk) return false;
        }
        pos++; i++;
    }
    return true;
}

int main()
{
    freopen("radio2.in","r",stdin);
    freopen("radio2.out","w",stdout);

    scanf("%ld %ld %ld %ld\n%s\n",&n,&m,&l,&k,s+1); k++;
    dim = l/k; powS = 1; Hash.init(); s[0] = 'a';
    for(i=1;i<dim;i++){
        act = (act*base + s[i]-'a')%mod;
        powS = (powS*base)%mod;
    }
    for(i=dim;i<=n;i++){
        act = (act-powS*(s[i-dim]-'a'));
        while(act<0) act += mod;
        act%= mod;
        act = (act*base+s[i]-'a')%mod;

        Hash.add(act,i);
    }

    for(;m;m--){
        scanf("%s\n",a+1);
        ans = 0;
        for(i=1;i<=k;i++){
            act = makeHash(dim*(i-1)+1);
            for(j=0;j<Hash.C[act].size();j++){
                if(check(Hash.C[act][j]-dim*i+1)){
                    ans = 1; break;
                }
            }
            if(ans) break;
        }
        printf("%ld\n",ans);
    }

    return 0;
}
