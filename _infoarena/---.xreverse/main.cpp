#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011
#define maxK 33

int k;
int mod;
int powTen[maxN<<1];
int powTen_k[maxN<<1];

class State {
    public:
        int howMany;
        int data_sum[maxK][maxK];
        int data_count[maxK][maxK];

        void init(bool withOne) {
            howMany = 0;
            memset(data_sum,0,sizeof(data_sum));
            memset(data_count,0,sizeof(data_count));

            if (!withOne) return;

            howMany = 1;
            for (int value = 1; value < 10; value++) {
                data_sum[value % k][value % k] += value;
                data_count[value % k][value % k]++;

                modIt(data_sum[value % k][value % k]);
                modIt(data_count[value % k][value % k]);
            }
        }

        void Multiply(const State& who,State& dest) {
            dest.init(false);
            dest.howMany = howMany + who.howMany;

            if (howMany == 0) {
                for (int i = 0; i < k; i++){
                    for (int j = 0; j < k; j++){
                        dest.data_sum[i][j] = who.data_sum[i][j];
                        dest.data_count[i][j] = who.data_count[i][j];
                    }
                }

                return;
            }

            for (int v1 = 0; v1 < k; v1++) {
                for (int v2 = 0; v2 < k; v2++) {
                    int d_sum = data_sum[v1][v2];
                    int d_count = data_count[v1][v2];

                    for (int vv1 = 0; vv1 < k; vv1++) {
                        for (int vv2 = 0; vv2 < k; vv2++) {
                            /*  Now i have the states [v1][v2]
                             *  and [vv1][vv2]
                             */

                             int go_v1 = (v1 * powTen_k[who.howMany] + vv1) % k;
                             int go_v2 = (vv2 * powTen_k[howMany] + v2) % k;

                             dest.data_count[go_v1][go_v2] = (dest.data_count[go_v1][go_v2] +
                                                              d_count * who.data_count[vv1][vv2]) % mod;

                             int auxV1 = (((d_sum * powTen[who.howMany]) % mod) * who.data_count[vv1][vv2]) % mod;
                             int auxV2 = (who.data_sum[vv1][vv2] * d_count) % mod;

                             dest.data_sum[go_v1][go_v2] = (dest.data_sum[go_v1][go_v2] + auxV1 + auxV2)% mod;
                        }
                    }
                }
            }
        }

    private:

        void modIt(int &who) {
            while (who >= mod) who -= mod;
        }
};

int n,i;

void debug_sum(State &who) {
    for (int ii = 0; ii < k; ii++){
        for (int jj = 0; jj < k; jj++)
            cerr << who.data_sum[ii][jj] << ' ';
        cerr << '\n';
    }
}
void debug_count(State &who) {
    for (int ii = 0; ii < k; ii++){
        for (int jj = 0; jj < k; jj++)
            cerr << who.data_count[ii][jj] << ' ';
        cerr << '\n';
    }
}

int main()
{
    freopen("xreverse.in","r",stdin);
    freopen("xreverse.out","w",stdout);

    scanf("%d%d%d",&n,&k,&mod);

    powTen[0] = 1;
    for (i = 1; i <= 2*n; i++) powTen[i] = (powTen[i-1] * 10) % mod;
    powTen_k[0] = 1;
    for (i = 1; i <= 2*n; i++) powTen_k[i] = (powTen_k[i-1] * 10) % k;

    State ans[2],aux[2];
    int ans_i = 0;
    int aux_i = 0;

    ans[ans_i].init(0);
    aux[aux_i].init(1);

    while (n > 0) {
        if (n & 1) {
            ans[ans_i].Multiply(aux[aux_i], ans[ans_i ^ 1]);
            ans_i ^= 1;
        }

        n >>= 1;
        if (n == 0) break;

        aux[aux_i].Multiply(aux[aux_i], aux[aux_i ^ 1]);
        aux_i ^= 1;
    }

    printf("%d",ans[ans_i].data_sum[0][0]);

    return 0;
}
