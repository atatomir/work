///prof. Gorea Claudiu-Cristian
///Colegiul National Al. Papiu Ilarian Tg-Mures
#include <fstream>

using namespace std;
ifstream fin ("casa.in");
ofstream fout("casa.out");

struct casa
{
    int x,y;
}coada[100002];



int dx[4]={ 0,-1,+1, 0};
int dy[4]={+1, 0, 0,-1};

int caz,t,leg,lin,col,lmax,cmax,i,j,n,m,st,dr,k;
char c;

int main()
{

    fin>>caz;


    if (caz==1)
    {
        fin>>t;
        coada[1].x=coada[1].y=1;
        lmax=1;
        cmax=1;

        for(i=2;i<=t;i++)
        {
            fin>>leg>>c;
            lin=coada[leg].x;
            col=coada[leg].y;
            if (c=='E') col++;
            if (c=='V') col--;
            if (c=='N') lin--;
            if (c=='S') lin++;
            coada[i].x=lin;
            coada[i].y=col;
           // a[lin][col]=1;
            if (lin>lmax) lmax=lin;
            if (col>cmax) cmax=col;
        }
        fout<<lmax<<" "<<cmax<<endl;


        bool a[lmax+2][cmax+2];
        ///initializare
        for(i=1;i<=lmax;i++)
            for(j=1;j<=cmax;j++)
                a[i][j]=0;
        ///copiere din coada
        a[1][1]=1;
        for(i=2;i<=t;i++) a[coada[i].x][coada[i].y]=1;

        ///afisare
        for(i=1;i<=lmax;i++)
        {
            for(j=1;j<cmax;j++)
                fout<<a[i][j]<<" ";
            fout<<a[i][j]<<endl;  ///ultimul de pe linie
        }
    }


    if (caz==2)
    {
        fin>>n>>m;
        bool a[n+2][m+2];  ///definire locala de matrice

        ///initializare bordura
        for(i=0;i<=n+1;i++)  a[i][0]=a[i][m+1]=0;
        for(j=1;j<=m+1;j++)  a[0][j]=a[n+1][j]=0;

        ///prelucrare
        t=0;
        lmax=0;
        cmax=0;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                fin>>a[i][j];
                t+=a[i][j];
                if ((lmax+cmax==0) && (a[i][j]==1)) lmax=i,cmax=j;
            }
        fout<<t<<" "<<cmax<<"\n";

        st=dr=1;
        coada[1].x=lmax;
        coada[1].y=cmax;
        a[lmax][cmax]=0;
        while(st<=dr)
        {
             // st - nr camerei vecina
            lmax=coada[st].x;
            cmax=coada[st].y;
            for(k=0;k<4;k++)
                if (a[lmax+dx[k]][cmax+dy[k]]==1)
                {
                    fout<<st;
                    if (k==0) fout<<" E\n";
                    if (k==1) fout<<" N\n";
                    if (k==2) fout<<" S\n";
                    if (k==3) fout<<" V\n";
                    a[lmax+dx[k]][cmax+dy[k]]=0;
                    dr++;
                    coada[dr].x=lmax+dx[k];
                    coada[dr].y=cmax+dy[k];
                }
            st++;
        }

    }


    return 0;
}
