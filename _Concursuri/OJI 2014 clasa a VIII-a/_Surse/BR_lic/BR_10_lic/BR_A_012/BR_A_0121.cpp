#include <fstream>
using namespace std;

ifstream f("ferma.in");
ofstream g("ferma.out");

int v, m, n, dl[4]={-1, 0, 1, 0}, dc[4]={0, 1, 0, -1}, lmn, lm, p, ferma2[401][401], lg[160804], im, jm;
char aux[401], ferma[401][401], caut, cul[160804];

void bordare()
{
    for(int i=0; i<=m+1; i++)
        ferma[i][0]=ferma[i][n+1]=-1;
    for(int i=0; i<=n+1; i++)
        ferma[0][i]=ferma[m+1][i]=-1;
}

void citire()
{
    for(int i=1; i<=m; i++)
    {
        f >> aux;
        for(int j=0; j<n; j++)
            ferma[i][j+1]=aux[j];
    }
    bordare();
}

void fill(int i, int j)
{
    if(ferma[i][j]==caut)
    {
        ferma[i][j]='0';
        if(v==2) ferma2[i][j]=p;
        lmn++;
        for(int k=0; k<4; k++) fill(i+dl[k], j+dc[k]);
    }
}

int dif(int i, int j, int k, int b)
{
    if(k==1 && b==0 && cul[ferma2[i+dl[b]][j+dc[b]]]!=cul[ferma2[i+dl[b]][j+dc[k]]] && cul[ferma2[i+dl[k]][j+dc[k]]]!=cul[ferma2[i+dl[b]][j+dc[k]]])
        return 1;
    else if(k==2 && b==1 && cul[ferma2[i+dl[b]][j+dc[b]]]!=cul[ferma2[i+dl[k]][j+dc[b]]] && cul[ferma2[i+dl[k]][j+dc[k]]]!=cul[ferma2[i+dl[k]][j+dc[b]]])
        return 1;
    else if(k==3 && b==2 && cul[ferma2[i+dl[b]][j+dc[b]]]!=cul[ferma2[i+dl[b]][j+dc[k]]] && cul[ferma2[i+dl[k]][j+dc[k]]]!=cul[ferma2[i+dl[b]][j+dc[k]]])
        return 1;
    else if(k==4 && b==0 && cul[ferma2[i+dl[b]][j+dc[b]]]!=cul[ferma2[i+dl[b]][j+dc[k]]] && cul[ferma2[i+dl[k]][j+dc[k]]]!=cul[ferma2[i+dl[b]][j+dc[k]]])
        return 1;
    else if((b==k-2 || b==k+2) && ferma2[i+dl[b]][j+dc[b]]!=ferma2[i+dl[k]][j+dc[k]] && ferma2[i+dl[b+1]][j+dc[b+1]]!=ferma2[i+dl[k+1]][j+dc[k+1]] && ferma2[i+dl[b-1]][j+dc[b-1]]!=ferma2[i+dl[k-1]][j+dc[k-1]])
        return 1;
    return 0;
}

int main()
{
    f >> v >> m >> n;
    citire();
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
            if(ferma[i][j]>='a' && ferma[i][j]<='z')
            {
                caut = ferma[i][j];
                lmn = 0; p++;
                if(v==2) cul[p]=caut;
                fill(i, j);
                if(lmn>lm) lm=lmn;
                if(v==2) lg[p]=lm;
            }
    if(v==1)
    {
        g << lm;
        g.close();
    } else if(v==2)
    {
        lm=0;
        for(int i=1; i<=m; i++)
            for(int j=2; j<=n; j++)
                for(int k=0; k<4; k++)
                    if(lg[ferma2[i+dl[k]][j+dc[k]]])
                        for(int b=0; b<4; b++) if(b!=k && dif(i, j, k, b) && cul[ferma2[i][j]]!=cul[ferma2[i+dl[k]][j+dc[k]]] && cul[ferma2[i][j]]!=cul[ferma2[i+dl[b]][j+dc[b]]] &&
                                                  lg[ferma2[i+dl[k]][j+dc[k]]]+lg[ferma2[i+dl[b]][j+dc[b]]]>lm && cul[ferma2[i+dl[k]][j+dc[k]]]==cul[ferma2[i+dl[b]][j+dc[b]]])
                        {
                            im = i; jm = j;
                            caut = cul[ferma2[i+dl[b]][j+dc[b]]];
                            lm=lg[ferma2[i+dl[k]][j+dc[k]]]+lg[ferma2[i+dl[b]][j+dc[b]]];
                        }
        g << im << " " << jm << '\n' << caut;
    }
    return 0;
}
