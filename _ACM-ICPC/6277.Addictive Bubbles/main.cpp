#include <iostream>
#include <fstream>

using namespace std;

long n,m,i,j,k,pos,a[10],v[105][105];
char c;

int main()
{
    //ifstream f("test.in");

    while (!cin.eof()) {

        cin >> n >> m >> k ;

        if (cin.eof()) return 0;

        for(i=1;i<=k;i++) cin >> a[i];

        pos = 1; i = n; j = 1;

        while (pos <= k) {
            v[i][j] = pos; a[pos]--;
            if (a[pos] == 0) {
                pos++;
            }
            i--;
            if(i==0) {
                i=n; j++;
            }
        }

        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++) cout << v[i][j];
            cout << "\n";
        }

    }

    return 0;
}
