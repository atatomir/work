#include <iostream>
#include <cstdio>

using namespace std;

long n,i;
char x,y,z,t;
char s[10];

bool isOk(){
    long f = (x-'0')*10 + y-'0';
    long s = (z-'0')*10 + t-'0';

    if(f>=24 || s >= 60) return false;
    if(s==0) return true;
    if(f==s) return true;
    if((x==t)&&(y==z)) return true;
    if((x+1==y)&&(y+1==z)&&(z+1==t)) return true;
    f = f*100+s;

    if(f<1000) return false;
    while(f%2==0) f/=2;
    if(f==1) return true;
    return false;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++){
        scanf("%s\n",s+1);
        x = s[1]; y=s[2]; z=s[4]; t=s[5];
        if(isOk()){
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
