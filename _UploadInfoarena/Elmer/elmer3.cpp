// Popoveniuc Mircea - O((N*M)^2) - 40p
#include<bits/stdc++.h>

using namespace std;

#define dbg(x) (cout<<#x<<" = "<<(x)<<'\n')

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

lld find_min_pos(Point& duck, Point& wall) {
	if (duck.second <= wall.second)
		return INF;
	double x = (wall.first * 1LL * duck.second - duck.first * 1LL * wall.second) * 1.0 / (duck.second - wall.second);
	return (fabs(x) - (lld)x <= 1e-6) ? x : x + 1.0;
}

lld find_max_pos(Point& duck, Point& wall) {
	if (duck.second <= wall.second)
		return -INF;
	double x = (wall.first * 1LL * duck.second - duck.first * 1LL * wall.second) * 1.0 / (duck.second - wall.second);
	return x;
}

bool intersect(Point wall, Point duck, Point hunter) {
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
		assert(1 <= x && x <= 1000000000);
		assert(1 <= y && y <= 1000000000);
		ducks.push_back(make_pair(x, y));
	}

	scanf("%d", &M);

	assert(1 <= M && M <= 1000);

	for (int i = 1, x, h; i <= M; i++) {
		scanf("%d%d", &x, &h);
		assert(1 <= x && x <= 1000000000);
		assert(1 <= h && h <= 1000000000);
		walls.push_back(make_pair(x, h));
	}
}

int solutie_pe_pozitie(lld x) {
	if (x <= 0) return -1;
	int hit = 0;

	for (auto duck = ducks.begin(); duck != ducks.end(); duck++) {
		int w = 0;

		for (auto wall = walls.begin(); wall != walls.end(); wall++) {
			if (wall->first == x) w++;
			else if (intersect(*wall, *duck, make_pair(x, 0))) w++;
		}

		if (!w) hit++;
	}
	return hit;
}

void solve() {
	sort(ducks.begin(), ducks.end());
	sort(walls.begin(), walls.end());

	for (lld i = 0; i < N; i++) {
		Point duck = ducks[i];

		lld lb = (lld)(lower_bound(walls.begin(), walls.end(), duck) - walls.begin());

		for (lld j = lb; j < M; j++) {
			lld pozitie = find_min_pos(duck, walls[j]);
			sol = max(sol, solutie_pe_pozitie(pozitie));
		}

		for (lld j = lb - 1; j >= 0; j--) {
			lld pozitie = find_max_pos(duck, walls[j]);
			sol = max(sol, solutie_pe_pozitie(pozitie));
		}
	}
}

void print() {
	printf("%d\n", sol);
}
