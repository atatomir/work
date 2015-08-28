#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2511
#define maxK 511

#define big_int_dim 50
class big_integer {
    public:
        int dim;
        long long base = 10000000000000000LL;
        long long data[big_int_dim];

        void init() {
            dim = 1;
            memset(data,0,sizeof(data));
        }

        void set(int val) {
            data[1] = val ;
        }

        void operator+=(big_integer& who) {
            dim = max(dim,who.dim);
            for (int i = 1; i <= dim; i++) {
                data[i] += who.data[i];
                if (data[i] >= base) {
                    data[i+1]++;
                    data[i] -= base;
                }
            }

            if (data[dim+1] != 0) dim++;
        }

        void operator=(big_integer& who) {
            dim = who.dim;
            memcpy(&data[0],&who.data[0], sizeof(data) );
        }

        void operator-=(int val) {
            data[1] -= val;
            for (int i = 1; i <= dim; i++) {
                if (data[i] >= 0) continue;

                data[i] += base;
                data[i+1]--;
            }

            while (dim > 1 && data[dim] == 0) dim--;
        }

        void write() {
            printf("%lld",data[dim]);


            for (int i = dim-1; i > 0; i--) {
                if (data[i]==0) {
                    printf("0");
                    continue;
                }

                long long aux = base;
                while(aux) {
                    aux /= 10;
                    if (data[i] >= aux)
                        break;
                    else
                        printf("0");
                }

                printf("%lld",data[i]);
            }
        }
};

int n,i,j,k,act;
big_integer dp[2][maxK];
int dp_s,dp_d;

int main()
{
    freopen("mult.in","r",stdin);
    freopen("mult.out","w",stdout);

    scanf("%d%d",&n,&k);

    dp_s = 0; dp_d = 1;
    for (i = 0; i < k; i++) {
        dp[dp_s][i].init();
        dp[dp_d][i].init();
    }
    dp[dp_s][0].set(1);

    for (int pas = 1; pas <= n; pas++) {
        scanf("%d",&act);

        for (i = 0; i < k; i++) dp[dp_d][i] = dp[dp_s][i];
        for (i = 0; i < k; i++) {
            int dest = (i*10 + act)%k;
            dp[dp_d][dest] += dp[dp_s][i];
        }

        swap(dp_s,dp_d);
    }

    dp[dp_s][0] -= 1;
    dp[dp_s][0].write();

    return 0;
}
