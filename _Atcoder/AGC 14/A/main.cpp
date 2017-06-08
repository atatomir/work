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

ll A, B, C, sum;
int ans;

int main()
{
    //freopen("test.in","r",stdin);

    cin >> A >> B >> C;

    while (A % 2 == 0 && B % 2 == 0 && C % 2 == 0) {
        if (A == B && B == C) {
            cout << "-1";
            return 0;
        }

        ans++;

        sum = A + B + C;
        A = (sum - A) / 2;
        B = (sum - B) / 2;
        C = (sum - C) / 2;
    }

    cout << ans;


    return 0;
}
