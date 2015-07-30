
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
    FILE *fIn = fopen("flooow.in","r");
    FILE *fOut = fopen("flooow.out","r");
    FILE *fOk = fopen("flooow.ok","r");

    if(fOut == NULL) result("Fisier de iesire lipsa.",0);

    long long a,b,sa,sb;
    fscanf(fOk,"%lld %lld",&sa,&sb);
    if(fscanf(fOut,"%lld %lld",&a,&b)<2) result("Fisier de iesire corupt.",0);

    if(sa!=a || sb!=b) result("Nu prea ai flooow!",0);

    long long t;
    fscanf(fIn,"%lld",&t);

    long pct;
    if(t<=40) pct = 3; else pct = 5;

    result("Ai flooow!",pct);

    return 0;
}
