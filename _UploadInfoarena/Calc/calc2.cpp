// Mircea Popoveniuc - 100 de puncte - Complexitate O(N)
#include<bits/stdc++.h>

using namespace std;

typedef long long int lld;
const int INF = (1LL << 30) - 1;
const lld LINF = (1LL << 62) - 1;
const int MOD =  (int)1e9 + 7;
const int NMAX = 1e5;

int cerinta, N;
char numar[NMAX + 5];
char prevNr[NMAX + 5];
char nextNr[NMAX + 5];

void solve_a();
void solve_b();
void do_prev();
void do_next();

int main() {
	freopen("calc.in", "r", stdin);
	freopen("calc.out", "w", stdout);

	scanf("%d", &cerinta);
	scanf("%d", &N);
	scanf("%s", numar + 1);

	if (cerinta == 1) solve_a();
	else solve_b();

	return 0;
}

void solve_a() {
	int a = 0, b = 1;

	for (int i = 1, c; i <= N; i++) {
		c = (a + b) % MOD;
		a = b;
		b = c;
	}

	printf("%d\n", b);
}

void solve_b() {
	do_prev();
	do_next();
}

void do_prev() {
	strcpy(nextNr + 1, numar + 1);

	int zero = 0;
	for (int i = N; i >= 1; i--)
		if (numar[i] == '0') zero++;
		else break;

	if (zero == N)
		strcpy(nextNr + 1, "-1");

	else if (zero) {
		for (int i = N; i >= N - zero + 2; i--)
			nextNr[i] = '1';
		nextNr[N - zero] = nextNr[N - zero + 1] = '0';

	}  else if (numar[N] == '1' && numar[N - 1] == '1')
		nextNr[N] = nextNr[N - 1] = '0';

	else {
		zero = 0;
		for (int i = N - 1; i >= 1; i--)
			if (numar[i] == '0') zero++;
			else break;

		if (zero == N - 1)
			strcpy(nextNr + 1, "-1");

		else {
			for (int i = N; i >= N - zero + 1; i--)
				nextNr[i] = '1';
			nextNr[N - zero - 1] = nextNr[N - zero] = '0';
		}
	}

	printf("%s\n", nextNr + 1);
}

void do_next() {
	strcpy(prevNr + 1, numar + 1);

	int unu = 0;
	for (int i = N; i >= 1; i--)
		if (numar[i] == '1') unu++;
		else break;

	if (unu == N)
		strcpy(prevNr + 1, "-1");

	else if (unu % 2 == 0 && unu) {
		for (int i = N - 1; i >= N - unu; i--)
			prevNr[i] = '0';
		prevNr[N - unu - 1] = '1';

	} else if (unu % 2 == 1 && unu) {
		for (int i = N; i >= N - unu; i--)
			prevNr[i] = '0';
		prevNr[N - unu - 1] = '1';

	} else if (numar[N] == '0' && numar[N - 1] == '0')
		prevNr[N] = prevNr[N - 1] = '1';

	printf("%s\n", prevNr + 1);
}
