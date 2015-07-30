#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

long n,k,i,l,ans,pos;
long cont['Z'+10];
char s[56000];

queue<char> Q;

int main()
{
    freopen("teatru.in","r",stdin);
    freopen("teatru.out","w",stdout);

    scanf("%ld %ld",&n,&k);
    scanf("%s",s+1);

    i=0;
    while(i<=n){
        i++;
        if(!cont[s[i]]) k--;
        cont[s[i]]++;
        Q.push(s[i]);

        if(!k) break;
    }
    l = i;

    ans = Q.size(); pos = 1;
    for(i=l+1;i<=n;i++){
        if(!cont[s[i]]){
            while(1){
                char c = Q.front(); Q.pop();
                cont[c]--;
                if(!cont[c]) break;
            }
        }
        cont[s[i]]++;
        Q.push(s[i]);

        if(ans < Q.size()){
            ans = Q.size();
            pos = i - ans+1;
        }
    }

    printf("%ld\n",ans);
    for(i=pos;i<pos+ans;i++) printf("%c",s[i]);

    return 0;
}
