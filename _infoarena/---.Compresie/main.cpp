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

#define maxM 1000011
#define maxN 1024

int n, i, m, pos;
char s[maxM];
char ans[maxN][maxN];

int splits;
int dim;

bool is_char(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

int read_nr() {
    int ans = 0;

    while (is_digit(s[pos])) {
        ans = ans * 10 + s[pos] - '0';
        pos++;
    }

    return ans;
}

pair<int, char> read_elems() {
    int cnt = 1;
    if (is_digit(s[pos]))
        cnt = read_nr();
    return mp(cnt, s[pos++]);
}

void _fill(int x1, int y1, int x2, int y2, char c) {
    for (int i = x1; i <= x2; i++)
        for (int j = y1; j <= y2; j++)
            ans[i][j] = c;
}

void solve(int x1, int y1, int x2, int y2) {
    if (s[pos] == '*') { //! splited
        int mid_x = (x1 + x2) / 2;
        int mid_y = (y1 + y2) / 2;

        pos++;
        solve(x1, y1, mid_x, mid_y);

        if (mid_y != y2)
            solve(x1, mid_y + 1, mid_x, y2);

        if (mid_x != x2)
            solve(mid_x + 1, y1, x2, mid_y);

        if (mid_x != x2 && mid_y != y2)
            solve(mid_x + 1, mid_y + 1, x2, y2);

    } else { //! not splited
        auto now = read_elems();
        _fill(x1, y1, x2, y2, now.second);
    }
}

int main()
{
    freopen("compresie.in","r",stdin);
    freopen("compresie.out","w",stdout);

    scanf("%s", s + 1);
    m = strlen(s + 1);

    for(pos = 1; pos <= m; ) {
        if (s[pos] == '*') {
            splits++;
            pos++;
            continue;
        }

        auto now = read_elems();
        dim += now.first;
    }

    n = sqrt(dim);

    pos = 1;
    solve(1, 1, n, n);

    printf("%d\n", splits);
    for (i = 1; i <= n; i++)
        printf("%s\n", ans[i] + 1);

    return 0;
}
