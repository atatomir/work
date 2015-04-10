#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

#define maxL 100011

long i,cnt,x,y;
char s[maxL],pp[maxL];
stack<char> S;
stack<long> SS;
short rankOp[2000];

void makeDef(){
    rankOp['(']=rankOp[')']=0;
    rankOp['+']=rankOp['-']=1;
    rankOp['*']=rankOp['/']=2;
}

void goPolnish(){
    long i;

    S.push('(');

    for(i=1;s[i]!='\0';i++){
        if(s[i]>='0' && s[i] <= '9'){
            pp[++cnt]=',';
            while(s[i]>='0' && s[i] <= '9') pp[++cnt] = s[i++];
            i--;
            continue;
        }

        if(s[i]=='('){
            S.push(s[i]);
        } else
        if(s[i]==')'){
            while(S.top()!='('){
                pp[++cnt] = S.top();
                S.pop();
            }
            S.pop();
        } else {
            while(rankOp[S.top()] >= rankOp[s[i]]){
                pp[++cnt] = S.top();
                S.pop();
            }
            S.push(s[i]);
        }
    }

    while(!S.empty()){
        pp[++cnt] = S.top();
        S.pop();
    }
    cnt--;
}

long getNr(){
    long ans=0;
    i++;
    while(pp[i]>='0'&&pp[i]<='9'){
        ans = ans*10 + pp[i]-'0';
        i++;
    }
    i--;
    return ans;
}

int main()
{
    freopen("evaluare.in","r",stdin);
    freopen("evaluare.out","w",stdout);

    makeDef();

    scanf("%s",s+1);
    goPolnish();

    for(i=1;i<=cnt;i++){
        if(pp[i]==','){
            x=getNr();
            SS.push(x);
            continue;
        }

        y = SS.top(); SS.pop();
        x = SS.top(); SS.pop();

        if(pp[i]=='+') SS.push(x+y);
        if(pp[i]=='-') SS.push(x-y);
        if(pp[i]=='*') SS.push(x*y);
        if(pp[i]=='/') SS.push(x/y);
    }

    x = SS.top();
    printf("%ld",x);

    return 0;
}
