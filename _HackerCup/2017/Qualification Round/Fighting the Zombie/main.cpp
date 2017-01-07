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

#define maxY 23
#define maxX 23
#define maxVal (maxY * maxX)

int t, ti, n, i, H, pos;
double dp[maxY][maxX][maxVal];
string s;
double ans;

void pre() {
    int dice, step, i, limit, v;

    for (dice = 4; dice <= 20; dice += 2) {
        if (dice == 14 || dice == 16 || dice == 18) continue;

        dp[dice][0][0] = 1.00;
        for (step = 0; step < 20; step++) {
            limit = step * dice;

            for (i = step; i <= limit; i++) {
                for (v = 1; v <= dice; v++)
                    dp[dice][step + 1][i + v] += dp[dice][step][i] / dice;
            }
        }
    }
}

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

int read_nr() {
    while (!is_digit(s[pos])) pos++;

    int nr = 0;
    while (is_digit(s[pos])) {
        nr = nr * 10 + s[pos] - '0';
        pos++;
    }

    return nr;
}

double check() {

    s += "@";
    pos = 0;

    int steps = read_nr();
    int dice = read_nr();
    int dif = 0;

    if (s[pos] == '+' || s[pos] == '-') {
        dif = (s[pos] == '+' ? 1 : -1);
        dif *= read_nr();
    }

    int limit = dice * steps;
    double ans = 0.00;

    for (int i = steps; i <= limit; i++) {
        if (i + dif < H) continue;
        ans += dp[dice][steps][i];
    }

    return ans;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    pre();

    cin >> t;
    cerr << "Start solving " << t << " cases.\n";
    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << "\n";

        ans = 0.00;
        cin >> H >> n;

        for (i = 1; i <= n; i++) {
            cin >> s;
            //cerr << s << '\n';
            ans = max(ans, check());
        }

        printf("Case #%d: %.6lf\n", ti, ans);
    }


    return 0;
}
