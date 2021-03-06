/**
 * Solutie de complexitate O(N * M * log(N))
 *
 * @author Adrian Budau
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ifstream cin("tort3.in");
    ofstream cout("tort3.out");

    int N, M; assert(cin >> N >> M);
    assert(1 <= N && N <= 1500);
    vector<string> S(N);
    for (int i = 0; i < N; ++i) {
        assert(cin >> S[i]);
        assert(int(S[i].size()) == M);
        for (auto &c : S[i])
            assert(c >= '0' && c <= '9');
    }

    vector< vector<int> > dp(N, vector<int>(M, 1));
    for (int i = N - 2; i >= 0; --i)
        for (int j = M - 2; j >= 0; --j)
            if (S[i][j] == S[i + 1][j] && S[i][j] == S[i][j + 1] && S[i][j] == S[i + 1][j + 1])
                dp[i][j] = min(dp[i + 1][j], min(dp[i][j + 1], dp[i + 1][j + 1])) + 1;


    vector< vector< pair<int, int> > > has(min(N, M) + 1);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            has[dp[i][j]].emplace_back(i, j);

    for (int L = min(N, M); L > 0; --L) {
        sort(has[L].begin(), has[L].end());
        for (auto &p : has[L]) {
            int i = p.first;
            int j = p.second;

            if (S[i][j] == '-')
                continue;

            if (dp[i][j] == L && S[i + L - 1][j] != '-' && S[i][j + L - 1] != '-' && S[i + L - 1][j + L - 1] != '-') {
                cout << L << " " << i + L << " " << j + L << "\n";
                for (int k = 0; k < L; ++k)
                    for (int p = 0; p < L; ++p)
                        S[i + k][j + p] = '-';
            } else {
                int step;
                for (step = 1; step <= L; step <<= 1);
                int newL;
                for (newL = 0; step; step >>= 1)
                    if (newL + step <= L && i + newL + step <= N && j + newL + step <= M)
                        if (S[i + newL + step - 1][j] != '-' && S[i][j + newL + step - 1] != '-' && S[i + newL + step - 1][j + newL + step - 1] != '-')
                            newL += step;
                dp[i][j] = newL;
                has[newL].emplace_back(i, j);
            }
        }
    }
}
