// Complexitate O(n ^ 3) optimizat
#include <bits/stdc++.h>
using namespace std;

struct elem
{
    int val, l, r;
    elem(int _val, int _l, int _r)
    {
        val = _val;
        l = _l;
        r = _r;
    }
};

vector<int> make_dp(int n, int lim, vector<int>& a)
{
    vector<int> dp(n + 5, 0), prev(n + 5, 0);
    vector<elem> poz;

    // preprocess
    vector<pair<int, int> > b;
    for (int i = 0; i < a.size(); i++)
        b.push_back(make_pair(a[i], i));
    sort(b.begin(), b.end());
    for (int i = 0; i < b.size(); i++)
    {
        int ind = i, mn = b[i].second, mx = b[i].second;
        while (ind + 1 < b.size() && b[ind + 1].first == b[ind].first)
        {
            ind++;
            mn = min(mn, b[ind].second);
            mx = max(mx, b[i].second);
        }
        poz.push_back(elem(b[i].first, mn, mx));
        i = ind;
    }

    // for every [i, j] see if it's stable in O(n)
    for (int i = 1; i <= n; i++)
    {
        int mn = lim + 1, mx = -1;
        for (int j = i; j >= 1; j--) 
        {
            // update min and max
            mn = min(mn, a[j]);
            mx = max(mx, a[j]);

            // check stability
            bool stable = 1;
            int st = 0, dr = poz.size() - 1, ind = poz.size();
            while (st <= dr)
            {
                int mij = (st + dr) / 2;
                if (poz[mij].val >= mn)
                {
                    ind = mij;
                    dr = mij - 1;
                }
                else st = mij + 1;
            }
            while (ind < poz.size() && poz[ind].val <= mx && stable)
            {
                if (!(j <= poz[ind].l && poz[ind].r <= i))
                    stable = 0;
                ind++;
            }

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