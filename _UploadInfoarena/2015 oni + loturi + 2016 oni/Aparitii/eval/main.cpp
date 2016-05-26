#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void result(char msg[], int p)
{
    fprintf(stderr, "%s", msg);
    printf("%d", p);
    exit(0);
}

#define maxN 1000011

long n,i;
char s[maxN],t[maxN];

int main()
{
    FILE *fIn = fopen("aparitii2.in","r");
    FILE *fOut = fopen("aparitii2.out","r");
    FILE *fOk = fopen("aparitii2.ok","r");

    if(fOut == NULL) result("Fisier de iesire lipsa",0);
    fscanf(fIn,"%s\n%s",t+1,s+1);

    n = strlen(s+1); n/=2;
    for(i=1;i<=n;i++){
        long aOk,a;
        fscanf(fOk,"%ld",&aOk);
        if(fscanf(fOut,"%ld",&a)==0) result("Fisier de iesire corupt",0);
        if(a!=aOk) result("Mai incearca...",0);
    }

    if(n<=10000) result("Corect",3);
    else           result("Corect",4);

    return 0;
}
