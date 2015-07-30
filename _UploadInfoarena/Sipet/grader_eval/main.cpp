#include <iostream>
#include <cstdio>

using namespace std;

void result(char msg[], int p){
    fprintf(stderr, "%s", msg);
    printf("%d", p);
    exit(0);
}

inline bool notPrime(long x){
    for(long i=2;i*i<=x;i++){
        if(x%i==0) return true;
    }
    return false;
}
long getPP(long x){
    x++;
    while(notPrime(x)) x++;
    return x;
}

int main()
{
    FILE *fIn = fopen("sipet.in","r");
    FILE *fOut = fopen("sipet.out","r");
    FILE *fOk = fopen("sipet.ok","r");

    if(fOut==NULL){
        result("Fisier de iesire lipsa",0);
        return 0;
    }


    long t,i,n,p1,p2,p3;
    long s,x,y,z,d;
    long _s,_x,_y,_z,_d;

    fscanf(fIn,"%ld",&t);
    for(;t;t--){
        fscanf(fIn,"%ld%ld",&n,&p1);
        if(fscanf(fOut,"%ld%ld%ld%ld%ld",&s,&x,&y,&z,&d)<5){
            result("Fisier de iesire corupt",0);
            return 0;
        }
        fscanf(fOk,"%ld%ld%ld%ld%ld",&_s,&_x,&_y,&_z,&_d);

        p2 = getPP(p1);
        p3 = getPP(p2);

        if(s!= _s || d!=_d){
            result("Mai incearca...",0);
            return 0;
        }
        if(s != x+y+z){
            result("Mai incearca...",0);
            return 0;
        }

        long ssum = x*p1 + y*p2 + z*p3;
        if(ssum+d != n){
            result("Mai incearca...",0);
            return 0;
        }
    }

    result("Bravo!",10);

    return 0;
}
