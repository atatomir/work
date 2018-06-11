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

const int maxN = 100011;
const int sigma = 26;

int n, i, j, p;
char s[maxN];
int ans;

int aux[sigma + 11];
bool on[sigma + 11];

bool check(int sz) {
    int i, j, maxi, mini;

    memset(aux, 0, sizeof(aux));
    memset(on, 0, sizeof(on));

    for (i = 1; i <= sz; i++) on[s[i] - 'a'] = true;
    for (i = 1; i <= sz; i++) {
        aux[s[i] - 'a']++;

        maxi = mini = aux[s[i] - 'a'];
        for (j = 0; j < sigma; j++)
            if (on[j])
                mini = min(mini, aux[j]), maxi = max(maxi, aux[j]);

        if (maxi - mini > 1) return false;
    }

    return true;
}

void brute(int step, int cost) {
    if (cost >= ans) return;
    if (!check(step - 1)) return;

    if (step == n + 1) {
        ans = min(ans, cost);
        return;
    }

    char old = s[step];
    brute(step + 1, cost);

    for (int i = 0; i < sigma; i++) {
        s[step] = 'a' + i;
        brute(step + 1, cost + 1);
    }

    s[step] = old;
}

int main()
{
    freopen("smooth2.in", "r", stdin);
    freopen("smooth2.ok", "w", stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);
    ans = n;

    brute(1, 0);

    printf("%d", ans);

    return 0;
}
