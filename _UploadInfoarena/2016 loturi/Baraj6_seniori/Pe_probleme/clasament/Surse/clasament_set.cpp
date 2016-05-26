#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define int int64_t

const int INF = 1e16;

vector<int> permHash;
const vector<int> primes = {rand() / 4, rand() / 4, rand() / 4, rand() / 4, rand() / 4, rand() / 4, rand() / 4, rand() / 4, rand() / 4};

map<vector<int>, int> Map;
int V[100005], I[100005];

struct cmp {
	bool operator() (const int &a, const int &b) const {
		return make_pair(-V[a], I[a]) < make_pair(-V[b], I[b]);
	}
};
set<int, cmp> Set;

vector<int> Hash(int a, int b) {
	vector<int> res(primes);
	for(auto &prime : res) 
		prime = (123LL * a * b % prime + 7LL * b % prime + 3LL * a) % prime;		
		//prime = (11498712LL * a % prime * b % prime + 2345LL * a % prime + 6654LL * b + 432432LL * a % prime * a % prime + 129841LL * b % prime * b % prime) % prime;
	return res;
}

void add(const vector<int>& what) {
	for(int i = 0; i < permHash.size(); ++i) {
		permHash[i] += what[i];
		while(permHash[i] >= primes[i])
			permHash[i] -= primes[i];
	}
}
void sub(const vector<int>& what) {
	for(int i = 0; i < permHash.size(); ++i) {
		permHash[i] -= what[i];
		while(permHash[i] < 0)
			permHash[i] += primes[i];
	}
}

void Insert(int i) {
	auto it = Set.insert(i).first;

	auto pred = it, succ = it;
	--pred; ++succ;

	add(Hash(*pred, *it));
	add(Hash(*it, *succ));
	sub(Hash(*pred, *succ));
}

void Erase(int i) {
	auto it = Set.find(i);

	auto pred = it, succ = it;
	--pred; ++succ;

	sub(Hash(*pred, *it));
	sub(Hash(*it, *succ));
	add(Hash(*pred, *succ));

	Set.erase(it);
}


int32_t main() {
	ifstream cin("clasament.in");
	ofstream cout("clasament.out");


	int n, q, a, b;
	cin >> n >> q;


	V[0] = -INF;
	I[0] = 1;
	V[n + 1] = INF;
	I[n + 1] = 2;

	Set.insert(0);
	Set.insert(n + 1);
	permHash = Hash(0, n + 1);

	int shit = 2;

	for(int i = 1; i <= n; ++i) {
		cin >> V[i];
		I[i] = ++shit;
		Insert(i);
	}

	Map[permHash]++;
	while(q--) {
		cin >> a >> b;

		Erase(a);
		V[a] = b;
		I[a] = ++shit;
		Insert(a);

		cout << (Map[permHash]++) << '\n';
	}
	return 0;
}
