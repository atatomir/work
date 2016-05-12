#include <cstdlib>
#include <cmath>
#include <cassert>

#include "header.h"

using namespace std;

static const double EPS = 1e-4;

static int N;
static int queryCount = 0;

static inline bool equal(const double x, const double y) {
  if (abs(x - y) <= EPS)
    return true;
  if (abs(x) <= EPS || abs(y) <= EPS)
    return false;
  if (abs((x - y) / x) <= EPS)
    return true;
  if (abs((x - y) / y) <= EPS)
    return true;
  return false;
}

double query(int a, int b) {
  if (a < 0 || a >= N || b < 0 || b >= N || a == b)
    exit(1);
  ++queryCount;
  return 42.0;
}

void sendRecovered(double *x, double *y) {
  int score = 5;
  if (3 * N < queryCount)
    score = 3;
  if (10 * N < queryCount)
    score = 1;
  exit(0);
}

int main() {
  N = 5;
  recover(N);
  int score = 0;
  return 0;
}
