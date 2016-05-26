#include<stdio.h>
#include<cassert>
#include<vector>
using namespace std;

#define pb push_back
#define pii pair< pair<int, int>, int>
#define x first.first
#define y first.second
#define z second
#define mp make_pair
#define NMAX 523
#define MMAX 500006

int AIB[NMAX][NMAX],n,m;
int nrquery,nrupdate,nonquery;
vector<int> sol;
vector<int> stiva;
vector<int> v[MMAX],querylist[MMAX];
vector< pii > myupdate, myquery;

void update(int px, int py, int val)
{
    int sy = py;
   for( ; px <= n; px += px ^ (px - 1) & px)
   		for(py = sy; py <= n; py += py ^ (py - 1) & py)
            AIB[px][py] += val;
//    AIB[px][py] += val;
}
 
int query(int px, int py)
{
    int sy = py, sol = 0;
    for( ; px; px -= px ^ (px - 1) & px)
        for(py = sy; py; py -= py ^ (py - 1) & py)
            sol += AIB[px][py];
    return sol;
}

void dfs(int nod)
{
	int i, index, lim = v[nod].size(), limq = querylist[nod].size();
	if(nod)
		update(myupdate[nod].x, myupdate[nod].y, myupdate[nod].z);

	for(i = 0; i < limq; i++)
	{
		index = querylist[nod][i];
		sol[index] = query(myquery[index].x, myquery[index].y);
		//printf("Sunt la nodul %d si rezultatul pentru query-ul %d (adica) este %d\n",nod,index,sol[index]);
	}
	for(i = 0; i < lim; i++)
		dfs(v[nod][i]);
		
	if(nod)
		update(myupdate[nod].x, myupdate[nod].y, -myupdate[nod].z);
}

void InitialPB()
{
	sol.pb(0);
	stiva.pb(0);
	myupdate.pb(mp(mp(0, 0), 0));	
	myquery.pb(mp(mp(0, 0), 0));
}

int main ()
{
	int i, steps, tip, a, b, c;
	
	assert( freopen("undo.in","r",stdin) != NULL);
	assert( freopen("undo.out","w",stdout) != NULL );
	
	InitialPB();
	
	assert(scanf("%d%d",&n,&m) == 2);
	assert(1 <= n && n <= 520);
	assert(1 <= m && m <= 500000);
	int sum = 0;
	for(i = 1; i <= m; i++)
	{
		assert( scanf("%d",&tip) == 1 );
		assert(1 <= tip && tip <= 3);
		if(tip == 1)
		{
			nrupdate++;
			nonquery++;
			assert( scanf("%d%d%d",&a,&b,&c) == 3 );
			assert(1 <= a && a <= n && 1 <= b && b <= n && -2000 <= c && c <= 2000);
			sum += c;
			myupdate.pb(mp(mp(a,b),c));
			stiva.pb(nrupdate);
			v[stiva[nonquery - 1]].pb(nrupdate);
		//	printf("In stiva la pozitia nonquery = %d am pus %d\n",nonquery, nrupdate);
			//printf("Am tras muchie de la %d ld %d\n",stiva[nonquery - 1], nrupdate);
		}
		else if(tip == 2)
		{
			nrquery++;
			assert( scanf("%d%d",&a,&b) == 2 );
			assert(1 <= a && a <= n && 1 <= b && b <= n);			
			
			myquery.pb(mp(mp(a,b),0));
			querylist[stiva[nonquery]].pb(nrquery);
		//	printf("Query-ul %d la momentul %d\n",nrquery, stiva[nonquery]);
		}
		else
		{
			nonquery++;
			assert( scanf("%d",&steps) == 1 );
			assert(steps <= nonquery - 1);
			stiva.pb(stiva[nonquery - steps - 1]);
		//	printf("Ultimul nod este %d\n",stiva[nonquery]);
		}
	}
	assert(-1000000000 <= sum && sum <= 1000000000);
	for(i = 1; i <= nrquery; i++)
		sol.pb(0);
	dfs(0);
	
	for(i = 1; i <= nrquery; i++)
		printf("%d\n",sol[i]);
	
	return 0;
}




