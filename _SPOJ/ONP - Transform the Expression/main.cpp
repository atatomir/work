#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxL 411

long t;
char s[maxL];

short rankOp[2000];
stack<char> S;

void makeDef(){
    rankOp['+']=rankOp['-']=1;
    rankOp['*']=rankOp['/']=2;
    rankOp['^']=3;
    rankOp['(']=rankOp[')']=0;
}

void solve(){
    long i;
    while(!S.empty()) S.pop(); S.push('(');

    for(i=1;s[i]!='\0';i++){

        if(s[i]>='a' && s[i]<='z'){
            printf("%c",s[i]);
            continue;
        }

        if(s[i]=='('){
            S.push(s[i]);
        } else
        if(s[i]==')'){
            while(S.top()!='('){
                printf("%c",S.top());
                S.pop();
            }
            S.pop();
        } else {
            if(s[i]=='^'){
                S.push('^');
            } else {
                while(rankOp[S.top()] >= rankOp[s[i]]){
                    printf("%c",S.top());
                    S.pop();
                }
                S.push(s[i]);
            }
        }
    }

    while(!S.empty()){
        if(S.top()!='(') printf("%c",S.top());
        S.pop();
    }
    printf("\n");
}

int main()
{
    freopen("test.in","r",stdin);

    makeDef();

    scanf("%ld\n",&t);
    for(;t;t--){
        scanf("%s\n",s+1);
        solve();
    }

    return 0;
}
