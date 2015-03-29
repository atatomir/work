#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const long val[10] = {0,2,5,5,4,5,6,3,7,6};

long p,i,n,cont,ans[30],j,rez;
char s[30];
bool noLimit=false;

int main()
{
    freopen("7segmente.in","r",stdin);
    freopen("7segmente.out","w",stdout);

    scanf("%s %ld",&s,&p);
    n = strlen(s);

    rez = 0;
    for(i=0;i<n;i++) rez += val[s[i] - '0'];
    printf("%ld ",rez);

    for(cont=0;cont < n && p > 1;cont++){
        ans[cont] = 1; p -= 2;
    }

    if(cont < n) noLimit = true;

    for(i=0;i < cont;i++){
        if(noLimit) s[i] = '9';
        for(j = s[i]-'0';j > 1;j--){
            long dif = val[j] - 2;
            if(dif <= p){
                p -= dif;
                ans[i] = j;
                break;
            }
        }
        if (ans[i] != s[i]-'0') noLimit = true;
    }

    for(i=0;i<cont;i++) printf("%ld",ans[i]);

    return 0;
}
