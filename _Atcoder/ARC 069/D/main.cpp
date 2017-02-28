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

int say[maxN];
int tp[maxN];

void check() {
    for (i = 2; i <= n + 1; i++)
        tp[i + 1] = tp[i] ^ say[i] ^ tp[i - 1];

    if (tp[1] != tp[n + 1]) return;
    if (tp[2] != tp[n + 2]) return;

    for (i = 1; i <= n; i++)
        printf("%c", (tp[i] ? 'W' : 'S'));

    exit(0);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n%s", &n, s + 1);
    s[n + 1] = s[1];
    s[n + 2] = s[2];

    for (i = 1; i <= n + 2; i++) say[i] = (s[i] == 'o' ? 0 : 1);

    tp[1] = 0;
    tp[2] = 0;
    check();

    tp[1] = 0;
    tp[2] = 1;
    check();

    tp[1] = 1;
    tp[2] = 0;
    check();

    tp[1] = 1;
    tp[2] = 1;
    check();

    printf("-1");



    return 0;
}
