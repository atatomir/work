#include <iostream>

using namespace std;

long n,m,k,i,j,x,col[10005],pos=1,v[105][105];

inline void diag(long i,long j) {
    while ((i > 0)&&(j <= m)) {
        v[i][j] = col[pos++];
        i--; j++;
    }
}

int main()
{
    while(!cin.eof()) {
        cin >> n >> m >> k;

        if (cin.eof()) return 0;

        for(i=1;i<=k;i++) {
            cin >> x;
            for(;x>0;x--) col[pos++] = i;
        }

        pos = 1;
        for(i=1;i<=n;i++) diag(i,1);
        for(i=2;i<=m;i++) diag(n,i);

        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++) cout << v[i][j];
            cout << '\n';
        }
    }



    return 0;
}
