#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 4018

int A, B, i, n;
stack<int> S;
int ans[maxN];

int ask(int a, int b) {
    printf("? %d %d\n", a - 1, b - 1);
    fflush(stdout);

    char c;
    cin >> c;

    if (c == 'Y')
        return 1;
    else
        return 0;
}

int main()
{

    cin >> A >> B; n = A + B;
    if (A <= B) {
        printf("Impossible\n");
        fflush(stdout);
        return 0;
    }

    for (i = 1; i <= n; i++) {
        if (S.empty()) {
            S.push(i);
        } else {
            if (ask(S.top(), i)) {
                S.push(i);
            } else {
                S.pop();
            }
        }
    }

    int R = S.top();
    for (i = 1; i <= n; i++)
        ans[i] = ask(R, i);

    printf("! ");
    for (i = 1; i <= n; i++)
        printf("%d", ans[i]);
    printf("\n");
    fflush(stdout);


    return 0;
}
