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

const int maxN = 55;

int a, b, c, i, bg;
int full, part;

int main()
{
    freopen("test.in","r",stdin);

    cin >> a >> b >> c;
    bg = max(max(a, b), c);

    for (; ; bg++) {
        full = part = 0;

        full += (bg - a) / 2;
        part += (bg - a) % 2;

        full += (bg - b) / 2;
        part += (bg - b) % 2;

        full += (bg - c) / 2;
        part += (bg - c) % 2;

        if (part % 2) continue;
        cout << full + (part / 2);
        return 0;
    }

    return 0;
}
