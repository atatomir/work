#include <iostream>
#include <fstream>
using namespace std;
int a[100][100],x[100],y[100],z[100],t[100];
/*
Pentru primul punct la subiectul intai fac suma pe linii si verific sa vad care are cel mai mare numar de patratele goale, apoi
introducem valoarea cea mai mare in M.
La al doilea punct daca gasim o patratica goala, luam un contor care sa creasca odata cu gasirea patratelelor albe.
*/
int main()
{
    ifstream f("betasah.in");
    ofstream g("betasah.out");
    int N,D,K,M,P,i,j,max,s,gri,suprafatabuna;
    f>>N;f>>D;f>>K;
    M=0;
    s=0;
    for (i=1;i<=N;i++)
    {
        s=s+a[i][0];
        if (s>M)
            M=s;
    }
    g<<M<<endl;
    for (i=1;i<=N;i++)
        for (j=1;j<=N;j++)
            if (a[i][j]!=gri)
                suprafatabuna++;
    g<<suprafatabuna<<'\n';
    return 0;
}
