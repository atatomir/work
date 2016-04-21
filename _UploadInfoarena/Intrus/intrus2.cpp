// Mircea Popoveniuc - 100 de puncte - O(N * M * D^2)
#include<bits/stdc++.h>

using namespace std;

#define dbg(x) (cout<<#x<<" = "<<(x)<<'\n')

const int NMAX = 1e3;
const int VMAX = 1e6;

int cerinta, R, C, D;
bitset < VMAX + 5 > neprim;
int grid[NMAX + 5][NMAX + 5];
int S[NMAX + 5][NMAX + 5];
int freq[VMAX + 5];
vector<pair<pair<int, int>, pair<int, int> > > suspecti;

bool cmp(pair<pair<int, int>, pair<int, int> > A, pair<pair<int, int>, pair<int, int> > B) {
	if (A.first == B.first)
		return A.second < B.second;
	return A.first > B.first;
}

void ciur() {
	neprim[0] = neprim[1] = 1;

	for (int i = 4; i <= 1e6; i += 2)
		neprim[i] = 1;

	for (int i = 3; i * i <= 1e6; i += 2)
		if (!neprim[i])
			for (int j = 2 * i; j <= 1e6; j += i)
				neprim[j] = 1;
}

void sume_partiale() {
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + (!neprim[grid[i][j]]);
}

int vipmax(int x, int y, int xmin, int ymin, int xmax, int ymax) {
	int val = 0;
	for (int i = xmin; i <= xmax; i++)
		for (int j = ymin; j <= ymax; j++)
			if ((i != x || j != y) && !neprim[grid[i][j]])
				val = max(val, grid[i][j]);
	return val;
}

int main() {
	cin.sync_with_stdio(false);

	#ifndef ONLINE_JUDGE
	freopen("intrus.in", "r", stdin);
	freopen("intrus.out", "w", stdout);
	#endif

	scanf("%d", &cerinta);
	scanf("%d%d%d", &R, &C, &D);

	assert(1 <= R && R <= 1000);
	assert(1 <= C && C <= 1000);
	assert(3 <= D && D <= 9 && (D % 2));

	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++) {
			scanf("%d", &grid[i][j]);
			assert(0 <= grid[i][j] && grid[i][j] <= 999999);
			if (grid[i][j]) freq[grid[i][j]]++;
		}

	ciur();
	sume_partiale();

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++)
			if (freq[grid[i][j]] > 1) {
				int xmin = max(i - D / 2, 1);
				int ymin = max(j - D / 2, 1);
				int xmax = min(i + D / 2, R);
				int ymax = min(j + D / 2, C);
				int vip = S[xmax][ymax] - S[xmin - 1][ymax] - S[xmax][ymin - 1] + S[xmin - 1][ymin - 1] - !(neprim[grid[i][j]]);
				suspecti.push_back(make_pair(make_pair(vip, vipmax(i, j, xmin, ymin, xmax, ymax)), make_pair(i, j)));
			}
	}

	if (cerinta == 1) {
		printf("%d\n", (int)suspecti.size());

	} else {
		sort(suspecti.begin(), suspecti.end(), cmp);

		for (int i = 0, x, y; i < (int)suspecti.size(); i++) {
			x = suspecti[i].second.first;
			y = suspecti[i].second.second;
			printf("%d %d %d\n", grid[x][y], x, y);
			//printf("%d %d | %d %d\n", suspecti[i].first.first, suspecti[i].first.second, x, y);
		}

		if (suspecti.empty())
			printf("-1\n");
	}

	return 0;
}
