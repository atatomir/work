#include<stdio.h>
#include<queue>
#include<vector>
using namespace std;
 
#define pii pair< pair<int, int>, int>
#define x first.first
#define y first.second
#define z second
#define mp make_pair
#define pb push_back
#define INF 1000000005
#define NMAX 1506
#define MMAX 30005
#define pi pair<int, int>
 
pii muchie[MMAX];
int n, m, sol[NMAX];
int dist[NMAX], tata[NMAX];
char viz[NMAX];
vector<int> v[NMAX];
 
class cmp
{
public:
    bool operator()(const pi& a,const pi& b)
    {
	    return a > b;
	}
};
  
priority_queue< pi, vector< pi >, cmp> myset;
  
inline void Reset()
{
    int i;
    for(i = 1; i <= n; i++)
    {
        dist[i] = INF;
        tata[i] = 0;
        viz[i] = 0;
    }
}
  
inline void dijkstra(int nod)
{
    int i, p, j, lim, a, b, c, index, aux;
    pi p2;
    dist[nod] = 0;
    myset.push(mp(0, nod));
    while(1)
    {
 		if(myset.empty())
 			break;

        p2 = myset.top();
        myset.pop();
        p = p2.second;

        if(viz[p])
          	continue;
        viz[p] = 1;
        lim = v[p].size();
        for(j = 0; j < lim; j++)
        {
            index = v[p][j];
            a = muchie[index].x;
            b = muchie[index].y;
            if(b == p)
            {
                aux = b;
                b = a;
                a = aux;
            }
            c = muchie[index].z;
            if(dist[b] > dist[a] + c)
            {
                dist[b] = dist[a] + c;
                if(a == nod)
	                tata[b] = b;
	            else
	            	tata[b] = tata[a];
                myset.push( mp(dist[b], b));
            }
        }
    }
    for(i = 1; i <= m; i++)
    {
        a = muchie[i].x;
        b = muchie[i].y;
        c = muchie[i].z;
        if(a == nod && tata[b] == b)
            continue;
        if(b == nod && tata[a] == a)
            continue;
		if(a == nod)
        	sol[a] = min(sol[a], c + dist[b]);
        if(b == nod)
          	sol[b] = min(sol[b], c + dist[a]);
        if(tata[a] == tata[b])
            continue;
        sol[nod] = min(sol[nod], dist[b] + c + dist[a]);  
    }
}

int main ()
{
    int i, a, b , c;
    freopen("dbz.in","r",stdin);
    freopen("dbz.out","w",stdout);
     
    scanf("%d%d",&n,&m);
    for(i = 1; i <= m; i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        v[a].pb(i);
        v[b].pb(i);
        muchie[i] = mp(mp(a,b),c);
    }
        
    for(i = 1; i <= n; i++)
        sol[i] = INF;
     
    for(i = 1; i <= n; i++)
    {
        Reset();
        dijkstra(i);
    }
 
    for(i = 1; i <= n; i++)
        if(sol[i] == INF)
            printf("-1 ");
        else
            printf("%d ",sol[i]);
    printf("\n");
         
    return 0;
}



