#include <iostream>
#include <cstdio>

using namespace std;

char ch;
long n,i,val,act;

void Impar(){
    for(i=1;i<=n;i++){
        act = n-i+1;
        if(i&1)
            val += (act+1)/2;
        else
            val += act/2;
    }

    if(ch=='S')
        printf("%ld",val);
    else{
        val<<=2;
        val -= ((n+1)/2)*4;
        val++;
        printf("%ld",val);
    }
}

void Par(){
    for(i=1;i<=n;i++){
        act = n-i+1;
        if(i&1)
            val += act/2;
        else
            val += (act+1)/2;
    }

    if(ch=='S')
        printf("%ld",val);
    else{
        val<<=2;
        val -= (n/2)*4;
        printf("%ld",val);
    }
}

int main()
{
    freopen("furnica.in","r",stdin);
    freopen("furnica.out","w",stdout);

    scanf("%c\n%ld",&ch,&n); n++;

    if(n&1) Impar(); else Par();




    return 0;
}
