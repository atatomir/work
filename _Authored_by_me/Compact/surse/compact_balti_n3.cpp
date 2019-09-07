// Complexitate O(n ^ 3)
#include <bits/stdc++.h>
using namespace std;

vector<int> make_dp(int n, int lim, vector<int>& a)
{
    vector<int> dp(n + 5, 0);
    vector<int> prev(n + 5, 0);
    // for every [i, j] see if it's stable in O(n)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) 
        {
            // compute min and max
            int mn = lim + 1, mx = -1;
            for (int k = j; k <= i; k++)
            {
                mn = min(mn, a[k]);
                mx = max(mx, a[k]);
            }

            bool stable = 1;
            for (int k = 1; k < j; k++)
                if (mn <= a[k] && a[k] <= mx)
                    stable = 0;
            for (int k = i + 1; k <= n; k++)
                if (mn <= a[k] && a[k] <= mx)
                    stable = 0;
                
            if (stable && (j == 1 || (j > 1 && dp[j - 1] > 0)))
                if (dp[j - 1] + 1 > dp[i])
                {
                    dp[i] = dp[j - 1] + 1;
                    prev[i] = j - 1;
                }
        }
    
    vector<int> ans;
    for (int i = n; i > 0; i = prev[i])
        ans.push_back(i);
    reverse(ans.begin(), ans.end());

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