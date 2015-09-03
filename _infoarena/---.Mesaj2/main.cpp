#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxL 1024

int n,i,j;
int bigDim;
char bigString[maxL];
int smallDim;
char smallString[maxL];

int left_limit[maxL];
int dp[2][maxL]; //! dp[ posBig ][ posSmall ]
int dp_s,dp_d;

/*
 * Daca inversem matricea dinamica obtine un timp mai mic pt smallDim mai mare
 * De asemenea, dupa inversare , creste timpul pt smallDim mai mic
 * Voi varia cele doua matode in functie de cuvantul adaugat
 */

void add_to_dictionary() {
    dp_s = 0; dp_d = 1;

    for (int i = 1; i <= bigDim; i++)
        dp[dp_s][i] = (bigString[i] == smallString[1] ? i : dp[dp_s][i-1]) ;

    for (int posSmall = 2; posSmall <= smallDim; posSmall++) {
        for (int i = 1; i <= bigDim; i++)
            dp[dp_d][i] = (bigString[i] == smallString[posSmall] ? dp[dp_s][i-1] : dp[dp_d][i-1] );

        if (dp[dp_d][bigDim] == 0) return;
        swap(dp_d,dp_s);
    }

    for (int i = 1; i <= bigDim; i++) left_limit[i] = max(left_limit[i], dp[dp_s][i]);
}

void add_to_dictionary_reverse() {
    dp_s = 0; dp_d = 1;

    for (int posSmall = 1; posSmall <= smallDim; posSmall++) dp[dp_s][posSmall] = 0;
    for (int posBig = 1; posBig <= bigDim; posBig++) {
        if (bigString[posBig] == smallString[1])
            dp[dp_d][1] = posBig;
        else
            dp[dp_d][1] = dp[dp_s][1];

        for (int posSmall = 2; posSmall <= smallDim; posSmall++)
            dp[dp_d][posSmall] = (bigString[posBig] == smallString[posSmall] ? dp[dp_s][posSmall-1] : dp[dp_s][posSmall] );

        left_limit[posBig] = max(left_limit[posBig], dp[dp_d][smallDim]);
        swap(dp_d,dp_s);
    }
}

int getBest() {
    int ans = 0;
    int limit = 0;

    for (int i = 1; i <= bigDim; i++) {
        if (limit >= left_limit[i]) continue;

        ans ++;
        limit = i;
    }

    return ans;
}

int main()
{
    freopen("mesaj2.in","r",stdin);
    freopen("mesaj2.out","w",stdout);

    scanf("%s\n%d\n",bigString+1,&n);
    bigDim = strlen(bigString+1);

    for (; n; n--) {
        memset(smallString,0, smallDim + 10 );
        gets(smallString+1);
        smallDim = strlen(smallString+1);

        if (smallDim < bigDim/50)
            add_to_dictionary();
        else
            add_to_dictionary_reverse();

        printf("%d\n", getBest() );
    }


    return 0;
}
