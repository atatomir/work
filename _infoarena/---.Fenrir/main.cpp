#include <iostream>
#include <cstdio>
 
using namespace std;
 
long i,j;
 
inline void set(long x,long y){
    printf("%ld %ld\n",x,y);
}
 
int main()
{
    freopen("fenrir.out","w",stdout);
 
    cout << "99\n";
    for(i=2;i<=10;i++) set(1,i);
    for(i=2;i<=10;i++)
        for(j=11;j<=20;j++)
            set(i,j);
 
    return 0;
}