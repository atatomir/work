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

#define maxN 150011

int t, ti, n, i;
char s[maxN];
int pos;

int must(string patt) {
    int i, j;
    bool good;

    if (pos == 0) return 0;

    i = pos;
    good = true;
    for (j = 0; j < patt.size(); j++)
        if (s[i + j] != patt[j])
            good = false;

    if (good)
        return pos + patt.size();

    return 0;
}

int rep(string patt) {
    int i, j;
    bool good;

    if (pos == 0) return 0;

    for (i = pos; i + patt.size() - 1 <= n; i += patt.size()) {
        good = true;
        for (j = 0; j < patt.size(); j++)
            if (s[i + j] != patt[j])
                good = false;
        if (!good) return i;
    }

    return i;
}


bool c1() {
    pos = 1;
    pos = rep("0");
    pos = must("1");
    pos = rep("0");

    return pos == n + 1;
}

bool c2() {
    if (s[1] == '1') return false;

    pos = 1;
    pos = rep("0");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c3() {
    if (s[n] == '1') return false;

    pos = 1;
    pos = rep("0");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c4() {
    pos = 1;

    pos = rep("0");
    pos = must("11");
    pos = rep("01");
    pos = must("00");
    pos = rep("10");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c5() {
    pos = 1;

    pos = rep("0");
    pos = must("11");
    pos = rep("01");
    pos = rep("11");
    pos = must("00");
    pos = rep("10");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c6() {
    pos = 1;

    pos = rep("0");
    pos = must("11");
    pos = rep("01");
    pos = must("00");
    pos = rep("11");
    pos = rep("10");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c7() {
    pos = 1;

    pos = rep("0");
    pos = must("11");
    pos = rep("01");
    pos = rep("11");
    pos = must("1011");
    pos = rep("10");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c8() {
    pos = 1;

    pos = rep("0");
    pos = must("11");
    pos = rep("01");
    pos = must("1101");
    pos = rep("11");
    pos = rep("10");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c9() {
    pos = 1;

    pos = rep("0");
    pos = must("11");
    pos = rep("01");
    pos = rep("11");
    pos = must("01");
    pos = rep("0");

    return pos == n + 1;
}

bool c10() {
    pos = 1;

    pos = rep("0");
    pos = must("10");
    pos = rep("11");
    pos = rep("10");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool c11() {
    pos = 1;

    pos = rep("0");
    pos = must("11");
    pos = must("01");
    pos = rep("01");
    pos = rep("0");

    return pos == n + 1;
}

bool c12() {
    pos = 1;

    pos = rep("0");
    pos = rep("10");
    pos = must("10");
    pos = must("11");
    pos = rep("0");

    return pos == n + 1;
}

bool good() {
    if (c1()) return true;
    if (c2()) return true;
    if (c3()) return true;
    if (c4()) return true;
    if (c5()) return true;
    if (c6()) return true;
    if (c7()) return true;
    if (c8()) return true;
    if (c9()) return true;
    if (c10()) return true;
    if (c11()) return true;
    if (c12()) return true;


    reverse(s + 1, s + n + 1);

    if (c1()) return true;
    if (c2()) return true;
    if (c3()) return true;
    if (c4()) return true;
    if (c5()) return true;
    if (c6()) return true;
    if (c7()) return true;
    if (c8()) return true;
    if (c9()) return true;
    if (c10()) return true;
    if (c11()) return true;
    if (c12()) return true;

    return false;
}

int main()
{
    freopen("peg.in","r",stdin);
    freopen("peg.out","w",stdout);

    scanf("%d\n", &t);
    for (ti = 1; ti <= t; ti++) {
        memset(s, 0, n + 3);
        scanf("%s\n", s + 1);
        n = strlen(s + 1);

        if (good())
            printf("1\n");
        else
            printf("0\n");
    }


    return 0;
}
