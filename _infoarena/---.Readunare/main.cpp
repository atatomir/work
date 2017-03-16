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

#define maxN 4444

int n, i, a, b;
char s[maxN];

int get_nr() {
    int i;
    int ans = 1;
    int act = 0;

    n = strlen(s + 1);

    if (n == 2)
        return 0;

    for (i = 1; i <= n; i++) {
        if (s[i] == '{')
            act++;
        if (s[i] == '}')
            act--;

        if (act == 1 && s[i] == ',') ans++;
    }

    return ans;
}

void print_nr(int x) {
    printf("{");
    for (int i = x - 1; i >= 0; i--) {
        print_nr(i);
        if (i != 0)
            printf(",");
    }

    printf("}");
}

int main()
{
    freopen("readunare.in","r",stdin);
    freopen("readunare.out","w",stdout);

    scanf("%s", s + 1);
    a = get_nr();
    memset(s, 0, sizeof(s));
    scanf("%s", s + 1);
    b = get_nr();

    print_nr(a + b);



    return 0;
}
