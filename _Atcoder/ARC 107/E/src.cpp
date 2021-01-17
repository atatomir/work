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
#define data blabla123

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
  cerr << "[";
  for (auto e : aux) cerr << e << ' ';
  cerr << "]";
  return cerr;
}

const int maxN = 500011;

int n;
vector<int> data[maxN];
vector<int> def[3];
ll cnt[3];

int mex(int x, int y) {
  return def[x][y];
}

void extra(int x, int y, int v) {
  int dx = n - x;
  int dy = n - y;

  cnt[v] += 1LL * min(dx, dy);
}

int main()
{
  //freopen("test.in", "r", stdin);

  def[0] = {1, 2, 1};
  def[1] = {2, 0, 0};
  def[2] = {1, 0, 0};

  cin >> n;
  for (int i = 1; i <= 4; i++)
    data[i].resize(n + 1);

  for (int i = 5; i <= n; i++)
    data[i].resize(5);

  for (int i = 1; i <= n; i++) {
    cin >> data[1][i];
    cnt[data[1][i]]++;
  }

  for (int i = 2; i <= n; i++) {
    cin >> data[i][1];
    cnt[data[i][1]]++;
  }

  for (int i = 2; i <= min(n, 4); i++) {
    for (int j = 2; j <= n; j++) {
      data[i][j] = mex(data[i - 1][j], data[i][j - 1]);
      cnt[data[i][j]]++;

      if (i == 4 && j >= 4) extra(i, j, data[i][j]);
    }
  }

  for (int i = 5; i <= n; i++) {
    for (int j = 2; j <= 4; j++) {
      data[i][j] = mex(data[i - 1][j], data[i][j - 1]);
      cnt[data[i][j]]++;

      if (j == 4 && i > 4) extra(i, j, data[i][j]);
    }
  }

  cout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << '\n';



  return 0;
}
