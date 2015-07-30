#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

typedef pair<long,long> QElem;

#define maxN 9010

long t,i,n,sum,k,decr,a[maxN];
queue<QElem> Q;
bool ok;

int main()
{
    freopen("auto.in","r",stdin);
    freopen("auto.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        sum = 0;

        scanf("%ld",&n);
        for(i=1;i<=n;i++){
            scanf("%ld",&a[i]);
            sum += a[i];
        }

        printf("%ld ",1L);
        for(k=2;k<=n;k++){
            while(!Q.empty()) Q.pop();

            if(sum % k) continue;
            decr = 0; ok = true;

            for(i=1;i<=n-k+1;i++){
                if(!Q.empty()){
                    if(Q.front().second == i){
                        decr -= Q.front().first;
                        Q.pop();
                    }
                }

                if(a[i] - decr < 0){
                    ok = false;
                    break;
                }

                Q.push(make_pair(a[i]-decr,i+k));
                decr += a[i] - decr;
            }

            if(!ok) continue;

            for(i=n-k+2;i<=n;i++){
                if(!Q.empty()){
                    if(Q.front().second == i){
                        decr -= Q.front().first;
                        Q.pop();
                    }
                }

                if(a[i] - decr != 0){
                    ok = false;
                    break;
                }
            }

            if(ok) printf("%ld ",k);
        }
        printf("\n");
    }


    return 0;
}
