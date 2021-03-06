// Mircea Popoveniuc - 100 de puncte - O(M log M)
#include<bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;
const int VMAX = 1e6;

void insert(int);
void erase(int);
void undo(int);
int count(int);

int N, top;
vector<int> S;
vector<int> poz[VMAX + 5];

int main() {
	cin.sync_with_stdio(false);

	#ifndef ONLINE_JUDGE
	freopen("undo2.in", "r", stdin);
	freopen("undo2.out", "w", stdout);
	#endif

	scanf("%d", &N);

	for(int op, x; N--; ) {	
		scanf("%d%d", &op, &x);
		if (op == 1) insert(x);
		else if (op == 2) erase(x);
		else if (op == 3) undo(x);
		else if (op == 4) printf("%d\n", count(x));
	}

	return 0;
}

void insert(int x) {
	while (top < (int)S.size()) {
		poz[S.back()].pop_back();
		S.pop_back();
	}
	poz[x].push_back(++top);
	S.push_back(x);
}

void erase(int x) {
	top -= x;
}

void undo(int x) {
	top += x;
}

int count(int x) {
	return (int)(upper_bound(poz[x].begin(), poz[x].end(), top) - poz[x].begin());
}
