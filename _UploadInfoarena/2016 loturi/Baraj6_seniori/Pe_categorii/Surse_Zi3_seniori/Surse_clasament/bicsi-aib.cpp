#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>

using namespace std;

const int MAXN = 100005;
const int64_t B = 989171;

vector<pair<int, int>> Norm, Queries;
int V[MAXN], Old[MAXN];

map<int64_t, int> Map;

int timer = 0;


void addHash(int val) {
	Norm.emplace_back(-val, ++timer);
}

int getHash(int val) {
	pair<int, int> p(-val, ++timer);
	auto it = upper_bound(Norm.begin(), Norm.end(), p);
	return it - Norm.begin();
}

int64_t permHash = 0;
int totCount = 0;

int Cnt[600005];
int64_t Sum[600005], Pow[600005];

pair<int, int64_t> query(int pos) {
	int cnt = 0;
	int64_t sum = 0;
	for(; pos <= Norm.size(); pos += (pos & -pos))
		cnt += Cnt[pos], sum += Sum[pos];
	return make_pair(cnt, sum);
}

void add(int pos, int val) {
	auto p = query(pos);
	permHash += (B - 1) * p.second;
	permHash += Pow[totCount - p.first] * val;
	
	for(; pos > 0; pos -= (pos & -pos))
		Cnt[pos] += 1, Sum[pos] += val;
	totCount += 1;
}

void remove(int pos, int val) {
	auto p = query(pos + 1);
	permHash -= (B - 1) * p.second;
	permHash -= Pow[totCount - 1 - p.first] * val;

	for(; pos > 0; pos -= (pos & -pos))
		Cnt[pos] -= 1, Sum[pos] -= val;
	totCount -= 1;
}

int main() {
	
	Pow[0] = 1;
	for(int i = 1; i <= 600000; ++i)
		Pow[i] = Pow[i - 1] * B;

	int n, q;
	cin >> n >> q;

	for(int i = 1; i <= n; ++i) {
		cin >> V[i];
		addHash(V[i]);
	}

	Queries.reserve(q);
	while(q--) {
		int a, b;
		cin >> a >> b;
		Queries.emplace_back(a, b);
		addHash(b);
	}

	sort(Norm.begin(), Norm.end());
	timer = 0;


	for(int i = 1; i <= n; ++i) {
		Old[i] = getHash(V[i]);
		add(Old[i], i);
	}


	Map[permHash] += 1;
	for(auto q : Queries) {
		int newpos = getHash(q.second);

		remove(Old[q.first], q.first);
		add(newpos, q.first);
		Old[q.first] = newpos;

		auto &cnt = Map[permHash];
		cout << cnt << '\n';
		cnt += 1;
	}

	return 0;
}