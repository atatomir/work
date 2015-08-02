#include <iostream>
#include<fstream>
#include<string.h>
#include<math.h>

using namespace std;

int n,trans[5][50002],size[5],solfin[50001],solfinsize,solfinfalsaux[50001],solfinfals[50001],solfinsizefals,sumafinal;
char start[5][50001];

ifstream f("subsecvente.in");
ofstream g("subsecvente.out");

int verifica(int a,int b,int len,int i)
{
    solfinsizefals=0;
    int suma=0,lenfals=0;
    solfinfalsaux[0]=min(solfinfals[a],trans[i][b]);
    suma+=solfinfalsaux[0];
    for(int i=1;i<=len;i++)
    {
        a++;
        b++;
        if(solfinfals[a]!=trans[i][b])
        {
            solfinfalsaux[i]=min(solfinfals[a],trans[i][b]);
            suma+=solfinfalsaux[i];
            solfinsizefals++;
            i=len+1;
        }
        else
        {
            solfinfalsaux[i]=solfinfals[a];
            suma+=solfinfalsaux[i];
            solfinsizefals++;
        }

    }
    return suma;
}

void delimitare(int i)
{

    for(int k=0;k<=solfinsizefals;k++)
            solfinfals[k]=solfin[k];
    int b=0,a=1,len=1,suma=0,sumafals;
    while(a!=0)
    {
        sumafals=verifica(a,b,len,i);
        if(sumafals>suma)
        {
            suma=sumafals;
            for(int k=0;k<=solfinsizefals;k++)
            solfinfals[k]=solfinfals[k];
        }
        a--;
        len++;
    }
    while(b!=size[i]-1)
    {

        sumafals=verifica(a,b,len,i);

        if(sumafals>suma)
        {
            suma=sumafals;
            for(int k=0;k<=solfinsizefals;k++)
            solfinfals[k]=solfinfals[k];
        }
        if(b==-solfinsizefals+size[i]+1)
        len--;
        b++;
    }
    sumafinal=suma;
        for(int k=0;k<=solfinsizefals;k++)
            solfin[k]=solfinfals[k];
}

int main()
{
    int nvar,ok,i,j;
    char contr;
    f>>n;
    //citire+transformare
    for(i=1;i<=n;i++)
    {
        f>>start[i];
        if(start[i][0]=='a')
        {
            nvar=0;
            contr='a';
            ok=1;
            for(j=1;j<=strlen(start[i]);j++)
            {
                if(start[i][j]==contr) ok++;
                else
                {
                    trans[i][nvar]=ok;
                    ok=1;
                    nvar++;
                    if(contr=='a')
                        contr='b';
                    else contr='a';
                }
            }
            size[i]=nvar;
        }
        else
        {
            trans[i][0]=0;
            nvar=1;
            contr='b';
            ok=0;
            for(j=0;j<=strlen(start[i]);j++)
            {
                if(start[i][j]==contr)ok++;
                else
                {
                    trans[i][nvar]=ok;
                    ok=1;
                    nvar++;
                    if(contr=='a')
                        contr='b';
                    else contr='a';
                }
            }
            size[i]=nvar;
        }
    }
solfinsize=size[1];

    for(i=2;i<=n;i++)
    {

        for(j=0;j<=size[1];j++)
            solfin[j]=trans[1][j];
            delimitare(i);
    }

    g<<sumafinal+1;
    return 0;
}
