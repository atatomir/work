#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

#define maxN 200010

long n,i,a[maxN];
stack<long> S;
bool op[maxN];
long Ans;

int main()
{
    freopen("copaci4.in","r",stdin);
    freopen("copaci4.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);

        if(!S.empty())
        while(S.top() < a[i]){
            S.pop();
            if(S.empty()) break;
        }

        if(!S.empty()){
            if(S.top() == a[i]) continue;
            op[i] = true;
        }
        S.push(a[i]);
    }

    while(!S.empty()) S.pop();

    for(i=n;i;i--){
        if(!S.empty())
        while(S.top() < a[i]){
            S.pop();
            if(S.empty()) break;
        }

        if(!S.empty()){
            if(S.top() == a[i]) continue;

            if(op[i]) Ans++;
        }
        S.push(a[i]);
    }

    printf("%ld",Ans);

    return 0;
}
