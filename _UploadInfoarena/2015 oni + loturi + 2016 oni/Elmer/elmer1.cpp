// Popoveniuc Mircea - O((N*M)*log(N*M)) - 100p
#include<bits/stdc++.h>

using namespace std;

typedef long long int lld;
typedef pair<lld, lld> Point;
const lld INF = (1LL << 60) - 1;
const lld NMAX = 1e3;
const lld MMAX = 1e3;

void read();
void solve();
void print();

int N, M, sol;
vector<Point> ducks;
vector<Point> walls;
vector<Point> E;

struct eventCmp {
	bool operator()(const Point& e1, const Point &e2) const {
		if (e1.first == e2.first)
			return e1.second > e2.second;
		return e1.first < e2.first;
	}
};

lld cp(Point& A, Point& B, Point& C) {
	return (A.first - C.first) * 1LL * (B.second - C.second) - (A.second - C.second) * 1LL * (B.first - C.first);
}

lld find_min_pos(Point& duck, vector<Point>& S) {
	if (duck.second <= S[0].second)
		return INF;
	double x = (S[0].first * 1LL * duck.second - duck.first * 1LL * S[0].second) * 1.0 / (duck.second - S[0].second);
	return (fabs(x) - (lld)x <= 1e-6) ? x : x + 1.0;
}

lld find_max_pos(Point& duck, vector<Point>& S) {
	if (duck.second <= S[0].second)
		return -INF;
	double x = (S[0].first * 1LL * duck.second - duck.first * 1LL * S[0].second) * 1.0 / (duck.second - S[0].second);
	return x;
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
		assert(1 <= x && x <= 1000000000);
		assert(1 <= y && y <= 1000000000);
		ducks.push_back(make_pair(x, y));
	}

	walls.push_back(make_pair(0, 0));

	scanf("%d", &M);

	assert(1 <= M && M <= 1000);

	for (int i = 1, x, h; i <= M; i++) {
		scanf("%d%d", &x, &h);
		assert(1 <= x && x <= 1000000000);
		assert(1 <= h && h <= 1000000000);
		walls.push_back(make_pair(x, h));
	}

	M += 2;

	walls.push_back(make_pair(INF, 0));
}

void solve() {
	lld L[NMAX + 5];
	lld R[NMAX + 5];

	sort(ducks.begin(), ducks.end());
	sort(walls.begin(), walls.end());

	for (int i = 0; i < N; i++) {
		Point duck = ducks[i];

		int lb = (int)(lower_bound(walls.begin(), walls.end(), duck) - walls.begin());
		vector<Point> S;

		for (int j = lb; j < M; j++) {
			Point wall = walls[j];

			while (!S.empty() && cp(duck, S.back(), wall) >= 0)
				S.pop_back();
			S.push_back(wall);

			L[j] = find_min_pos(duck, S);
			R[j] = INF - 1;
		}

		S.clear();

		for (int j = lb - 1; j >= 0; j--) {
			Point wall = walls[j];

			while (!S.empty() && cp(duck, S.back(), wall) <= 0)
				S.pop_back();
			S.push_back(wall);

			L[j] = -INF + 1;
			R[j] = find_max_pos(duck, S);
		}

		for (int j = 0; j + 1 < M; j++) {
			lld l, r;

			l = max(walls[j].first + 1LL, L[j]);
			r = min(walls[j + 1].first - 1LL, R[j + 1]);

			if (l <= r) {
				E.push_back(make_pair(l, 1));
				E.push_back(make_pair(r, -1));
			}
		}
	}

	sort(E.begin(), E.end(), eventCmp());

	int hit = 0;

	for (auto event = E.begin(); event != E.end(); event++) {
		hit += event->second;
		sol = max(sol, hit);
	}
}

void print() {
	printf("%d\n", sol);
}
