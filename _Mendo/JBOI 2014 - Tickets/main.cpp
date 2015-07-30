#include <iostream>

using namespace std;

int main()
{
    long long n,k;

    cin >> n >> k;
    long long put = 1 ;
    for (int i = 1 ; i< n;i++) put *= 2;

    for (int i = n ; i > 0 ; i--) {
        if (k > put) {
           cout << 1;
           k = k-put;
           k = put-k+1;
        } else cout << 0;
        put = put >> 1;

    }


    return 0;
}
