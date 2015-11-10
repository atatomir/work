#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxDim 3100000
#define maxPress 1024
#define maxN 1024

int n, i;
char s[maxDim];
char num[maxPress];
int beg[maxN];
int len[maxN];

int prov['z' + 11];

void do_it() {
    prov['a'] = 2;
    prov['b'] = 2;
    prov['c'] = 2;

    prov['d'] = 3;
    prov['e'] = 3;
    prov['f'] = 3;

    prov['g'] = 4;
    prov['h'] = 4;
    prov['i'] = 4;

    prov['j'] = 5;
    prov['k'] = 5;
    prov['l'] = 5;

    prov['m'] = 6;
    prov['n'] = 6;
    prov['o'] = 6;

    prov['p'] = 7;
    prov['q'] = 7;
    prov['r'] = 7;
    prov['s'] = 7;

    prov['t'] = 8;
    prov['u'] = 8;
    prov['v'] = 8;

    prov['w'] = 9;
    prov['x'] = 9;
    prov['y'] = 9;
    prov['z'] = 9;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n", &n);

    beg[1] = 1;
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + beg[i]);
        len[i] = strlen(s + beg[i]);
        beg[i + 1] = beg[i] + len[i] + 5;
    }
    scanf("%s", num + 1);
    int num_len = strlen(num + 1);

    do_it();

    int ans = 0;
    for (i = 1; i <= n; i++) {
        if (num_len != len[i]) continue;

        bool good = true;
        for (int j = 0; j < len[i]; j++) {
            int go = prov[ s[ beg[i] + j ] ];
            if (go != num[j + 1] - '0') {
                good = false;
                break;
            }
        }

        if (good) ans++;
    }
    printf("%d", ans);


    return 0;
}
