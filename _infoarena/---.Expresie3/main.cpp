#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;

#define maxS 20111

long n,i,pos,sign,last;
char s[maxS];

long Ans['z'+10];
bool util['z'+10];
stack<long> S;

int main()
{
    freopen("expresie3.in","r",stdin);
    freopen("expresie3.out","w",stdout);

    scanf("%s",s); n = strlen(s);
    S.push(1); sign = last = 1;

    while(pos < n){
        if(s[pos] == '('){
            sign = last * S.top();
            S.push(sign);
            pos++;
            last = 1;
            continue;
        } else
        if(s[pos] == ')'){
            S.pop(); sign = S.top();
            pos++;
            continue;
        }

        if(s[pos] == '*')
            sign = S.top(),pos++,last=1;
        else
        if(s[pos] == '/')
            sign = -S.top(),pos++,last=-1;

        if(s[pos] >= 'a' && s[pos] <= 'z'){
            char c = s[pos++];
            util[c] = true;
            Ans[c] += sign;
        }
    }

    for(char c='a';c<='z';c++){
        if(!util[c]) continue;
        printf("%c %ld\n",c,Ans[c]);
    }

    return 0;
}
