#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 55
#define maxM 22
#define maxX 66

int n,m,i,j,l,r,k,X,cost,how;

int so,de;
int matrix[maxN][maxM];
int dp[2][maxM][maxM][maxX];
int aux[2][maxM][maxX];
int ans;

int main()
{
    freopen("zidar.in","r",stdin);
    freopen("zidar.out","w",stdout);

    scanf("%d%d%d%d",&n,&m,&X,&cost);
    for (i = 1; i <= n; i++){
        for (j = 1; j <= m; j++){
            scanf("%d",&matrix[i][j]);
            matrix[i][j] += matrix[i][j-1];
        }
    }

    for (l = 1; l <= m; l++)
        for (r = l+1; r <= m; r++)
            for (how = 1; how <= X; how++)
                dp[so][l][r][how] = cost+1;
    for (int pos = 1; pos <= m; pos++)
        for (how = 1; how <= X; how++)
            aux[so][pos][how] = cost+1;

    so = 0; de = 1;
    for (int step = 1; step <= n; step++) {

        for (int pos = 1; pos <= m; pos++)
            for (how = 0; how <= X; how++)
                aux[de][pos][how] = cost+1;

        for (l = 1; l <= m; l++) { //! left
            for (r = l; r <= m; r++) { //! right
                int dim = r - l + 1;
                int sum = matrix[step][r] - matrix[step][l-1];

                for (how = dim; how <= X; how++) { //! how many bricks
                    dp[de][l][r][how] = cost + 1;

                    for (k = l; k <= r; k++) //! get result
                        dp[de][l][r][how] = min(dp[de][l][r][how], aux[so][k][ how - dim ] + sum);

                    dp[de][l][r][how] = min(dp[de][l][r][how], cost+1);

                    for (k = l; k <= r; k++) //! set aux
                        aux[de][k][how] = min(aux[de][k][how], dp[de][l][r][how]);

                    if (how > ans && dp[de][l][r][how] <= cost) ans = how;
                }
            }
        }

        swap(so,de);
    }

    printf("%d",ans);


    return 0;
}
