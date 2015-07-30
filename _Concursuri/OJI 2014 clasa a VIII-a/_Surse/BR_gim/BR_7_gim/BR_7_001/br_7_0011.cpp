//Problema 1- PATRAT
#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ifstream f("patrat.in");
    ofstream g("patrat.out");
    int n,m,i,j,nrstele,poz,maxim;
    int a[200][200],lin[100],col[100];
    f>>n>>m; //n linii si m coloane
    //bordez matricea
    for (i=1; i<=m+1; i++){
        a[0][i]=0;
        a[n+1][i]=0;
    }
    for (i=1; i<=n+1; i++){
        a[i][0]=0;
        a[i][m+1]=0;
    }
    for (i=1; i<=n; i++)
        for (j=1; j<=m; j++)
            f>>a[i][j];
    poz=0;
    nrstele=0;
    for (i=1; i<=n; i++)
        for (j=1; j<=m; j++)
            //caut stele stralicitoare
            //diagonala
            if (a[i-1][j-1]<a[i][j] && a[i+1][j+1]<a[i][j] && a[i-1][j+1]<a[i][j] && a[i+1][j-1]<a[i][j])
                //veritcala
                if (a[i][j-1]<a[i][j] && a[i][j+1]<a[i][j])
                    //orizontala
                    if (a[i-1][j]<a[i][j] && a[i+1][j]<a[i][j] )
                    {
                        //a[i][j]= stea stralucitoare
                        nrstele++;
                        poz++;
                        //retin coordonatele
                        lin[poz]=i;
                        col[poz]=j;
                        if (j!=m)
                            j++;
                    }
    g<<nrstele<<'\n';
    g<<"0"<<'\n';
    maxim=0;
    i=1;
    j=poz+1;
    while (i<=poz){
        j--;
        if (col[i]==col[j]){
            if (lin[j]-lin[i]+1>maxim && col[j]<m && col[i]<m )
                maxim=lin[j]-lin[i]+1;
        }
        if (j==1){
            j=poz+1;
            i++;
        }
    }
    g<<maxim<<'\n';

    f.close();
    g.close();
    return 0;
}
