#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int t, n, k, i, dim;
char s[maxN];
bool is_start[maxN];
int per;
vector<int> id;

int work[maxN];

void get_period() {
    int i;

    memset(is_start, 0, sizeof(is_start));
    i = 0;
    while (is_start[i] == false) {
        is_start[i] = true;
        i = (i + k) % n;
    }

    is_start[n] = true;
    for (per = 0; is_start[per + 1] == false; per++);
    per++;
}

bool cmp(int a, int b) {
    int bg_a = a * per;
    int bg_b = b * per;

    int i = 0;
    for (; s[bg_a] == s[bg_b] && i < per; i++, bg_a++, bg_b++);
    return s[bg_a] < s[bg_b];
}

bool are_same(int a, int b) {
    int bg_a = a * per;
    int bg_b = b * per;

    int i = 0;
    for (; s[bg_a] == s[bg_b] && i < per; i++, bg_a++, bg_b++);
    return i == per;
}

void get_new_string() {
    int i;

    id.clear();

    for (i = 0; i < n; i++)
        if (is_start[i])
            id.pb(id.size());

    sort(id.begin(), id.end(), cmp);

    dim = id.size();

    work[ id[0] ] = 0;
    for (i = 1; i < dim; i++) {
        if ( are_same(id[i], id[i - 1]) )
            work[ id[i] ] = work[ id[i - 1] ];
        else
            work[ id[i] ] = i;
    }
}

int solve() {
    int best = 0;
    int pos = 1;
    int l = 0;

    while (pos < dim && best + l + 1 < dim) {
        if (work[best + l] == work[(pos + l) % dim]) l++;
        else
        if (work[best + l] < work[(pos + l) % dim]) pos += l + 1, l = 0;
        else
        if (work[best + l] > work[(pos + l) % dim]) best = max(pos, best + l + 1), pos = best + 1, l = 0;
    }

    return best;
}

int main()
{
    freopen("talharie.in","r",stdin);
    freopen("talharie.out","w",stdout);

    scanf("%d\n", &t);
    for (; t > 0; t--) {
        memset(s, 0, sizeof(s));
        scanf("%d %d %s\n", &n, &k, s);

        get_period();
        get_new_string();

        int pos = solve() * per;
        printf("%s", s + pos);
        s[pos] = '\0';
        printf("%s\n", s);
    }


    return 0;
}
