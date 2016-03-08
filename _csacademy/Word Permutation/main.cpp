#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i;
pair<string, int> work[maxN];
int ind[maxN];

bool cmp(int a, int b) {
    return work[a].first < work[b].first;
}

int main() {
    
    /*
    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> work[i].first;
        work[i].second = i;
    }
    
    sort(work + 1, work + n + 1);
    for (i = 1; i <= n; i++) printf("%d ", work[i].second);
    */
    
    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> work[i].first;
        ind[i] = i;
    }
    
    sort(ind + 1, ind + n + 1, cmp);
    for (i = 1; i <= n; i++) printf("%d ", ind[i]);
    
    
}

