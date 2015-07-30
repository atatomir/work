#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxS 350

long t,i,n,pos;
char s[maxS];

long vInd,cInd,x,f,v;

bool isDigit(char c){
    return c>='0'&&c<='9';
}
long getLong(){
    long ans =0,sign=1;
    if(s[pos]=='-'){sign=-1;pos++;}
    if(s[pos]=='+') pos++;
    while(isDigit(s[pos])) ans = ans*10+s[pos++]-'0';

    if(s[pos]=='x' && !isDigit(s[pos-1])) ans=1;
    return ans*sign;
}

int main()
{
    freopen("ecuatii2.in","r",stdin);
    freopen("ecuatii2.out","w",stdout);

    scanf("%ld\n",&t);
    for(;t;t--){
        memset(s,0, sizeof(s));
        scanf("%s\n",s+1);

        vInd = 1; cInd = -1; x=f=0; pos=1;
        while(isDigit(s[pos])||s[pos]=='='||s[pos]=='+'||s[pos]=='x'||s[pos]=='-'){
            if(s[pos]=='='){vInd*=-1;cInd*=-1;pos++;}
            v = getLong();
            if(s[pos]=='x'){
                x += vInd*v;
                pos++;
            } else {
                f += cInd*v;
            }
        }

        if(x==f && x==0) printf("infinit\n"); else
        if(x==0) printf("imposibil\n"); else
        printf("%.5lf\n",1.00*f/x);
    }

    return 0;
}
