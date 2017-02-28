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
     
    #define maxN 500011
     
    int n, i, cnt;
    char s[maxN], rev[maxN];
    int pr[maxN];
     
    bool le[maxN], ri[maxN];
     
    void solve(char *s, bool *ans) {
        int i, u;
     
        pr[1] = u = 0;
        for (i = 2; i <= n; i++) {
            while (u != 0 && s[i] != s[u + 1]) u = pr[u];
            if (s[i] == s[u + 1]) u++;
            pr[i] = u;
     
            ans[i] = (u != 0 && i % (i - u) == 0);
        }
    }
     
    int main()
    {
      //  freopen("test.in", "r", stdin);
     
        scanf("%s", s + 1);
        n = strlen(s + 1);
     
        for (i = 1; i <= n; i++)
            rev[n - i + 1] = s[i];
     
        solve(s, le);
        solve(rev, ri);
     
        if (le[n] == false) {
            printf("1\n1");
            return 0;
        }
     
        bool same = true;
        for (i = 2; i <= n; i++)
            if (s[i] != s[1])
                same = false;
     
        if (same) {
            printf("%d\n%d", n, 1);
            return 0;
        }
     
        for (i = 1; i < n; i++) {
            if (!le[i] && !ri[n - (i + 1) + 1])
                cnt++;
        }
     
        printf("2\n%d", cnt);
     
        return 0;
    }
