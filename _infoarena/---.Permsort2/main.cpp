#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class AIB{
    private:
        vector<long> C;
        long lim;
        long zrs(long x){ return (x^(x-1))&x; }
    public:
        AIB(long dim){
            C.resize(dim+17);
            lim= dim;
        }

        void add(long pos){
            while(pos <= lim){
                C[pos]++;
                pos += zrs(pos);
            }
        }
        long sum(long pos){
            long ans = 0;
            while(pos){
                ans += C[pos];
                pos -= zrs(pos);
            }
            return ans;
        }
};

#define maxN 1000024

long n,i;
pair<long,long> a[maxN];
vector<long> ans;

int main()
{
    freopen("permsort2.in","r",stdin);
    freopen("permsort2.out","w",stdout);

    scanf("%ld",&n);  AIB Aib(n);
    for(i=1;i<=n;a[i].second=i++) scanf("%ld",&a[i].first);
    sort(a+1,a+n+1);

    for(i=n;i;i--){
        if(i==n && a[n].second==1) {Aib.add(1);continue;}

        long pos = a[i].second;
        long sum = Aib.sum(pos);
        pos += (n-i)-sum;

        ans.push_back(pos);
        Aib.add(a[i].second);
    }

    printf("%ld\n",ans.size()*2);
    for(i=0;i<ans.size();i++) printf("P %ld\nP %ld\n",ans[i]-1,ans[i]);


    return 0;
}
