#include <bits/stdc++.h>

using namespace std;

ifstream f("atlas.in");
ofstream g("atlas.out");

const int NMAX = 1e5+5;
const long long INF = (1LL<<50);
const int NMAXLIMIT = 1e5;
const long long QMAX = 10000000000LL;
const int TMAX = 3;

long long h[NMAX], n, q, t;
long long sum[NMAX], sum2[NMAX], cost[NMAX];
vector<pair<int, long long> > v;
deque<int> dq;
vector<int> lungime, poss;
int latt[NMAX];

long long cmmdc(long long x, long long y){
    if (!y){
        return x;
    }
    return cmmdc(y, x%y);
}

void reset(){
    dq.clear();
    lungime.clear();
    poss.clear();
    v.clear();
}

void baga(){
    dq.push_back(0);
    for(int i=1; i<=n+1; ++i){
        while(h[dq.back()] <= h[i]){
            v.push_back( make_pair(dq.back(), cost[dq.back()] + h[dq.back()]*(i-dq.back()) - (sum[i-1] - sum[dq.back()-1]) ));
            poss.push_back(i-1);
            lungime.push_back(i-1 - dq.back() + 1 + latt[dq.back()]-1);
            dq.pop_back();
        }
        //leftPos[i] = dq.back();
        cost[i] = cost[dq.back()] + h[i] * (i-dq.back()-1) - (sum[i-1]-sum[dq.back()]);
        v.push_back(make_pair(i, cost[i]));
        lungime.push_back(i - dq.back());
        latt[i] = i - dq.back();
        dq.push_back(i);
        poss.push_back(i);
    }
}

void solve(long long x){
    int st = -1;
    int dr = v.size();
    while(dr - st > 1){
        int mij = (st + dr) / 2;
        if (v[mij].second < x){
            st = mij;
        }else dr = mij;
    }
    long long inaltime = h[ v[st].first ];
    long long ramas = x - v[st].second;
    int pos = v[st].first;
    long long lat = 1LL*lungime[st];

    long long xx =1LL*inaltime*lat + ramas;
    long long y = lat;
    long long z = cmmdc(xx, y);
    assert(poss[st] >= 1 && poss[st] <= n);
    g << poss[st] <<" " << xx / z << "/" << y / z << "\n";
}

int main(){
    f >> t;
    assert(t >= 1 && t <= TMAX);
    for(; t; --t){
        reset();
        f >> n;

        assert(n >= 1 && n<= NMAXLIMIT);
        h[0] = INF+1;
        h[n+1] = INF;
        for(int i=1; i<=n; ++i){
            f >> h[i];
            assert(h[i] >= 0 && h[i] <= NMAXLIMIT);
            sum[i] = sum[i-1] + h[i];
        }
        sum[n+1] = h[n+1] + sum[n];

        baga();
        f >> q;
        assert(q >= 1 && q <= NMAXLIMIT);

        for(int i=1; i<=q; ++i){
            long long x; f >> x;
            assert(x >= 1 && x <= QMAX);
            solve(x);
        }
    }

    return 0;
}
