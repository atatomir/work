// Adrian Budau - intre 18 si 26 de puncte - O(N)
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL));

    freopen("movedel.in","r",stdin);
    freopen("movedel.out","w",stdout);
    int N; cin >> N;

    for (int i = 0; i < N; ++i)
        cout << char(rand() % 26 + 'a');
    cout << "\n";
    for (int i = 0; i < N; ++i)
        cout << char(rand() % 26 + 'a');
    cout << "\n";
}
