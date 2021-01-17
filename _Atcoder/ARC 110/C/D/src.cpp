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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
  cerr << "[";
  for (auto e : aux) cerr << e << ' ';
  cerr << "]";
  return cerr;
}

const int maxN = 200011;

int n, p[maxN];
bool used[maxN];
vector<int> order;

bool exec(int i) {
  if (p[i] > p[i + 1])  {
    if (used[i]) {
      cout << -1;
      exit(0);
    }

    used[i] = true;
    order.pb(i);
    swap(p[i], p[i + 1]);
    return true;
  }

  return false;
}

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> p[i];

  bool any = true;
  while (any && order.size() <= n - 1) {
    any = false;

    for (int i = 1; i + 1 <= n; i++) 
      any |= exec(i);

    for (int i = n - 1; i >= 1; i--)
      any |= exec(i);
  }


  if (order.size() != n - 1) {
    cout << -1;
    return 0;
  }

  for (auto e : order)
    cout << e << '\n';


  return 0;
}
