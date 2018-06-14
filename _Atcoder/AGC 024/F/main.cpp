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

int n, k, i, j, p, limit, bit, mask, nxt, aux, aux_bits;
char s[1 << maxN];
vector<int> data[maxN][maxN]; //! fixed bits, total bits
vector<int> emp;

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
        
        emp = vector<int>(limit, 0);
        for (j = 0; j <= i; j++)
            data[j][i] = emp;

        for (j = 0; j < limit; j++)
            data[0][i][j] = s[j] - '0';
    }

    for (int bts = 0; bts <= n; bts++) {
        mask = (1 << bts) - 1;

        for (i = bts + 1; i <= n; i++) {
           int limit = (1 << i);

           for (j = 0; j < limit; j++) {
                data[bts][bts][j & mask] += data[bts][i][j];
                
                for (nxt = 0; nxt < 2; nxt++) {
                    aux = j;
                    aux_bits = i;

                    while (((aux >> bts) & 1) != nxt) {
                        aux = (aux & mask) | ((aux >> (bts + 1)) << bts);
                        if(--aux_bits == bts) break;
                    }

                    if (aux_bits != bts)
                        data[bts + 1][aux_bits][aux] += data[bts][i][j];
                }
           }
        }
    }

    for (i = n; i >= 1; i--) {
        limit = (1 << i);
        for (j = 0; j < limit; j++) {
            if (data[i][i][j] < k) continue;
            print_nr(i, j);
            return 0;
        }
    }

    return 0;
}
