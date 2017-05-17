#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.ok", "w", stdout);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vii items;
	while (n--) {
		ll w, c;
		cin >> w >> c;
		items.push_back({c, w});
	}
	sort(items.begin(), items.end(), [](const ii& l, const ii& r) {
		return l.first*r.second < r.first*l.second;
	});
	
	ll ans = 0LL;
	while (m >= 100 && !items.empty())
		ans += items.back().first,
		m -= (int)items.back().second,
		items.pop_back(); 
	
	vi dp(m+1, 0LL);
	for (size_t i = 0; i < items.size(); ++i) {
		ll c = items[i].first;
		int tw = items[i].second;
		for (int w = m - tw; w >= 0; --w)
			if (dp[w+tw]<dp[w]+c)
				dp[w+tw] = dp[w]+c;
	}
	ll best = 0LL;
	for (ll v : dp) best = max(v, best);
	cout << ans+best << endl;
	
	return 0;
}
