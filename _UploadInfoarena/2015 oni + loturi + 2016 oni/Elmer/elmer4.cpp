// Popoveniuc Mircea - O(N*M*VMAX) - 15p
#include<bits/stdc++.h>

using namespace std;

const int VMAX = 1000;
const int NMAX = 50;
const int MMAX = 50;

void read();
void solve();
void print();

int N, M, sol;
vector<pair<int, int>> ducks, walls;

int cp(pair<int, int> A, pair<int, int> B, pair<int, int> C) {
	return (A.first - C.first) * 1LL * (B.second - C.second) - (A.second - C.second) * 1LL * (B.first - C.first);
}

bool intersect(pair<int, int> wall, pair<int, int> duck, pair<int, int> hunter) {
	if ((hunter <= wall && wall <= duck) || (hunter >= wall && wall >= duck)) {
		if (hunter >= duck) return (cp(hunter, duck, wall) < 0);
		else return (cp(hunter, duck, wall) > 0);
	}
	return false;
}

int main() {
	freopen("elmer.in", "r", stdin);
	freopen("elmer.out", "w", stdout);

	read();
	solve();
	print();

	return 0;
}

void read() {
	scanf("%d", &N);

	assert(1 <= N && N <= 1000);

	for (int i = 1, x, y; i <= N; i++) {
		scanf("%d%d", &x, &y);
		assert(1 <= x && x <= 1e9);
		assert(1 <= y && y <= 1e9);
		ducks.push_back(make_pair(x, y));
	}

	scanf("%d", &M);

	assert(1 <= M && M <= 1000);

	for (int i = 1, x, h; i <= M; i++) {
		scanf("%d%d", &x, &h);
		assert(1 <= x && x <= 1e9);
		assert(1 <= h && h <= 1e9);
		walls.push_back(make_pair(x, h));
	}
}

void solve() {
	for (int x = 1; x <= VMAX; x++) {
		int hit = 0;

		for (auto duck = ducks.begin(); duck != ducks.end(); duck++) {
			int w = 0;

			for (auto wall = walls.begin(); wall != walls.end(); wall++) {
				if (wall->first == x) w++;
				else if (intersect(*wall, *duck, make_pair(x, 0))) w++;
			}

			if (!w) hit++;
		}
		sol = max(sol, hit);
	}
}

void print() {
	printf("%d\n", sol);
}
