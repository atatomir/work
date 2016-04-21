// Istvan Budai - 100 de puncte - O(N * M * D^2)
#include <iostream>
#include <fstream>
using namespace std;

const int Rmax=1001;
const int Cmax=1001;

ifstream f("intrus.in");
ofstream g("intrus.out");
int X[Rmax][Cmax];
int W[1000001];
typedef struct elem{int r; int c; int niv; int maxpri;};
int pt=0;
elem Y[Rmax*Cmax+1], Temp;

bool prim(int k)
{
    if (k<2) return false;
    if (k==2) return true;
    if (k>2 && k%2==0) return false;
    for (int i=3; i*i<=k; i=i+2) if (k%i==0) return false;
    return true;
}

int nivel(int M[][Cmax], int is, int js, int r, int c, int d, int &mx)
{
    int i1, j1, i2, j2, v=0, ii, jj, ns=0;
    if (is-d/2>=1) i1=is-d/2; else i1=1;
    if (js-d/2>=1) j1=js-d/2; else j1=1;
    if (is+d/2<=r) i2=is+d/2; else i2=r;
    if (js+d/2<=c) j2=js+d/2; else j2=c;
    mx=0;
    for (ii=i1; ii<=i2; ii++)
       {
        for (jj=j1; jj<=j2; jj++)
        {
            if (prim(M[ii][jj]) && (ii!=is || jj!=js))
            {
                ns++;
                if (M[ii][jj]>mx) mx=M[ii][jj];
            }
        }
       }
    return ns;
}

void seek(int M[][Cmax], int nr, int ii, int jj, int &i0, int &j0)
{
    for (int ir=1; ir<=ii; ir++)
        for (int ic=1; ic<=jj; ic++)
            if (M[ir][ic]==nr)
    {
        i0=ir;
        j0=ic;
        return;
    }
}

int main()
{
    //cout << "i_n_t_r_u_s" << endl;
    //cout<<"Rmax="<<Rmax<<" "<<"Cmax="<<Cmax<<endl;
    int p, R, C, D, S=0, t, i0, j0, si, oi;
    f>>p; //cout<<"p="<<p<<endl;
    f>>R>>C>>D;
    //cout<<"R="<<R<<" "<<"C="<<C<<" D="<<D<<endl;
    if (p==2)
    {
    for (si=1; si<=R; si++) for (oi=1; oi<=C; oi++) f>>X[si][oi];
    for (si=1; si<=R; si++)
        for (oi=1; oi<=C; oi++)
        {//cout<<si<<" "<<oi<<endl;
            if (X[si][oi]!=0)
            {
                W[X[si][oi]]=W[X[si][oi]]+1;
                t=W[X[si][oi]];
                if (t>=2)
                {
                    if (t==2)
                    {
                        seek(X, X[si][oi], R, C, i0, j0);
                        pt++;
                        Y[pt].r=i0; Y[pt].c=j0;
                        Y[pt].niv=nivel(X, i0, j0, R, C, D, Y[pt].maxpri);
                        pt++;
                        Y[pt].r=si; Y[pt].c=oi;
                        Y[pt].niv=nivel(X, si, oi, R, C, D, Y[pt].maxpri);
                    }
                    else
                    {
                        pt++;
                        Y[pt].r=si; Y[pt].c=oi;
                        Y[pt].niv=nivel(X, si, oi, R, C, D, Y[pt].maxpri);
                    }
                }
            }
        }
    for (si=1; si<pt; si++)
       for (oi=si+1; oi<=pt; oi++)
            if (Y[si].niv<=Y[oi].niv)
                {
                    if (Y[si].niv==Y[oi].niv)
                    {
                        if(Y[si].maxpri<=Y[oi].maxpri)
                        {
                            if (Y[si].maxpri<Y[oi].maxpri)
                            {
                                Temp=Y[si];
                                Y[si]=Y[oi];
                                Y[oi]=Temp;
                            }
                            else
                            if (Y[si].r>=Y[oi].r)
                            {
                                if (Y[si].r>Y[oi].r)
                                {
                                    Temp=Y[si];
                                    Y[si]=Y[oi];
                                    Y[oi]=Temp;
                                }
                                else
                                if (Y[si].c>Y[oi].c)
                                {
                                    Temp=Y[si];
                                    Y[si]=Y[oi];
                                    Y[oi]=Temp;
                                }
                            }
                        }

                    }
                    else
                    {
                        Temp=Y[si];
                        Y[si]=Y[oi];
                        Y[oi]=Temp;
                    }
                }
    if (pt>0) for (si=1; si<=pt; si++)
                    g<<X[Y[si].r][Y[si].c]<<" "<<Y[si].r<<" "<<Y[si].c<<endl;
    else g<<-1;
    }
    else//p==1
    {
        int mm=0;
        for (int i=1; i<=R; i++)
        for (int j=1; j<=C; j++)
        {
            f>>X[i][j];
            if (X[i][j]) {++W[X[i][j]]; if (X[i][j]>mm) mm=X[i][j];}
        }
        for (int i=1; i<=mm; i++) if (W[i]>1) S=S+W[i];
        g<<S;
    }
    f.close(); g.close();
    //cout<<"Total memory: "<<(sizeof(X)+sizeof(Y)+sizeof(W))/1024<<" KB.";
    return 0;
}
