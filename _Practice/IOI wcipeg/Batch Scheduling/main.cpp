#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10011

class Buffer {
    public:
        Buffer(int _dim) {
            //freopen("test.in","r",stdin);
            dim = _dim;
            data.resize(dim);
            reFill();
        }

        Buffer& operator>>(int &dest) {
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
Buffer fin(1 << 20);

int n, i, S;
int taskTime[maxN], taskPay[maxN];
int dp[maxN];

deque<int> work;

int compute(int l, int r) {
    r--;
    return (taskPay[n] - taskPay[l - 1]) * (taskTime[r] - taskTime[l - 1] + S) + dp[r + 1];
}

double getTime(int l, int r) {
    return 1.00 * ( dp[l] - dp[r] ) / (taskTime[r - 1] - taskTime[l - 1]);
}

bool itsBetter(int i, int j1, int j2) {
    double _Time1 = getTime(i, j2);
    double _Time2 = getTime(j1, j2);

    return _Time1 <= _Time2;
}

int main()
{
    //freopen("test.in","r",stdin);

    fin >> n >> S;
    for (i = 1; i <= n; i++) {
        fin >> taskTime[i] >> taskPay[i];
        taskTime[i] += taskTime[i - 1];
        taskPay[i] += taskPay[i - 1];
    }

    work.push_back(n + 1);

    for (i = n; i > 0; i--) {
        while (work.size() > 1) {
            int j2 = work.front(); work.pop_front();
            int j1 = work.front(); work.push_front(j2);

            if (compute(i, j1) <= compute(i , j2)) {
                work.pop_front();
                continue;
            }
            break;
        }

        dp[i] = compute(i, work.front());


        while (work.size() > 1) {
            int j1 = work.back(); work.pop_back();
            int j2 = work.back(); work.push_back(j1);

            if (itsBetter(i, j1, j2)) {
                work.pop_back();
                continue;
            }
            break;
        }
        work.push_back(i);
    }

    printf("%d", dp[1]);


    return 0;
}
