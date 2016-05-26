#include <iostream>
#include <cstdio>

using namespace std;

void result(char msg[], int p){
    fprintf(stderr, "%s", msg);
    printf("%d", p);
    exit(0);
}

int main()
{
    FILE *fIn = fopen("risc2.in","r");
    FILE *fOut = fopen("risc2.out","r");
    FILE *fOk = fopen("risc2.ok","r");

    if(fOut==NULL){
        result("Fisier de iesire lipsa",0);
        return 0;
    }

    long how,corr;
    fscanf(fOk,"%ld",&corr);
    if(fscanf(fOut,"%ld",&how) < 1){
        result("Fisier de iesire formatat gresit",0);
        return 0;
    }

    long p,n;
    fscanf(fIn,"%ld%ld",&p,&n);
    if(corr != how){
        result("Incorect",0);
        return 0;
    }

    if(p==1)
        result("Corect",5);
    else{
        if(n<=7000)
            result("Corect",4);
        else
            result("Corect",5);
    }



    return 0;
}
