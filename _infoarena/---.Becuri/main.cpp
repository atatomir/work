#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 511

int n,m,i,j,x,prov;
bool matrix[maxN][maxN];
bool aux[maxN][maxN];
bool xor_ind;

vector<int> lines[2];
vector<int> columns[2];
bool work[2];
int ans[2];

bool Try(int id) {
    int i,j;

    for (j = 1; j <= m; j++) {
        xor_ind = 0;
        if (aux[1][j] == 1) {
            xor_ind = 1;
            columns[id].pb(j);
        }

        for (i = 1; i <= n; i++) aux[i][j] ^= xor_ind;
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (aux[i][j]) return false;

    return true;
}

int main()
{
    freopen("becuri.in","r",stdin);
    freopen("becuri.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i = 1; i <= n; i++){
        for (j = 1; j <= m; j++) {
            scanf("%d",&x);
            if (x) matrix[i][j] = true;
        }
    }

    //! first column 0
    lines[0].clear();
    columns[0].clear();

    for (i = 1; i <= n; i++){
        xor_ind = 0;
        if (matrix[i][1] == 1) {
            xor_ind = 1;
            lines[0].pb(i);
        }

        for (j = 1; j <= m; j++) aux[i][j] = matrix[i][j] ^ xor_ind;
    }
    work[0] = Try(0);

    //! first column 1
    lines[1].clear();
    columns[1].clear();

    for (i = 1; i <= n; i++){
        xor_ind = 0;
        if (matrix[i][1] == 0) {
            xor_ind = 1;
            lines[1].pb(i);
        }

        for (j = 1; j <= m; j++) aux[i][j] = matrix[i][j] ^ xor_ind;
    }
    work[1] = Try(1);

    if (work[0]) {
        int a = lines[0].size();
        int b = columns[0].size();
        if (a < b) swap(a,b);

        if ( (a-b)%2 != 0 ) work[0] = false;
        ans[0] = max(a,b);
    }
    if (work[1]) {
        int a = lines[1].size();
        int b = columns[1].size();
        if (a < b) swap(a,b);

        if ( (a-b)%2 != 0 ) work[1] = false;
        ans[1] = max(a,b);
    }

    if (work[0] == false && work[1] == false) {
        printf("-1");
        return 0;
    }

    if (work[0] == false)
        prov = 1;
    else
    if (work[1] == false)
        prov = 0;
    else
        prov = ( ans[0] < ans[1] ? 0:1 );

    while(lines[prov].size() < columns[prov].size()) lines[prov].pb(1);
    while(lines[prov].size() > columns[prov].size()) columns[prov].pb(1);

    printf("%d\n",ans[prov]);
    for (i = 0; i < lines[prov].size(); i++)
        printf("%d %d\n",lines[prov][i],columns[prov][i]);

    return 0;
}
