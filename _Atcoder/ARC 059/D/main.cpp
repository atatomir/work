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

#define maxN 100011

int n, i;
char s[maxN];
int sum[maxN], best[maxN];

void check(char c) {
    int i;

    for (i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + (s[i] == c ? 1 : -1);
        best[i] = min(best[i - 1], sum[i]);

        if (i >= 2) {
            if (best[i - 2] < sum[i]) {

                for (int j = 0; j <= i - 2; j++) {
                    if (sum[j] < sum[i]) {
                        printf("%d %d", j + 1, i);
                        exit(0);
                    }
                }

            }
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    for (char c = 'a'; c <= 'z'; c++)
        check(c);

    printf("-1 -1");


    return 0;
}
