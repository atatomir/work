#include <cstdio>
using namespace std;
int a[202][202],r,n,m,x,st[500],sf[500],poz,next[1000],depa[1000],prev[1000],dest[1000],p,xc,yc,k,i,y,lee[40001][2],leemax,valee[40001];
int tunnel,ra,g,xd,yd,xa,ya,node1,node2,nindex[40001],gindex[1000],euler[1000],maxeuler,aux,enext[1000];
void fox(int x, int y)
{
	a[x][y]=-1;
	if(r>0){
		a[x-1][y]=-1;
		a[x+1][y]=-1;
		a[x][y-1]=-1;
		a[x][y+1]=-1;
		   }
	if(r>1){
		a[x-1][y-1]=-1;
		a[x-1][y+1]=-1;
		a[x+1][y-1]=-1;
		a[x+1][y+1]=-1;
		if(x-2>=0){a[x-2][y]=-1;}
		if(y-2>=0){a[x][y-2]=-1;}
		if(x+2<=n){a[x+2][y]=-1;}
		if(y+2<=m){a[x][y+2]=-1;}
		   }
}
void add(int x, int y)
{
	if(st[x]==0){st[x]=poz;sf[x]=0;}
	else{next[sf[x]]=poz;}
	depa[poz]=x;prev[poz]=sf[x];sf[x]=poz;dest[poz]=y;next[poz]=0;
}
void remove(int x)
{
	if(prev[x]==0){st[depa[x]]=next[x];}
	if(next[x]==0){sf[depa[x]]=prev[x];}
	next[prev[x]]=next[x];
	prev[next[x]]=prev[x];
}
int reverse(int q){if(q%2){return q+1;}return q-1;}
int main()
{
	freopen("cartite.in","r",stdin);
	freopen("cartite.out","w",stdout);
	scanf("%d",&p);
	scanf("%d%d",&n,&m);
	scanf("%d%d",&xc,&yc);
	scanf("%d",&k);
	for(i=1;i<=n;i++){a[i][0]=-1;a[i][m+1]=-1;}
	for(i=1;i<=m;i++){a[0][i]=-1;a[n+1][i]=-1;}
	for(i=1;i<=k;i++){
		scanf("%d%d%d",&x,&y,&r);
		fox(x,y);
					 }
	lee[1][0]=xc;lee[1][1]=yc;leemax=1;valee[1]=1;a[xc][yc]=1;
	i=1;
	while(i<=leemax){
		xc=lee[i][0];
		yc=lee[i][1];
		xc++;if(a[xc][yc]==0){leemax++;lee[leemax][0]=xc;lee[leemax][1]=yc;a[xc][yc]=valee[i]+1;valee[leemax]=valee[i]+1;}xc--;
		xc--;if(a[xc][yc]==0){leemax++;lee[leemax][0]=xc;lee[leemax][1]=yc;a[xc][yc]=valee[i]+1;valee[leemax]=valee[i]+1;}xc++;
		yc++;if(a[xc][yc]==0){leemax++;lee[leemax][0]=xc;lee[leemax][1]=yc;a[xc][yc]=valee[i]+1;valee[leemax]=valee[i]+1;}yc--;
		yc--;if(a[xc][yc]==0){leemax++;lee[leemax][0]=xc;lee[leemax][1]=yc;a[xc][yc]=valee[i]+1;valee[leemax]=valee[i]+1;}yc++;
		i++;
					}
	scanf("%ld",&tunnel);
	ra=50000;poz=0;g=0;
	for(i=1;i<=tunnel;i++){
		scanf("%d%d%d%d",&xd,&yd,&xa,&ya);
		if(a[xd][yd]>0){if(ra>a[xd][yd]){ra=a[xd][yd];xc=xd;yc=yd;}}
		if(a[xa][ya]>0){if(ra>a[xa][ya]){ra=a[xa][ya];xc=xa;yc=ya;}}
		node1=(xd-1)*m+yd-1;
		node2=(xa-1)*m+ya-1;
		if(nindex[node1]==0){nindex[node1]=++g;gindex[g]=node1;}
		if(nindex[node2]==0){nindex[node2]=++g;gindex[g]=node2;}
		poz++;add(nindex[node1],nindex[node2]);
		poz++;add(nindex[node2],nindex[node1]);
						  }
	if(p==1){printf("%ld %ld %ld\n",xc,yc,ra-1);return 0;}
		euler[1]=nindex[(xc-1)*m+yc-1];maxeuler=1;
		for(i=1;i<=tunnel;i++){
			x=st[euler[i]];poz=i;
			if(x){aux=enext[i];}else{aux=enext[maxeuler];}
			while(x){
				maxeuler++;
				enext[poz]=maxeuler;
				euler[maxeuler]=dest[x];
				remove(x);
				remove(reverse(x));
				x=st[euler[maxeuler]];
				poz=maxeuler;
					}
			enext[maxeuler]=aux;
						 }
	x=1;
	while(x){printf("%ld %ld\n",gindex[euler[x]]/m+1,gindex[euler[x]]%m+1);x=enext[x];}
return 0;
}