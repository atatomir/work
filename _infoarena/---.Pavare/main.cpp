#include <fstream>

using namespace std;

ifstream fin("pavare.in");
ofstream fout("pavare.out");

long n,m,k,i,l,c,cnr=0,val,j,maxim;
long mask[170];
long dp[170][2000];
long confs[2000];
long vals[2000];

inline bool check(long x){
    static long act;
    act =0; val = 0;
    for(long i = 0;i<=m;i++){
        if(x&1) {
            act++;
        } else {
            if(act % 2 == 1) return 0;
            val += act / 2;
            act = 0;
        }

        x >>= 1;
    }
    return 1;
}

int main()
{
    fin >> n >> m >> k;
    for(i=1;i<=k;i++){
        fin >> l >> c;
        mask[l] |= 1 << (c-1);
        mask[l+1] |= 1 << (c-1);
    }

    for(i=(1<<m)-1;i>=0;i--){
        if(check(i)){
            cnr++;
            confs[cnr] = i;
            vals[cnr] = val;
        }
    }

    for(i=2;i<=n;i++){
        for(j=1;j<=cnr;j++){
            if(confs[j]&mask[i]) continue;
            maxim = 0;
            for(k=1;k<=cnr;k++){
                if((confs[j] & confs[k]) == 0){
                    val = dp[i-1][k] + vals[j];
                    if(val > maxim) maxim = val;
                }
            }
            dp[i][j] = maxim;

        }
    }

    maxim = dp[n][1];
    for(i=2;i<=cnr;i++)
        if(maxim < dp[n][i]) maxim = dp[n][i];

    fout << maxim << '\n';

    /*for(i=1;i<=n;i++)
        for(j=1;j<=cnr;j++)
            fout << i << ' ' << confs[j] << ' ' << dp[i][j] << '\n';*/


    fin.close();
    fout.close();
    return 0;
}
