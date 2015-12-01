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

int n, m, i, j;
char s[maxN][maxN];
int ll[maxN][maxN], rr[maxN][maxN], uu[maxN][maxN], dd[maxN][maxN];
int Answer;

int on_left[maxN][maxN];
int on_right[maxN][maxN];

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
    int i, j, k, s, d;

    int ans = 0;
    for (i = l1; i < l2; i++)
        for (j = i + 1; j <= l2; j++)
            on_left[i][j] = on_right[i][j] = 0;

    for (i = l1; i < l2; i++) {
        s = mid - ll[i][mid] + 1;
        d = mid + rr[i][mid + 1];

        for (j = i + 1; j <= l2; j++) {
            while (j - uu[j][s] > i && s <= mid) s++;
            while (j - uu[j][d] > i && d >  mid) d--;

            if (mid - ll[j][mid] + 1 <= s)
                on_left[i][j] = s;
            if (mid + rr[j][mid + 1] >= d)
                on_right[i][j] = d;
        }
    }

    //! now from down...

    for (i = l2; i > l1; i--) {
        s = mid - ll[i][mid] + 1;
        d = mid + rr[i][mid + 1];

        for (j = i - 1; j >= l1; j--) {
            while (j + dd[j][s] <= i && s <= mid) s++;
            while (j + dd[j][d] <= i && d >  mid) d--;

            if (mid - ll[j][mid] + 1 <= s)
                on_left[j][i] = s;
            if (mid + rr[j][mid + 1] >= d)
                on_right[j][i] = d;
        }
    }

    for (i = l1; i < l2; i++)
        for (j = i + 1; j <= l2; j++)
            if (on_left[i][j] <= mid && on_right[i][j] > mid)
                ans = max(ans, (j - i + 1) * (on_right[i][j] - on_left[i][j] + 1) );

    return ans;
}

int split_lines(int l1, int c1, int l2, int c2, int mid) {
    int i, j, k;
    int s, d;

    int ans = 0;
    for (i = c1; i < c2; i++)
        for (j = i + 1; j <= c2; j++)
            on_left[i][j] = on_right[i][j] = 0;

    for (i = c1; i < c2; i++) {
        //! s - up, d - down
        s = mid - uu[mid][i] + 1;
        d = mid + dd[mid + 1][i];

        for (j = i + 1; j <= c2; j++) {
            while (j - ll[s][j] >= i && s <= mid) s++;
            while (j - ll[d][j] >= i && d >  mid) d--;

            if (mid - uu[mid][j] < s)
                on_left[i][j] = s;
            if (mid + dd[mid + 1][j] >= d)
                on_right[i][j] = d;
        }
    }

    //! now from right...

    for (i = c2; i > c1; i--) {
        s = mid - uu[mid][i] + 1;
        d = mid + dd[mid + 1][i];

        for (j = i - 1; j >= c1; j--) {
            while (j + rr[s][j] <= i && s <= mid) s++;
            while (j + rr[d][j] <= i && d >  mid) d--;

            if (mid - uu[mid][j] < s)
                on_left[j][i] = s;
            if (mid + dd[mid + 1][j] >= d)
                on_right[j][i] = d;
        }
    }

    for (i = c1; i < c2; i++)
        for (j = i + 1; j <= c2; j++)
            if (on_left[i][j] <= mid && on_right[i][j] > mid)
                ans = max(ans, (j - i + 1) * (on_right[i][j] - on_left[i][j] + 1) );

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
