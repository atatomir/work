#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111

static const int big_base = 100000000;
static const int big_dim = 27;
class big_integer {
    public:
        int dim;
        int data[big_dim];

        void init() {
            dim = 1;
            memset(data,0,sizeof(data));
        }
        void init(int v) {
            init();
            data[1] = v;
        }
        void operator=(const big_integer& who) {
            memcpy(data,who.data,sizeof(data));
        }
        void operator+=(const big_integer& who) {
            dim = max(dim,who.dim);
            for (int i = 1; i <= dim; i++) {
                data[i] += who.data[i];
                if (data[i] >= big_base) {
                    data[i] -= big_base;
                    data[i+1]++;
                }
            }
            if (data[dim+1] != 0) dim++;
        }
        void parseInt(int v) {
            for (int aux = big_base/10; aux > 0; aux /= 10) {
                if (v < aux)
                    printf("0");
                else
                    break;
            }
            printf("%d",v);
        }
        void write() {
            printf("%d",data[dim]);
            for (int i = dim - 1; i > 0; i--) parseInt(data[i]);
            printf("\n");
        }

};

int n,i,h_max;
big_integer dp[3][maxN][3]; //! pos,h,type
int ind_1,ind_2,ind_3;

int main()
{
    freopen("munte3.in","r",stdin);
    freopen("munte3.out","w",stdout);

    scanf("%d",&n);
    h_max = n-1;
    n = n * 2 - 2;

    ind_1 = 0;
    ind_2 = 1;
    ind_3 = 2;

    for (i = 0; i <= h_max+3; i++) {
        dp[ind_1][i][0].init(0);
        dp[ind_1][i][1].init(0);
        dp[ind_1][i][2].init(0);

        dp[ind_2][i][0].init(0);
        dp[ind_2][i][1].init(0);
        dp[ind_2][i][2].init(0);

        dp[ind_3][i][0].init(0);
        dp[ind_3][i][1].init(0);
        dp[ind_3][i][2].init(0);
    }

    dp[ind_1][0][0].init(1);
    dp[ind_2][1][1].init(1);

    if (n == 0) {
        printf("1\n");
        return 0;
    }

    for (i = 2; i <= n; i++) {
        for (int actH = 0; actH <= h_max; actH++) {
            dp[ind_3][actH][0].init(0);
            dp[ind_3][actH][0] += dp[ind_1][actH][0];
            dp[ind_3][actH][0] += dp[ind_1][actH][1];
            dp[ind_3][actH][0] += dp[ind_1][actH][2];

            dp[ind_3][actH][1].init(0);
            if (actH > 0) {
                dp[ind_3][actH][1] += dp[ind_2][actH-1][0];
                dp[ind_3][actH][1] += dp[ind_2][actH-1][1];
                dp[ind_3][actH][1] += dp[ind_2][actH-1][2];
            }

            dp[ind_3][actH][2].init(0);
            if (actH < h_max) {
                dp[ind_3][actH][2] += dp[ind_2][actH+1][0];
                if (actH != 0)
                    dp[ind_3][actH][2] += dp[ind_2][actH+1][1];
                dp[ind_3][actH][2] += dp[ind_2][actH+1][2];
            }
        }

        swap(ind_1,ind_2);
        swap(ind_2,ind_3);
    }

    big_integer ans;
    ans.init(0);
    ans += dp[ind_2][0][0];
    ans += dp[ind_2][0][1];
    ans += dp[ind_2][0][2];

    ans.write();

    return 0;
}
