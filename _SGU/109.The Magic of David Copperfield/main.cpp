#include <iostream>

using namespace std;

long n,i,j,k,nn,a[105][105];
long l,bonus=0;

int main()
{
    cin >> n; nn = n;
    k = n; if(k % 2 == 0) k++;
    k = k-2;

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            a[i][j] = (i-1)*n+j;
        }
    }

    if (n % 2 == 0) {
        k = k+2;
        cout << k << ' ';
        for(i=2;i<n;i=i+2) {
            cout << a[i][n] << " " << a[n][i] << " ";
        }
        cout << a[n][n] << '\n';

        k = k+2;
        cout << k << ' ';
        for(i=1;i<n;i=i+2) {
            cout << a[i][n] << " " << a[n][i] << " ";
        }
        cout << '\n';

        n--;
    }

    for(l=n;l>1;l=l-2) {
        k = k+2;
        cout << k << ' ';
        for(i=1;i<l;i=i+2) {
            cout << bonus+a[1][i] << " " << bonus+a[l][l-i+1] << " " << bonus+a[i][l] << " " << bonus+a[l-i+1][1] << " ";
        }
        cout << '\n';

        k = k+2;
        cout << k << ' ';
        for(i=2;i<=l;i=i+2) {
            cout << bonus+a[1][i] << " " << bonus+a[l][l-i+1] << " " << bonus+a[i][l] << " " << bonus+a[l-i+1][1] << " " ;
        }
        cout << '\n';

        bonus += nn+1;
    }

    return 0;
}
