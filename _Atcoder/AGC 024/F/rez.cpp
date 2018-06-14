#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 21;

int n, k, i, j, limit, bit, mask;
char s[1 << maxN];
vector<int> data[maxN];

void print_nr(int bits, int j) {
    for (bits--; bits >= 0; bits--) {
        printf("%d", (j >> bits) & 1);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &k);
    for (i = 0; i <= n; i++) {
        scanf("%s\n", s);
        limit = 1 << i;
        data[i].resize(limit);

        for (j = 0; j < limit; j++)
            data[i][j] = s[j] - '0';
    }

    for (bit = n; bit >= 1; bit--) {
        mask = (1 << (bit - 1)) - 1;
        for (i = bit; i <= n; i++) {
            limit = 1 << i;

            for (j = 0; j < limit; j++) {
                int addr = (j & mask) | ((j >> (bit + 1)) << bit);
                //cerr << j << ' ' << addr << ' ' << i <<  '\n';
                //if (addr >= (limit / 2)) cerr << "Err\n";
                data[i - 1][addr] += data[i][j];
            }
        }
    }

    for (i = n; i >= 0; i--) {
        limit = 1 << i;

        for (j = 0; j < limit; j++) { 
            if (data[i][j] >= k) {
                print_nr(i, j);
                return 0;
            }
        }
    }


    return 0;
}
