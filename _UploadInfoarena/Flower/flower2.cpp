#include<stdio.h>
#include<algorithm>
using namespace std;

#define ll long long
#define modul(val) ((val) < 0 ? -(val) : (val))
#define INF (1LL<<60)
#define NMAX 300005

int smecheru[4 * NMAX],n,m,nr,ok;
ll aint[4 * NMAX],miros[NMAX];
int cusca[NMAX],p[NMAX];

/*inline int modul(int val)
{
	if(val < 0)
		return -val;
	return val;
}*/

ll get_cost(int pozitie, int indice)
{
	return miros[indice] - (ll)p[indice] * modul(cusca[indice] - pozitie);
}

void update(int n, int st, int dr, int a, int b, int indice)
{
	if(a <= st && dr <= b)
	{
		smecheru[n] = indice;
		aint[n] = min(get_cost(st, indice), get_cost(dr, indice));
		return ;		
	}
	int mij = (st + dr) / 2;
	if(smecheru[n])
	{
		smecheru[2 * n] = smecheru[n];
		smecheru[2 * n + 1] = smecheru[n];
		
		aint[2 * n] = min(get_cost(st, smecheru[n]), get_cost(mij, smecheru[n]));
		aint[2 * n + 1] = min(get_cost(mij + 1, smecheru[n]), get_cost(dr, smecheru[n]));
		smecheru[n] = 0;
	}
	if(a <= mij)
		update(2 * n, st, mij, a, b, indice);
	if(b > mij)
		update(2 * n + 1, mij + 1, dr, a, b, indice);
	aint[n] = min(aint[2 * n], aint[2 * n + 1]);
}

int FindBoss(int n, int st, int dr, int pozitie)
{
	if(smecheru[n])
		return smecheru[n];
	int mij = (st + dr) / 2;
	if(pozitie <= mij)
		return FindBoss(2 * n, st, mij, pozitie);
	return FindBoss(2 * n + 1, mij + 1, dr, pozitie);
}

ll query(int n, int st, int dr, int a, int b)
{
	if(a <= st && dr <= b)
		return aint[n];
	int mij = (st + dr) / 2;
	ll v1 = INF, v2 = INF;
	
	if(smecheru[n])
	{
		smecheru[2 * n] = smecheru[n];
		smecheru[2 * n + 1] = smecheru[n];
		
		aint[2 * n] = min(get_cost(st, smecheru[n]), get_cost(mij, smecheru[n]));
		aint[2 * n + 1] = min(get_cost(mij + 1, smecheru[n]), get_cost(dr, smecheru[n]));
		smecheru[n] = 0;
	}
	
	if(a <= mij)
		v1 = query(2 * n, st, mij, a, b);
	if(b > mij)
		v2 = query(2 * n + 1, mij + 1, dr, a, b);
	return min(v1,v2);
}

int LeftBinarySearch(int indice)
{
	int st,dr,mij,candidat,sol = indice;
	
	st = 1; dr = cusca[indice];
	while(st <= dr)
	{
		mij = (st + dr) / 2;
		candidat = FindBoss(1,1,n,mij);
		if(get_cost(mij, candidat) <= get_cost(mij, indice))
		{
			sol = mij;
			dr = mij - 1;
		}
		else
			st = mij + 1;
	}
	return sol;
}

int RightBinarySearch(int indice)
{
	int st,dr,mij,candidat,sol = indice;
	
//	printf("Verific in dreapta la %d\n", indice);
	st = cusca[indice]; dr = n;
	while(st <= dr)
	{
		mij = (st + dr) / 2;
		candidat = FindBoss(1,1,n,mij);
//		printf("%d %lld %d %d %d\n",cusca[indice],miros[indice],p[indice],indice,mij);
//		printf("La %d candidatul este %d si costurile or sa vina %lld %lld\n",mij,candidat,get_cost(mij, candidat), get_cost(mij, indice));
		if(get_cost(mij, candidat) <= get_cost(mij, indice))
		{
			sol = mij;
			st = mij + 1;
		}
		else
			dr = mij - 1;
	}
	return sol;
}

void Adauga(int indice)
{
	if(!ok)
	{
		update(1,1,n,1,n,indice);
		ok = 1;
		return ;
	}
	
	ll mirosmaxim = query(1,1,n,cusca[indice],cusca[indice]);
	if(mirosmaxim >= miros[indice])
		return ;
		
	int poz;
	poz = LeftBinarySearch(indice);
//	printf("Intervalul lui %d vine de la %d la ",indice,poz);
	update(1, 1, n, poz, cusca[indice], indice);
	
	poz = RightBinarySearch(indice);
	//printf("%d\n",poz);
	update(1, 1, n, cusca[indice], poz, indice);
}

int main ()
{
	int i,a,b,tip;
	ll ans;
	
	freopen("flower.in","r",stdin);
	freopen("flower.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(i = 1; i <= m; i++)
	{
		scanf("%d",&tip);
		if(tip == 1)
		{
			++nr;
			scanf("%d%lld%d",&cusca[nr],&miros[nr],&p[nr]);
			Adauga(nr);
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

