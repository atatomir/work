#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 777
#define len_var int

int n, m, i, j;
char s[maxN][maxN];
int ll[maxN][maxN], rr[maxN][maxN], uu[maxN][maxN], dd[maxN][maxN];
int Answer;

multiset<len_var> work;
vector<len_var> rez[maxN];
len_var dp[maxN][maxN];

void preprocess() {
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if(s[i][j] == '0') continue;

            ll[i][j] = ll[i][j - 1] + 1;
            uu[i][j] = uu[i - 1][j] + 1;

            Answer = max(Answer, ll[i][j]);
            Answer = max(Answer, uu[i][j]);
        }
    }

    for (i = n; i >= 1; i--) {
        for (j = m; j >= 1; j--) {
            if(s[i][j] == '0') continue;

            rr[i][j] = rr[i][j + 1] + 1;
            dd[i][j] = dd[i + 1][j] + 1;

            Answer = max(Answer, rr[i][j]);
            Answer = max(Answer, dd[i][j]);
        }
    }
}

int split_columns(int l1, int c1, int l2, int c2, int mid) {
    int i, j;

    int ans = 0;

    for (i = l1; i < l2; i++) {
        for (j = i + 1; j <= l2; j++)
            dp[i][j] = 0;

        //! right side
        for (j = i + 1; j <= l2; j++)
            rez[j].clear();
        work.clear();

        for (j = mid + 1; j <= c2 && s[i][j] != '0'; j++) {
            rez[ i + dd[i][j] ].pb(j);
            work.insert(j);
        }

        for (j = i + 1; j <= l2; j++) {
            for (auto now : rez[j]) work.erase(now);
            auto it = work.upper_bound(mid + rr[j][mid + 1]);

            if (it == work.begin()) continue;

            it--;
            dp[i][j] = *it - mid;
        }

        //! left side
        for (j = i + 1; j <= l2; j++)
            rez[j].clear();
        work.clear();

        for (j = mid; j >= c1 && s[i][j] != '0'; j--) {
            rez[ i + dd[i][j] ].pb(j);
            work.insert(j);
        }

        for (j = i + 1; j <= l2; j++) {
            for (auto now : rez[j]) work.erase(now);
            auto it = work.lower_bound(mid - ll[j][mid] + 1);

            if (it == work.end()) continue;

            if (dp[i][j] == 0) continue;
            ans = max(ans, (dp[i][j] + (mid - *it + 1)) * (j - i + 1) );
        }
    }

    return ans;
}

int split_lines(int l1, int c1, int l2, int c2, int mid) {
    int i, j, k;

    int ans = 0;

    for (j = c1; j < c2; j++) {
        for (k = j + 1; k <= c2; k++)
            dp[j][k] = 0;

        //! upper side
        for (k = j + 1; k <= c2; k++)
            rez[k].clear();
        work.clear();

        for (k = mid; k >= l1 && s[k][j] != '0'; k--) {
            rez[j + rr[k][j]].pb(k);
            work.insert(k);
        }

        for (k = j + 1; k <= c2; k++) {
            for (auto now : rez[k])
                work.erase(now);
            auto it = work.lower_bound(mid - uu[mid][k] + 1);

            if (it == work.end()) continue;

            dp[j][k] = (mid - *it + 1);
        }

        //! bottom side
        for (k = j + 1; k <= c2; k++)
            rez[k].clear();
        work.clear();

        for (k = mid + 1; k <= l2 && s[k][j] != '0'; k++) {
            rez[j + rr[k][j]].pb(k);
            work.insert(k);
        }

        for (k = j + 1; k <= c2; k++) {
            for (auto now : rez[k])
                work.erase(now);
            auto it = work.upper_bound(mid + dd[mid + 1][k]);

            if (it == work.begin()) continue;

            it--;
            if (dp[j][k] == 0) continue;
            ans = max(ans, (dp[j][k] + *it - mid) * (k - j + 1) );
        }
    }

    return ans;
}


int compute(int l1, int c1, int l2, int c2) {
    int dim_l = l2 - l1 + 1;
    int dim_c = c2 - c1 + 1;
    int mid, ans;

    if (dim_l == 1 || dim_c == 1)
        return 0;

    ans = 0;

    if (dim_l <= dim_c) { //! split columns
        mid = (c1 + c2) >> 1;
        ans = max(ans, compute(l1, c1, l2, mid));
        ans = max(ans, compute(l1, mid + 1, l2, c2));
        ans = max(ans, split_columns(l1, c1, l2, c2, mid));
    } else { //! split lines
        mid = (l1 + l2) >> 1;
        ans = max(ans, compute(l1, c1, mid, c2));
        ans = max(ans, compute(mid + 1, c1, l2, c2));
        ans = max(ans, split_lines(l1, c1, l2, c2, mid));
    }

    Answer = max(Answer, ans);
    return ans;
}

int main()
{
    freopen("rama.in","r",stdin);
    freopen("rama.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%s\n", s[i] + 1);


    preprocess();
    compute(1, 1, n, m);
    printf("%d", Answer);
    cerr << Answer;

    return 0;
}
