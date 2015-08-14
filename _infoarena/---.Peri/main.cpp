#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 266

int n,m,i,j;
short matrix[maxN][maxN];
short line_sum[maxN][maxN];
short column_sum[maxN][maxN];

int lineOne,lineTwo;
short Answer=-1300;
long long cntAnswer;
short bestBack;
short howBack;

int main()
{
    freopen("peri.in","r",stdin);
    freopen("peri.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            scanf("%d",&matrix[i][j]);
            if (matrix[i][j]==0) matrix[i][j]=-1;
            line_sum[i][j] = line_sum[i][j-1]+matrix[i][j];
            column_sum[i][j] = column_sum[i-1][j]+matrix[i][j];
        }
    }

    for (lineOne=1;lineOne<n;lineOne++){
        for (lineTwo=lineOne+1;lineTwo<=n;lineTwo++){
            bestBack = column_sum[lineTwo-1][1]-column_sum[lineOne][1];
            howBack = 1;

            for (i=2;i<=m;i++){
                int act = column_sum[lineTwo-1][i]-column_sum[lineOne][i] +
                          line_sum[lineOne][i]+line_sum[lineTwo][i] + bestBack;

                if (act == Answer){
                    cntAnswer+=1LL*howBack;
                } else
                if (act >  Answer){
                    cntAnswer = 1LL*howBack;
                    Answer = act;
                }

                int prob = column_sum[lineTwo-1][i]-column_sum[lineOne][i] -
                           line_sum[lineOne][i-1] - line_sum[lineTwo][i-1] ;

                if (prob > bestBack){
                    bestBack = prob;
                    howBack = 1;
                } else
                if (prob==bestBack){
                    howBack++;
                }
            }
        }
    }

    printf("%d %lld",Answer,cntAnswer);

    return 0;
}
