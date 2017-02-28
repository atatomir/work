    #include <iostream>
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    #include <vector>
    #include <cmath>
     
    using namespace std;
     
    #define ll long long
    #define mp make_pair
    #define pb push_back
     
    #define maxN 100011
     
    int n, i, pos, cnt;
    int a[maxN];
    vector<int> ord[2], need, aux;
     
    int main()
    {
    //    freopen("test.in", "r", stdin);
     
        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d", &a[i]), ord[i & 1].pb(a[i]);
     
        sort(ord[0].begin(), ord[0].end());
        sort(ord[1].begin(), ord[1].end());
        sort(a + 1, a + n + 1);
        for (i = 1; i <= n; i += 2) need.pb(a[i]);
     
        aux = ord[1]; pos = 0;
        for (i = 0; i < aux.size(); i++) {
            while (pos < need.size()) {
                if (need[pos] >= aux[i]) break;
                pos++;
            }
     
            if (pos < need.size()) {
                if (need[pos] == aux[i]) {
                    pos++;
                    cnt++;
                }
            }
        }
     
        printf("%d", aux.size() - cnt);
     
     
        return 0;
    }
