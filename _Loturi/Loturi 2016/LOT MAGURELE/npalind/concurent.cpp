#include "header.h"
#include <vector>
#include <algorithm>

using namespace std;

void solve(int n, long long k) {
  int st = 0, dr = getMaxPalLength(0, n - 1);
  vector<int> ans;

  ans.clear();
  for (int i = 0; i < dr ; i++) ans.push_back(n - i);

    sort(ans.begin(), ans.end());
  solution(ans.size(), ans.data());
}
