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
    FILE *fIn = fopen("cub2.in","r");
    FILE *fOut = fopen("cub2.out","r");
    FILE *fOk = fopen("cub2.ok","r");

    if(fOut==NULL){
        result("Fisier de iesire lipsa",0);
        return 0;
    }

    long p ; fscanf(fIn,"%ld",&p);
    if(p==1){
        long cA,cB,cC,A,B,C;
        fscanf(fOk,"%ld %ld %ld",&cA,&cB,&cC);
        if(fscanf(fOut,"%ld %ld %ld",&A,&B,&C) < 3){
            result("Fisier de iesire formatat gresit",0);
            return 0;
        }
        if(A!=cA || B!=cB || C!=cC){
            result("Incorect",0);
            return 0;
        }
        result("Corect",2);
    } else {
        long cA,cB,cC,cD,A,B,C,D;
        fscanf(fOk,"%ld%ld%ld%ld",&cA,&cB,&cC,&cD);
        if(fscanf(fOut,"%ld%ld%ld%ld",&A,&B,&C,&D) < 4){
            result("Fisier de iesire formatat gresit",0);
            return 0;
        }
        if(A!=cA || B!=cB || C!=cC || D!=cD){
            result("Incorect",0);
            return 0;
        }
        result("Corect",8);
    }


    return 0;
}
