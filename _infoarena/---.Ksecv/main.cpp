#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define inf 1000000001

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);

            reFill();
        }

        Buffer& operator>>(int &dest) {
            while (!isDigit(data[pos])) {
                if(++pos == dim) reFill();
            }
            dest = 0;
            while (isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if(++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, sizeof(data));
            fread(&data[0], 1, dim, stdin);
        }

        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};

int n, i, k;
int vect[maxN];
int dp[2][maxN];
int dp_s, dp_d;

int s_dim;
pair<int , int> S[maxN];
int minS[maxN];

void clearStack() {
    s_dim = 0;
}

void addStack(int v, int before) {
    while (s_dim > 0) {
        auto act = S[s_dim];

        if (v < act.first) break;
        before = min(before, act.second);

        s_dim--;
    }

    S[++s_dim] = mp(v, before);
    if (s_dim == 1)
        minS[s_dim] =  v + before ;
    else
        minS[s_dim] = min(v + before, minS[s_dim - 1]) ;
}

int getBest() {
    return min(minS[s_dim], inf);
}

int main()
{
    //freopen("ksecv.in","r",stdin);
    Buffer fin("ksecv.in", 1 << 20);
    freopen("ksecv.out","w",stdout);

    fin >> n >> k;
    for (i = 1; i <= n; i++) fin >> vect[i];

    dp_s = 0; dp_d = 1;
    dp[dp_s][0] = inf;
    dp[dp_s][1] = vect[1];

    for (i = 2; i <= n; i++) dp[dp_s][i] = max(dp[dp_s][i - 1], vect[i]);

    for (int pas = 2; pas <= k; pas++) {
        clearStack();

        for (i = 0; i < pas; i++) dp[dp_d][i] = inf;
        for (i = pas; i <= n; i++) {
            addStack(vect[i], dp[dp_s][i-1]);
            dp[dp_d][i] = getBest();
        }

        swap(dp_s, dp_d);
    }

    printf("%d", dp[dp_s][n]);

    return 0;
}
