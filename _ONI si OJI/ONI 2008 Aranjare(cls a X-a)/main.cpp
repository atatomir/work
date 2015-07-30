#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 5111

long n,i;
char s[maxN << 1];

long space;


void dMove(long pos){
    s[space] = s[pos];
    s[space+1] = s[pos+1];
    s[pos] = s[pos+1] = 'S';
    space = pos;

    printf("%ld\n",pos);
}
void Move(long pos){
    if(s[pos+1] == 'S'){
        dMove(2*n+1);
        dMove(pos);
    } else dMove(pos);

    for(long i = pos+2;i<=2*n+2;i++){
        if(s[i] == 'F') {
            if(i != 2*n+2) dMove(i); else{
                dMove(2*n+1);
                dMove(n+2);
                dMove(n-1);
                dMove(n+1);
            }
            break;
        }
    }
}

int main()
{
    freopen("aranjare.in","r",stdin);
    freopen("aranjare.out","w",stdout);

    scanf("%ld\n%s",&n,s+1);
    for(i=1;i<2*n+2;i++){
        if(s[i] == 'S') {space=i;break;}
    }

    for(i=1;i<=n;i++){
        if(s[i] != 'F') Move(i);
    }
    if(s[n+1] != 'S') dMove(n+1);

    return 0;
}
