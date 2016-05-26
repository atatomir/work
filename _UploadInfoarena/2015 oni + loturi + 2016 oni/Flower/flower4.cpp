#include<stdio.h>
#include<algorithm>
using namespace std;

#define INF (1LL<<60)
#define NMAX 300005
#define ll long long

ll aint[4 * NMAX];
ll miroscurent[NMAX];
int n,m;

void update(int n, int st, int dr, int poz, ll val)
{
	if(st == dr)
	{
		aint[n] = val;
		return ;
	}
	int mij = (st + dr) / 2;
	if(poz <= mij)
		update(2 * n, st, mij, poz, val);
	else
		update(2 * n + 1, mij + 1, dr, poz, val);
	aint[n] = min(aint[2 * n], aint[2 * n + 1]);
}

ll query(int n, int st, int dr, int a, int b)
{
	if(a <= st && dr <= b)
		return aint[n];
	int mij = (st + dr) / 2;
	ll v1 = INF, v2 = INF;
	if(a <= mij)
		v1 = query(2 * n, st, mij, a, b);
	if(b > mij)
		v2 = query(2 * n + 1, mij + 1, dr, a, b);
	return min(v1,v2);
}

int main ()
{
	int i,j,tip,a,b,cusca,miros,p;
	ll ans;

	freopen("flower.in","r",stdin);
	freopen("flower.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	
	for(i = 1; i <= n; i++)
		miroscurent[i] = -INF;
	
	for(i = 1; i <= m; i++)
	{
		scanf("%d",&tip);
		if(tip == 1)
		{
			scanf("%d%d%d",&cusca,&miros,&p);
			for(j = cusca; j <= n; j++)
				if(miros - (ll)p * (j - cusca) >= miroscurent[j])
				{
					miroscurent[j] = miros - (ll)p * (j - cusca);
					update(1,1,n,j, miroscurent[j]);
				}
				else
					break;
			for(j = cusca - 1; j >= 1; j--)
				if(miros - (ll)p * (cusca - j) >= miroscurent[j])
				{
					miroscurent[j] = miros - (ll)p * (cusca - j);		
					update(1,1,n,j, miroscurent[j]);
				}
				else
					break;
		}
		else
		{
			scanf("%d%d",&a,&b);
			ans = query(1,1,n,a,b);
			printf("%lld\n",ans);
		}
	}
	
	return 0;
}

