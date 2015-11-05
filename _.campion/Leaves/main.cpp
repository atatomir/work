#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define ll long long
#define inf 1000000000000000000

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);
            reFill();
        }

        template<class T>
        Buffer& operator>>(T &dest) {
            while (!isDigit(data[pos])) {
                if (++pos == dim) reFill();
            }
            dest = 0;
            while(isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};
Buffer fin("leaves.in", 1 << 20);


#define compute(a, b) (dp[dp_s][b] - pay_sum[a] + pay_sum[b - 1] + 1LL * (sum[a] - sum[b - 1]) * a)
#define getTime(b, c) (1.00 * (pay_sum[b - 1] - pay_sum[c - 1] + dp[dp_s][b] - dp[dp_s][c]) / (sum[b - 1] - sum[c - 1]))

int n, i, k;

int how[maxN];
int sum[maxN];
ll pay[maxN];
ll pay_sum[maxN];

ll dp[2][maxN];
int dp_s, dp_d;

int qL, qR;
int work[maxN];
double _time[maxN];

/*
ll compute(ll a, ll b) {
    return dp[dp_s][b] + pay_sum[b - 1] - pay_sum[a] - (sum[b - 1] - sum[a]) * a;
}

double getTime(ll b, ll c) {
    return -1.00 * (pay_sum[b - 1] - pay_sum[c - 1] + dp[dp_s][b] - dp[dp_s][c]) / (sum[c - 1] - sum[b - 1]);
}
*/

void execute() {
    int i;

    qL = qR = 1;
    work[1] = n + 1;
    _time[1] = inf;

    for (i = n; i >= 1; i--) {
        while (_time[qL + 1] >= i) qL++;

        dp[dp_d][i] = compute(i, work[qL]);

        while (true) {
            _time[qR + 1] = getTime(i, work[qR] );

            if (_time[qR + 1] >= _time[qR])
                qR--;
            else {
                break;
            }
        }

        work[++qR] = i;
    }

}

int main()
{
    freopen("leaves.in","r",stdin);
    freopen("leaves.out","w",stdout);

    fin >> n >> k;
    for (i = 1; i <= n; i++) {
        fin >> how[i];
        sum[i] = how[i] + sum[i - 1];

        pay[i] = how[i] * i;
        pay_sum[i] = pay_sum[i - 1] + pay[i];
    }

    dp_s = 0; dp_d = 1;
    for (i = 1; i <= n; i++) dp[dp_s][i] = inf;
    dp[dp_s][n + 1] = 0;

    for (i = 1; i <= k; i++) {
        execute();
        swap(dp_s, dp_d);
    }

    printf("%lld", dp[dp_s][1]);

    return 0;
}
