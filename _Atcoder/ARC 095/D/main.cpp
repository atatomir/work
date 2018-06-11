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

int n, i, A, B, mid, mid2;
vector<int> data;
pair<int, int> best;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    data.resize(n);
    for (auto& e: data) scanf("%d", &e);
    sort(data.begin(), data.end());

    A = data.back();
    mid = A / 2;
    mid2 = (A + 1) / 2;

    best = mp(A + 3, -1);
    for (auto e : data) {
        if (e == A) continue;

        if (e <= mid) {
            best = min(best, mp(mid - e, e));
        } else {
            best = min(best, mp(e - mid2, e));
        }
    }

    B = best.second;
    printf("%d %d", A, B);


    return 0;
}
