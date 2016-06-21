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
  
int n, a, b, i, j, v;
vector< pair<int, int> > ans, aux;
  
void nosol() {
    printf("-1");
    exit(0);
}
  
void reverse_it() {
    for (i = 0; i < ans.size(); i++)
        if (ans[i].first > ans[i].second)
            swap(ans[i].first, ans[i].second);
  
    aux = ans;
    ans.clear();
    sort(aux.begin(), aux.end());
    reverse(aux.begin(), aux.end());
  
    for (i = 1; i < n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (!aux.empty())
                if (aux.back() == mp(i, j))
                    {aux.pop_back(); continue;}
  
            ans.pb(mp(i, j));
        }
    }
}
  
int main()
{
    freopen("grafc.in","r",stdin);
    freopen("grafc.out","w",stdout);
  
    scanf("%d%d%d", &n, &a, &b);
  
    if (a > n || b > n) nosol();
    if (a > 1 && b > 1) nosol();
  
    if (a == 1 && b == 1) {
    if (n == 1) {
        printf("0");
        return 0;
    }
        if (n <= 3) nosol();
  
        for (i = 1; i < n; i++)
            ans.pb(mp(i, i + 1));
    } else {
        v = max(a, b);
  
        for (i = 1; n - i >= v; i++) ans.pb(mp(i, i + 1));
        if (b > 1) reverse_it();
    }
  
    for (i = 0; i < ans.size(); i++)
        if (ans[i].first > ans[i].second)
            swap(ans[i].first, ans[i].second);
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  
    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d %d\n", e.first, e.second);
  
    return 0;
}
