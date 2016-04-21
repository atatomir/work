// Adrian Budau - intre 40 si 56 de puncte - O(N)
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(NULL));

    freopen("movedel.in","r",stdin);
    freopen("movedel.out","w",stdout);

    int N; cin >> N;
    string A(N, 'b');
    string B(N, 'c');
    B[0] = 'a';
    A[rand() % N] = 'a';

    cout << A << "\n" << B << "\n";
}
