#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<vector>
using namespace std;
 
#define ll long long
#define pb push_back
#define NMAX 504
#define MOD 666013
 
int rucsac[NMAX][NMAX],rucsac2[NMAX][NMAX];
int total[NMAX][NMAX],d1[NMAX][NMAX],d2[NMAX][NMAX],t;
int son[NMAX],nrson,n,sol[NMAX],tata[NMAX];
int gradmax[NMAX];
char viz[NMAX];
vector<int> v[NMAX];
 
void dfs(int nod)
{
    viz[nod] = 1;
    int i,j,grad,vec,lim = v[nod].size();
    for(i = 0; i < lim; i++)
        if(!viz[vec = v[nod][i]])
        {
            tata[vec] = nod;
            dfs(vec);
            gradmax[nod] = max(gradmax[nod], gradmax[vec]);
        }
    nrson = 0;
    for(i = 0; i < lim; i++)
        if(tata[vec = v[nod][i]] == nod)
            son[++nrson] = vec;
    gradmax[nod] = max(gradmax[nod], nrson);
             
    d1[nod][0] = 1;
    total[nod][0] = 1;
    if(nrson > 0)
        d1[nod][1] = nrson;
    total[nod][1] = 1 + d1[nod][1];
    sol[1] = (sol[1] + d1[nod][1]) % MOD;
         
    for(grad = 2; grad <= gradmax[nod] + 1; grad++)
    {
//      printf("Nodul %d gradul %d\n",nod,grad);
        rucsac[0][0] = 1;
        rucsac2[0][0] = 1;
        for(i = 1; i <= nrson; i++)
        {
            rucsac[i][0] = 1;
            rucsac2[i][0] = 1;
            for(j = 1; j <= min(grad,i); j++)
            {
                rucsac[i][j] = (rucsac[i - 1][j] + (ll)rucsac[i - 1][j - 1] * (d2[son[i]][grad] + total[son[i]][grad - 1])) % MOD;
                rucsac2[i][j] = (rucsac2[i - 1][j] + (ll)rucsac2[i - 1][j - 1] * (d2[son[i]][grad - 1] + total[son[i]][grad - 2])) % MOD;
            //  printf("Rucsacul din primele %d sa selectez %d zice ca %d si %d\n",i,j,rucsac[i][j],rucsac2[i][j]);
            }
        }
        if(grad > nrson)
            d1[nod][grad] = 0;
        else
            d1[nod][grad] = rucsac[nrson][grad];
        for(i = 0; i <= min(grad - 1, nrson); i++)
        {
            d2[nod][grad] += rucsac[nrson][i] - rucsac2[nrson][i];
            if(d2[nod][grad] >= MOD)
                d2[nod][grad] %= MOD;
            if(d2[nod][grad] < 0)
                d2[nod][grad] += MOD;
        }
        total[nod][grad] = (total[nod][grad - 1] + d1[nod][grad] + d2[nod][grad]) % MOD;
        sol[grad] = (sol[grad] + d1[nod][grad] + d2[nod][grad]) % MOD;
    }
    for(grad = gradmax[nod] + 2; grad < n; grad++)
    		total[nod][grad] = total[nod][grad - 1];
    	
//  for(i = 0; i < n; i++)
//      printf("Nodul %d gradul %d avem d1 = %d d2 = %d total = %d\n",nod,i,d1[nod][i],d2[nod][i],total[nod][i]);
}
 
int main ()
{
    int i,a,b;
     
    freopen("grarbore.in","r",stdin);
    freopen("grarbore.out","w",stdout);
     
    scanf("%d", &t);
    for(; t; t--)
    {
        scanf("%d",&n);
        for(i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            v[a + 1].pb(b + 1);
            v[b + 1].pb(a + 1);
        }
     
        dfs(1);
     
        for(i = 1; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
         
        memset(viz,0,sizeof(viz));
        memset(d1,0,sizeof(d1));
        memset(d2,0,sizeof(d2));       
        memset(total,0,sizeof(total));
        memset(sol,0,sizeof(sol));
        memset(tata,0,sizeof(tata));
        for(i = 1; i <= n; i++)
            v[i].clear();
    }
     
    return 0;
}


