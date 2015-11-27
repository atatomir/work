#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111
#define inf 1000000000

int _n, _i;
int _v[maxN];
int _id[maxN];
int _counter;


bool cmp(int a, int b) {
    return _v[a] < _v[b];
}

int init() {
    freopen("meandian.in", "r", stdin);

    scanf("%d", &_n);
    for (_i = 1; _i <= _n; _i++)
        scanf("%d", &_v[_i]);
    _counter = 0;

    return _n;
}

int Meandian(int A, int B, int C, int D) {
    _counter++;

    vector<int> aux = {_v[A], _v[B], _v[C], _v[D]};
    sort(aux.begin(), aux.end());
    return (aux[1] + aux[2]) / 2;
}

void Solution(const int *from) {
    freopen("meandian.out", "w", stdout);

    if (_counter > 1000) {
        printf("0\nCounter too big %d", _counter);
        return;
    }

    for (_i = 1; _i <= _n; _i++)
        _id[_i] = _i;
    sort(_id + 1, _id + _n + 1, cmp);
    _v[ _id[1] ] = _v[ _id[2] ] = _v[ _id[_n - 1] ] = _v[ _id[_n] ] = -1;

    //for (_i = 1; _i <= _n; _i++) cerr << from[_i] << ' ';

    for (_i = 1; _i <= _n; _i++) {
        if (from[_i] != _v[_i]) {
            printf("0\nYou are not magic..");
            return;
        }
    }

    printf("1\nAll right!");
}
