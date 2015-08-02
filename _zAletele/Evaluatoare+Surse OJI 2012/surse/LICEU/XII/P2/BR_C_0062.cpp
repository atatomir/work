#include <fstream>
#include<string.h>
using namespace std;

ifstream f ("subsecvente.in");
ofstream g("subsecvente.out");
char s1[10001],s2[10001],s3[10001],s4[10001];
int i,j,k,p,l1,l2,l3,l4,m,n;

void maxim3(int &l1, int &l2, int &l3, char s1[10001], char s2[10001], char s3[10001])
{
    int maxim=0,minim=99000;
    if (maxim<l1) maxim=l1;
    if (maxim<l2) maxim=l2;
    if (maxim<l3) maxim=l3;
    if (minim>l1) minim=l1;
    if (minim>l2) minim=l2;
    if (minim>l3) minim=l3;
    int aux;
    char auxs[10001];
    if (l2==maxim)
    {
        strcpy(auxs,s1);
        strcpy(s1,s2);
        strcpy(s2,auxs);
        aux=l1;
        l1=l2;
        l2=aux;
    }
    if (l3==maxim)
    {
        strcpy(auxs,s1);
        strcpy(s1,s3);
        strcpy(s3,auxs);
        aux=l1;
        l1=l3;
        l3=aux;
    }
    if (l1==minim)
    {
        strcpy(auxs,s3);
        strcpy(s3,s1);
        strcpy(s1,auxs);
        aux=l3;
        l3=l1;
        l1=aux;
    }
    if (l2==minim)
    {
        strcpy(auxs,s3);
        strcpy(s3,s2);
        strcpy(s2,auxs);
        aux=l3;
        l3=l2;
        l2=aux;
    }
}

void maxim4(int &l1, int &l2, int &l3, int &l4, char s1[10001], char s2[10001], char s3[10001], char s4[10001])
{
    int maxim=0,minim=99000;
    if (maxim<l1) maxim=l1;
    if (maxim<l2) maxim=l2;
    if (maxim<l3) maxim=l3;
    if (maxim<l4) maxim=l4;
    if (minim>l1) minim=l1;
    if (minim>l2) minim=l2;
    if (minim>l3) minim=l3;
    if (minim>l4) minim=l4;
    int aux;
    char auxs[10001];
    if (l2==maxim)
    {
        strcpy(auxs,s1);
        strcpy(s1,s2);
        strcpy(s2,auxs);
        aux=l1;
        l1=l2;
        l2=aux;
    }
    if (l3==maxim)
    {
        strcpy(auxs,s1);
        strcpy(s1,s3);
        strcpy(s3,auxs);
        aux=l1;
        l1=l3;
        l3=aux;
    }
    if (l4==maxim)
    {
        strcpy(auxs,s1);
        strcpy(s1,s4);
        strcpy(s4,auxs);
        aux=l1;
        l1=l4;
        l4=aux;
    }
    if (l1==minim)
    {
        strcpy(auxs,s4);
        strcpy(s4,s1);
        strcpy(s1,auxs);
        aux=l4;
        l4=l1;
        l1=aux;
    }
    if (l2==minim)
    {
        strcpy(auxs,s4);
        strcpy(s4,s2);
        strcpy(s2,auxs);
        aux=l4;
        l4=l2;
        l2=aux;
    }
    if (l3==minim)
    {
        strcpy(auxs,s4);
        strcpy(s4,s3);
        strcpy(s3,auxs);
        aux=l4;
        l4=l3;
        l3=aux;
    }
}

int valid1(int x, int y, char s1[10001], char s2[10001])
{
    int i,j=0;
    char aux[10001];
    for (i=x;i<=y;i++)
    {
        aux[i-x]=s2[i];
    }
    aux[i]=0;
    if (strstr(s1,aux)==0) return 0;
    else return strlen(aux);
}

int valid2(int x, int y, char s1[10001], char s2[10001], char s3[100])
{
    int i,j=0;
    char aux[10001];
    for (i=x;i<=y;i++)
    {
        aux[i-x]=s3[i];
    }
    aux[i]=0;
    if (strstr(s1,aux)!=0 && strstr(s2,aux)!=0) return strlen(aux);
    else return 0;
}

int valid3(int x, int y, char s1[10001], char s2[10001], char s3[10001], char s4[10001])
{
    int i,j=0;
    char aux[10001];
    for (i=x;i<=y;i++)
    {
        aux[i-x]=s4[i];
    }
    aux[i]=0;
    if (strstr(s1,aux)!=0 && strstr(s2,aux)!=0 && strstr(s3,aux)!=0) return strlen(aux);
    else return 0;
}

int main()
{
    f>>n;
    if (n==2)
    {
        f>>s1; f.get();
        f>>s2;
        l1=strlen(s1);
        l2=strlen(s2);
        if (l1>l2)
        {
            for (i=0;i<l2;i++)
                for (j=l2-1;j>=i;j--)
                    if (m<valid1(i,j,s1,s2)) m=valid1(i,j,s1,s2);
        }
        else
        {
            for (i=0;i<l1;i++)
                for (j=l1-1;j>=i;j--)
                    if (m<valid1(i,j,s2,s1)) m=valid1(i,j,s2,s1);
        }
    }
    else if (n==3)
    {
        f>>s1; f.get();
        f>>s2; f.get();
        f>>s3;
        l1=strlen(s1);
        l2=strlen(s2);
        l3=strlen(s3);
        maxim3(l1,l2,l3,s1,s2,s3);
        for (i=0;i<l3;i++)
                for (j=l3-1;j>=i;j--)
                    if (m<valid2(i,j,s1,s2,s3)) m=valid2(i,j,s1,s2,s3);
    }
    else if (n==4)
    {
        f>>s1; f.get();
        f>>s2; f.get();
        f>>s3; f.get();
        f>>s4;
        l1=strlen(s1);
        l2=strlen(s2);
        l3=strlen(s3);
        l4=strlen(s4);
        maxim4(l1,l2,l3,l4,s1,s2,s3,s4);
        for (i=0;i<l4;i++)
                for (j=l4-1;j>=i;j--)
                    if (m<valid3(i,j,s1,s2,s3,s4)) m=valid3(i,j,s1,s2,s3,s4);

    }
    g<<m<<"\n";
    f.close();
    g.close();
    return 0;
}
