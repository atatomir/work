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

const int maxN = 1 << 18;
const int mod = 200003;
const ll g = 2;
const double PI = acos(-1);

struct comp {
  double a, b;

  comp() {
    a = b = 0;
  }

  comp(double x) {
    a = x;
    b = 0;
  }

  comp(double x, double y) {
    a = x;
    b = y;
  }

  comp operator+(comp other) {
    return comp(a + other.a, b + other.b);
  }

  comp operator-(comp other) {
    return comp(a - other.a, b - other.b);
  }

  comp operator*(comp other) {
    return comp(a * other.a - b * other.b,
                a * other.b + b * other.a);
  }

  comp ref() {
    return comp(a, -b);
  }
};

int n;
ll to[maxN], from[maxN], x;
comp cnt[2 * maxN + 2]; 

void pre() {
  ll aux = 1;
  for (int i = 0; i < mod - 1; i++) {
    if (aux == 1 && i != 0) 
      cerr << i << ' ' << aux << '\n';

    to[i] = aux;
    from[aux] = i;
    aux = (aux * g) % mod;
  }
}

void shuf(comp* coef, int len) {
  vector<comp> aux = vector<comp>(len, comp());

  for (int batch = len / 2; batch > 0; batch >>= 1) {
    memcpy(&aux[0], coef, sizeof(comp) * len);

    for (int i = 0; i < len; i += 2 * batch) {
      for (int j = 0; j < batch; j++)
        coef[i + j] = aux[i + 2 * j];
      for (int j = 0; j < batch; j++)
        coef[i + batch + j] = aux[i + 2 * j + 1];
    }
  }
}

void fft(comp* coef, int len, bool rev) {
  shuf(coef, len);

  for (int batch = 1; 2 * batch <= len; batch <<= 1) {
    comp w = comp(cos(PI / batch), sin(PI / batch)); 
    if (rev) w = w.ref();

    for (int i = 0; i < len; i += 2 * batch) {
      comp act = comp(1.0);

      for (int j = 0; j < batch; j++) {
        comp a = coef[i + j];
        comp b = coef[i + batch + j];

        coef[i + j] = a + act * b;
        coef[i + batch + j] = a - act * b;

        act = act * w;
      }
    }
  }

  if (rev) {
    for (int i = 0; i < len; i++) 
      coef[i] = coef[i] * comp(1.0 / len);
  }
} 

int main()
{
  //freopen("test.in", "r", stdin);
  ll ans = 0;

  pre();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &x); 
    if (x == 0) continue;
    ans -= (x * x) % mod;

    x = from[x];
    cnt[x] = cnt[x] + comp(1);
  }

  fft(cnt, maxN << 1, false); 
  for (int i = 0; i < (maxN << 1); i++) 
    cnt[i] = cnt[i] * cnt[i];
  fft(cnt, maxN << 1, true);
  

  for (int i = 0; i < (maxN << 1); i++) {
    ll many = round(cnt[i].a);
    if (many == 0) continue;

    //cerr << i << ' ' << many << '\n';
    
    ans += many * to[i % (mod - 1)];
  }

  cout << ans / 2;


  return 0;
}
