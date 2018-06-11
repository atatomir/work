#include<bits/stdc++.h>

using namespace std;

int N, M, K, mod, cost1[20][1 << 20], cost2[20][1 << 20], dp[1 << 20][120], old[1 << 20][120];
bool isOk[1 << 20];
char sir[29][29];
//vector < int > v[1 << 20];

void adto (int &x, int y) {x += y; if (x >= mod) x -= mod;}

int main ()
{
freopen ("input", "r", stdin);
freopen ("output", "w", stdout);

int Tests;
scanf ("%d", &Tests);
while (Tests --)
{
    scanf ("%d %d", &M, &N);
    scanf ("%d", &K);
    scanf ("%d\n", &mod);
    for (int i=0; i<N; i++)
        scanf ("%s", sir[i]);
/*    for (int i=0; i<N; i++, printf ("\n"))
        for (int j=0; j<M; j++)
            printf ("%c", sir[i][j]);*/

    for (int msk = 0; msk < (1 << M); msk ++)
    {
        isOk[msk] = 1;
        for (int i=0; i<M; i++)
        if ((msk & (1 << i)) == 0)
        {
            int j;
            for (j=i; j<M; j++)
                if ((msk >> j) & 1)
                    break;
            j --;
            if ((j - i + 1) & 1)
            {
                isOk[msk] = 0;
                break;
            }
            i = j;
        }
    }

/*    for (int msk = 0; msk < (1 << M); msk ++)
    {
        v[msk].clear ();
        int mare = msk ^ ((1 << M) - 1);
        for (int sub = mare;; sub = (sub - 1) & mare)
        {
            if (isOk[sub | msk])
                v[msk].push_back (sub);
            if (sub == 0) break;
        }
    }*/

    for (int lin=0; lin<N; lin++)
    {
        for (int msk = 0; msk < (1 << M); msk ++)
            if (isOk[msk])
            {
                cost1[lin][msk] = 0;
                for (int i=0; i<M; i++)
                    if ((msk & (1 << i)) == 0)
                    {
                        int j;
                        for (j=i; j<M; j++)
                            if ((msk >> j) & 1)
                                break;
                        j --;
                        assert ((j - i + 1) % 2 == 0);
                        for (int k=i; k<j; k+=2)
                            cost1[lin][msk] += (sir[lin][k] == 'A' && sir[lin][k + 1] == 'A');
                        i = j;
                    }
            }
        if (lin + 1 < N)
        {
            for (int msk = 0; msk < (1 << M); msk ++)
            {
                cost2[lin][msk] = 0;
                for (int i=0; i<M; i++)
                    if (msk & (1 << i))
                        cost2[lin][msk] += (sir[lin][i] == 'A' && sir[lin + 1][i] == 'A');
            }
        }
    }

    memset (dp, 0, sizeof (dp));
    for (int msk = 0; msk < (1 << M); msk ++)
        if (isOk[msk])
            dp[msk][cost1[0][msk]] = 1;
    for (int lin=0; lin + 1 < N; lin++)
    {
        memcpy (old, dp, sizeof (old));
        memset (dp, 0, sizeof (dp));
        for (int msk = 0; msk < (1 << M); msk ++)
        {
            vector < int > v;
            int mare = ((1 << M) - 1) ^ msk;
            for (int sub = mare;; sub = (sub - 1) & mare)
            {
                if (isOk[sub | msk])
                    v.push_back (sub);
                if (sub == 0) break;
            }
            for (int j=0; j<=K && j<=((lin + 1) * M) / 2; j++)
                if (old[msk][j] > 0)
                {
                    for (auto sub : v)
                        if (j + cost2[lin][msk] + cost1[lin + 1][msk | sub] <= K && isOk[msk | sub] == 1)
                        {
                            if (sub == 1)
                                sub = 1;
                            adto (dp[sub][j + cost2[lin][msk] + cost1[lin + 1][msk | sub]], old[msk][j]);
                        }
                }
        }
/*        printf ("%d: \n", lin + 2);
        for (int msk = 0; msk < (1 << M); msk ++)
            for (int j=0; j<=K; j++)
                if (dp[msk][j] > 0)
                    printf ("(%d, %d) -> %d\n", msk, j, dp[msk][j]);*/
    }
    printf ("%d\n", dp[0][K]);
}

return 0;
}
