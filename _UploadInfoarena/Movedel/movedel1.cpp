// Adrian Budau - 100 de puncte - O(M)
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

static const int kMaxV = 1000 * 1000 + 7;

int main() {
    freopen("movedel.in","r",stdin);
    freopen("movedel.out","w",stdout);

    vector<bool> sieve(kMaxV, false);
    vector<int> primes;
    for (int i = 2; i < kMaxV; ++i)
        if (!sieve[i]) {
            primes.push_back(i);
            for (int j = i + i; j < kMaxV; j += i)
                sieve[j] = true;
        }
    reverse(primes.begin(), primes.end());

    int N; cin >> N;

    int covered = 0;
    vector<bool> cover(N, 0);
    int last = -1;
    int lastlast = 0;
    int now = 0;
    int iterations = 0;
    while (covered < N) {
        now = now + primes.back();
        primes.pop_back();
        now %= N;
        if (!cover[now]) {
            cover[now] = true;
            ++covered;
            lastlast = last;
            last = now;
        }
        ++iterations;
    }
    string A(N, 'b'), B(N, 'c');
    B[0] = 'a';
    A[last] = 'a';

    cerr << "I think i did " << iterations << " iterations\n";
    cerr << "With last " << last << " and last last " << lastlast << "\n";
    cout << A << "\n" << B << "\n";
}
