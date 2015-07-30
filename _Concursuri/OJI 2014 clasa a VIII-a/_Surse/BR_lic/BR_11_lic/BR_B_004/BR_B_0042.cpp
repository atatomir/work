#include <cstdio>
using namespace std;
long long n,c,p,i,j,a[2001],aux;
int main()
{
	freopen("fractii2.in","r",stdin);
	freopen("fractii2.out","w",stdout);
	scanf("%ld%ld",&p,&n);
	if(p==1){
		c=1;while(n!=2){printf("%d ",c);c++;n--;}
		printf("%ld %ld\n",c,c);
			}
	if(p==2){
		a[1]=1;
		a[2]=1;
		a[3]=1;
		for(i=4;i<=n;i++){
			for(j=1;j<=i/2;j++){
				if(j!=n-j){
				aux=(a[j]*a[i-j])%100003;
						  }
				else{
					aux=((a[j]*(a[j]+1))/2)%100003;
					}
				a[i]=(a[i]+aux)%100003;
							   }
						 }
		printf("%lld\n",a[n]);
			}
return 0;
}