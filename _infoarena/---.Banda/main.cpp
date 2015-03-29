#include <iostream>
#include <cstdio>

using namespace std;

long n,i,dim,k,dimh;
long v[35];

long pos,h,op;

void Right(){
    dim >>= 1; dimh <<= 1;
    if(pos > dim){
        h = dimh-h+1;
        pos = dim+dim-pos+1;
    }
}
void Left(){
    dim >>= 1; dimh <<= 1;
    if(pos > dim){
        pos -= dim;
    } else {
        h = dimh-h+1;
        pos = dim-pos+1;
    }
}
void rRight(){
    dim <<= 1; dimh >>= 1;
    if(h > dimh){
        h = dimh+dimh-h+1;
        pos = dim-pos+1;
    }
}
void rLeft(){
    dim <<= 1; dimh >>= 1;
    if(h <= dimh){
        pos += dim >> 1;
    } else {
        h = dimh+dimh-h+1;
        pos = (dim>>1)-pos+1;
    }
}

int main()
{
    freopen("banda.in","r",stdin);
    freopen("banda.out","w",stdout);

    scanf("%ld%ld",&n,&k);

    dim = 1<<n;
    for(i=1;i<=n;i++){
        dim >>= 1;
        if(k <= dim)
            v[i] = 1;
        else {
            v[i] = 0;
            k -= dim;
        }
    }

    scanf("%ld%ld",&op,&k);
    if(op == 1){
        pos = k; h = 1;
        dim = 1<<n; dimh = 1;

        for(i=1;i<=n;i++){
            if(v[i]) Right(); else Left();
        }
        printf("%ld",h);
    } else {
        pos = 1; h = k;
        dim = 1; dimh = 1<<n;

        for(i=n;i;i--){
            if(v[i]) rRight(); else rLeft();
        }
        printf("%ld",pos);
    }

    return 0;
}
