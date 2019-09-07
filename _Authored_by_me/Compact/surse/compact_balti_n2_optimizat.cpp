// Complexitate O(n ^ 2)
#include <bits/stdc++.h>
using namespace std;

vector<int> make_dp(int n, int lim, vector<int>& a)
{
    vector<int> dp(n + 5, 0), prev(n + 5, 0);
    vector<pair<int, int> > poz(lim + 5, {n + 1, -1});

    // preprocess
    for (int i = 0; i < a.size(); i++)
    {
        int mn = min(poz[a[i]].first, i);
        int mx = max(poz[a[i]].second, i);
        poz[a[i]] = {mn, mx};
    }

    for (int i = 1; i <= n; i++)
    {
        int mn_val = a[i] + 1, mx_val = a[i];
        int mn_poz = n + 1, mx_poz = -1;
        for (int j = i; j >= 1; j--) 
        {
            // update min poz and max poz in [mn_val, mx_val]
            while (mn_val - 1 >= a[j])
            {
                mn_val--;
                mn_poz = min(mn_poz, poz[mn_val].first);
                mx_poz = max(mx_poz, poz[mn_val].second);
            }

            while (mx_val + 1 <= a[j])
            {
                mx_val++;
                mn_poz = min(mn_poz, poz[mx_val].first);
                mx_poz = max(mx_poz, poz[mx_val].second);
            }

            if (mx_poz > i) // it cannot be solved for all j <= i
                break;

            // update min and max
            mn_val = min(mn_val, a[j]);
            mx_val = max(mx_val, a[j]);

            // check stability
            bool stable = 1;
            if (!(j <= mn_poz && mx_poz <= i))
                stable = 0;

            if (stable && (j == 1 || (j > 1 && dp[j - 1] > 0)))
                if (dp[j - 1] + 1 > dp[i])
                {
                    dp[i] = dp[j - 1] + 1;
                    prev[i] = j - 1;
                }
        }
    }

    vector<int> ans;
    for (int i = n; i > 0; i = prev[i])
        ans.push_back(i);
    std::reverse(ans.begin(), ans.end());

    return ans;
}

int main()
{
    freopen("compact.in", "r", stdin);
    freopen("compact.out", "w", stdout);
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 5, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<int> ans = make_dp(n, m, a);
    cout << ans.size() << "\n";
    for (int poz : ans)
        cout << poz << " ";
    cout << "\n";
    return 0;
}