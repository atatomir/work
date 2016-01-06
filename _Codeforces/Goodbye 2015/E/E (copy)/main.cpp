#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int n, i, pos;
int a, b, c, x, all_sum;

vector<int> limit;
int cnt[10];

int answer;

void solve(int v1, int v2, int v3) {
    int pos1 = 0;
    while (limit[pos1] < v1) pos1++;

    int pos2 = 0;
    while (limit[pos2] < v2) pos2++;

    int pos3 = 0;
    while (limit[pos3] < v3) pos3++;

    while (true) {
        //! il extrag pe al treilea
        while (cnt[pos3] == 0) {
            if (--pos3 < 0) {
                return;
            }
        }

        cnt[pos3]--;

        //! il extrag pe al doilea
        while (cnt[pos2] == 0) {
            if (--pos2 < 0) {
                cnt[pos3]++;
                return;
            }
        }

        cnt[pos2]--;

        //! il extrag pe primul
        while (cnt[pos1] == 0) {
            if (--pos1 < 0) {
                cnt[pos2]++;
                cnt[pos3]++;
                return;
            }
        }

        cnt[pos1]--;

        //! adaug solutia
        answer++;
    }
}

void solve(int v1, int v2) {
    if (v1 > v2) swap(v1, v2);

    int pos1 = 0;
    while (limit[pos1] < v1) pos1++;

    int pos2 = 0;
    while (limit[pos2] < v2) pos2++;

    while (true) {
        //! il extrag pe al doilea
        while (cnt[pos2] == 0) {
            if (--pos2 < 0) {
                return;
            }
        }

        cnt[pos2]--;

        //! il extrag pe primul
        while (cnt[pos1] == 0) {
            if (--pos1 < 0) {
                cnt[pos2]++;
                return;
            }
        }

        cnt[pos1]--;

        //! adaug solutia
        answer++;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d%d", &n, &a, &b, &c);

    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);

    limit = {a, b, c, a + b, a + c, c + b};
    sort(limit.begin(), limit.end());
    limit.resize( unique(limit.begin(), limit.end()) - limit.begin() );

    all_sum = a + b + c;

    for (i = 1; i <= n; i++) {
        scanf("%d", &x);

        if (x > all_sum) {
            printf("-1");
            return 0;
        }

        if (x > limit[limit.size() - 1]) {
            answer++;
        } else {
            pos = 0;
            while (limit[pos] < x) pos++;
            cnt[pos]++;
        }
    }

    solve(a, b, c);
    solve(a + b, c);
    solve(a + c, b);
    solve(b + c, a);

    for (i = 0; i < limit.size(); i++)
        answer += cnt[i];

    printf("%d", answer);

    return 0;
}
