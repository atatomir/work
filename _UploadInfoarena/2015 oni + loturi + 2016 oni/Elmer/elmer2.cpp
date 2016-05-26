// Budau Adrian - O((N*M)*log(N*M)) - 100p
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

static const int64_t kInfinite = numeric_limits<int64_t>::max() - 5;

int64_t intersect(pair<int, int> duck, pair<int, int> wall, bool right = false) {
    if (wall.first == duck.first)
        return wall.first + 1;
    int64_t prod = 1LL * (wall.first - duck.first) * duck.second;
    int64_t when = prod / (duck.second - wall.second);
    if (prod % (duck.second - wall.second)) {
        if (right && prod > 0)
            ++when;
        else if (!right && prod < 0)
            --when;
    }

    return when + duck.first;
}

int main() {
    ifstream cin("elmer.in");
    ofstream cout("elmer.out");

    int N; cin >> N;

    assert(1 <= N && N <= 1000);

    vector< pair<int, int> > duck(N);
    for (int i = 0; i < N; ++i)
        cin >> duck[i].first >> duck[i].second;

    int M; cin >> M;
    vector< pair<int, int> > wall(M);
    for (int j = 0; j < M; ++j)
        cin >> wall[j].first >> wall[j].second;

    sort(wall.begin(), wall.end());

    vector< pair<int64_t, int> > moments;
    moments.reserve(N * M);
    for (int i = 0; i < N; ++i) {
        int left = lower_bound(wall.begin(), wall.end(), duck[i], [&](pair<int, int> wall, pair<int, int> duck) {
            return wall.first < duck.first;
        }) - wall.begin();
        int right = left;

        int64_t to = kInfinite;
        if (left < M)
            to = wall[left].first - 1;

        while (left > 0) {
            if (to > wall[left - 1].first) {
                moments.emplace_back(wall[left - 1].first + 1, 1);
                moments.emplace_back(to + 1, -1);
            }
            if (duck[i].second <= wall[left - 1].second)
                break;
            to = min(to, intersect(duck[i], wall[left - 1]));
            --left;
        }

        if (left == 0 && to > 0) {
            moments.emplace_back(1, 1);
            moments.emplace_back(to + 1, - 1);
        }

        if (right == M || duck[i].second <= wall[right].second)
            continue;
        int64_t from = intersect(duck[i], wall[right], true);
        ++right;
        while (right < M) {
            if (from < wall[right].first) {
                moments.emplace_back(from, 1);
                moments.emplace_back(wall[right].first, -1);
            }
            if (duck[i].second <= wall[right].second)
                break;
            from = max(from, intersect(duck[i], wall[right], true));
            ++right;
        }
        if (right == M)
            moments.emplace_back(from, 1);
    }

    int answer = 0;
    sort(moments.begin(), moments.end());
    int aux = 0;
    for (int i = 0, j; i < int(moments.size()); i = j) {
        for (j = i; j < int(moments.size()) && moments[j].first == moments[i].first; ++j)
            aux += moments[j].second;
        answer = max(answer, aux);
    }

    cout << answer << "\n";
}
