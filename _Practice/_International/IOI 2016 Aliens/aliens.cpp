#include "aliens.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int N, M, K, i;
pair<int, int> p[maxN];
ll dp[maxN];
int prov[maxN];

int l, r;
int Q[maxN];
int better[maxN];
ll _pay;
ll last_cost;

void convex() {
    int i, j, maxi;
    int pas;

    pas = 0;
    for (i = 1; i <= N; i++)
        if (p[i].first > p[i].second)
            swap(p[i].first, p[i].second);
    sort(p + 1, p + N + 1);

    maxi = 0;
    for (i = 1; i <= N; i++) {
        if (p[i].first == p[i + 1].first && i != N) continue;
        if (p[i].second <= maxi) continue;

        p[++pas] = p[i];
        maxi = p[i].second;
    }

    N = pas;
    K = min(K, N);
}

ll sq(ll x) {
    return max(0LL, x) * max(0LL, x);
}

ll get_cost(int id1, int id2) {
    return dp[id1] - sq(p[id1].second - p[id1 + 1].first + 1) + sq(p[id2].second - p[id1 + 1].first + 1) + _pay;
}

ll when_better(int id1, int id2) {
    int ans = id2;

    for (int step = (1 << 17); step > 0; step >>= 1)
        if (ans + step <= N)
            if (get_cost(id1, ans + step) < get_cost(id2, ans + step))
                ans += step;

    return ans + 1;
}

ll check(ll pay) {
    int i;

    _pay = pay;
    dp[0] = 0;
    Q[l = r = 1] = 0;
    better[0] = 0;

    for (i = 1; i <= N; i++) {
        while (l < r) {
            if (get_cost(Q[l], i) < get_cost(Q[l + 1], i)) break;
            l++;
        }

        prov[i] = Q[l];
        dp[i] = get_cost(Q[l], i);

        while (l <= r) {
            better[i] = when_better(Q[r], i);
            if (better[i] > better[Q[r]]) break;
            r--;
        }

        Q[++r] = i;
        better[i] = max(better[i], i);
    }

    int step = 0;
    for (i = N; i != 0; i = prov[i]) step++;

    if (step >= K)
        last_cost = dp[N] - 1LL * K * pay;

    return step;
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
    p[0] = {0, 0};
    for (i = 1; i <= n; i++)
        p[i] = mp(r[i - 1] + 1, c[i - 1] + 1);

    N = n; M = m;
    K = k;

    convex();
    n = N; k = K;

    ll ans = 0;

    for (ll step = (1LL << 40); step > 0; step >>= 1)
        if (check(ans + step) >= k)
            ans += step;

    ll sol = 1LL << 60;

    check(ans);
    sol = last_cost;

    return sol;
}

// --------------------------------------------------

#define ff first
#define ss second

long long take_photos2(int N, int R, int K, vector<int> x, vector<int> y) {
	vector< pair<int,int> > Iall(N);
	for(int i =0; i < N; i++) {
		Iall[i].ff =min(x[i],y[i]);
		Iall[i].ss =max(x[i],y[i])+1;}
	sort(begin(Iall),end(Iall));
	vector< pair<int,int> > I;
	int rp =-1;
	for(int i =0; i < N; i++) {
		if(i < N-1 && Iall[i].ff == Iall[i+1].ff) continue;
		if(Iall[i].ss <= rp) continue;
		I.push_back(Iall[i]);
		rp =Iall[i].ss;}
	N =I.size();
	K =min(K,N);

	long long ans =1e18;
	long long costA =-1, costB =1e13;
	while(costB-costA > 1) {
		long long cost =(costA+costB)/2;
		vector<long long> A(N+1,1e18);
		vector<int> curK(N+1,0);
		A[0] =0;
		vector< pair<long long,int> > q;
		int a =-1;
		for(int i =0; i < N; i++) {
			long long x =A[i]+1LL*I[i].ff*I[i].ff, y =2*I[i].ff;
			while(q.size() >= 2) {
				long long x2 =q.back().ff, y2 =2*I[q.back().ss].ff;
				long long x1 =q[q.size()-2].ff, y1 =2*I[q[q.size()-2].ss].ff;
				if(1.0*(x2-x1)/(y2-y1) > 1.0*(x-x2)/(y-y2)) q.pop_back();
				else break;}
			a =min(a,(int)q.size()-1);
			q.push_back(make_pair(x,i));
			if(a == -1) a++;
			while(a < (int)q.size()-1) {
				if(q[a].ff-2LL*I[q[a].ss].ff*I[i].ss >= q[a+1].ff-2LL*I[q[a+1].ss].ff*I[i].ss) a++;
				else break;}
			A[i+1] =q[a].ff-2LL*I[q[a].ss].ff*I[i].ss+1LL*I[i].ss*I[i].ss+cost;
			curK[i+1] =curK[q[a].ss]+1;
			if(i < N-1 && I[i+1].ff < I[i].ss)
				A[i+1] -=1LL*(I[i].ss-I[i+1].ff)*(I[i].ss-I[i+1].ff);
			}
		if(curK[N] >= K) {
			costA =cost;
			ans =A[N]-K*cost;}
		else costB =cost;}

	return ans;}



