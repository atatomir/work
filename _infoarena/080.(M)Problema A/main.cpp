#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("pba.in");
ofstream fout("pba.out");

#define cin fin
#define cout fout
#define mod 1000000007

long n,i,a[50005];
long pos;
long long ans=1;

int main()
{
    cin >> n;
    for(i=1;i<=n;i++) cin  >> a[i];
    for(long t=3;t;t--){
        pos = 1;
        for(i=2;i<=n;i++){
            if(a[i] > a[pos]) pos = i;
        }
        ans *= a[pos];
        ans %= mod;
        a[pos] = -1;
    }
    cout << ans;
    return 0;
}
