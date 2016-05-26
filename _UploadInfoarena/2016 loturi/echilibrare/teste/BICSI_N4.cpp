// N^4 solution
// With hungarian algorithm

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

const int MAXN = 256;

int G[MAXN][MAXN], Gp[MAXN][MAXN];
int Left[MAXN], Right[MAXN];
bool Viz[MAXN], InVL[MAXN], InVR[MAXN];
int PotL[MAXN], PotR[MAXN];

int n;

#define arr_dump(x, n) {cerr<<#x<<"[]: ";for(int i=1; i<=n; ++i) cerr<<x[i]<<" ";cerr<<'\n';}

void Preprocess() {
	// Find maximum value and transform graph
	int max_v = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			Gp[i][j] = G[i][j];
			max_v = max(max_v, G[i][j]);
		}

	// Subtract min from all rows
	for(int i = 1; i <= n; ++i) {
		int min_l = 1e9 + 10;
		for(int j = 1; j <= n; ++j) {
			Gp[i][j] = max_v - Gp[i][j];
			min_l = min(min_l, Gp[i][j]);
		}

		for(int j = 1; j <= n; ++j) 
			Gp[i][j] -= min_l;
		
		// Initialize potential
		PotL[i] = 2 * (max_v - min_l);
	}
}

bool Match(int i) {
	if(Viz[i]) return false;

	Viz[i] = 1;
	for(int j = 1; j <= n; ++j) {
		if(Gp[i][j]) continue;

		if(!Left[j] || Match(Left[j])) {
			Right[i] = j;
			Left[j] = i;
			return true;
		}
	}
	return false;
}

void Support(int i) {
	for(int j = 1; j <= n; ++j) {
		if(Gp[i][j]) continue;

		if(!InVR[j]) {
			InVR[j] = 1;
			InVL[Left[j]] = 0;

			Support(Left[j]);
		}
	}
}

void Hungarian() {

	// Matchup
	memset(Viz, 0, sizeof(Viz));
	memset(InVR, 0, sizeof(InVR));

	bool ok = true;
	for(int i = 1; i <= n; ++i)
		if(!Right[i])
			ok &= Match(i);

	if(ok) return;

	// Make vertex cover
	for(int i = 1; i <= n; ++i)
		InVL[i] = (Right[i] != 0);

	for(int i = 1; i <= n; ++i)
		if(!InVL[i])
			Support(i);

	// Find minimum value amongst non-support edges
	int min_v = 1e9 + 10;
	for(int i = 1; i <= n; ++i) if(!InVL[i])
		for(int j = 1; j <= n; ++j) if(!InVR[j]) {
			min_v = min(min_v, Gp[i][j]);
		}

	// Update the matrix values
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			if(!InVL[i] && !InVR[j]) Gp[i][j] -= min_v;
			if( InVL[i] &&  InVR[j]) Gp[i][j] += min_v;
		}

	// Update potentials
	for(int i = 1; i <= n; ++i) {
		if(!InVL[i]) PotL[i] -= min_v;
		else 		 PotL[i] += min_v;

		if(!InVR[i]) PotR[i] -= min_v;
		else		 PotR[i] += min_v;
	}
	
	// Recall
	Hungarian();
}

int main() {
	freopen("echilibrare.in", "r", stdin);
	freopen("echilibrare.out", "w", stdout);
	
	cin >> n;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> G[i][j];

	Preprocess();
	Hungarian();

	int ans = 0;
	for(int i = 1; i <= n; ++i)
		ans += G[i][Right[i]];

	cout << ans * n << '\n';
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			assert((PotL[i] + PotR[j]) % 2 == 0);
			cout << (PotL[i] + PotR[j]) / 2 << " ";
		}
		cout << '\n';
	}
 
    return 0;
}
