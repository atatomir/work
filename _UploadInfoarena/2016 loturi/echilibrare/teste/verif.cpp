#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
ifstream fin("echilibrare.in");
ifstream fok("echilibrare.ok");
ifstream fout("echilibrare.out");
void Msg(int pct, string msg )
{
    cout << pct << ' ' << msg;
    try
    {
        fin.close();
        fok.close();
        fout.close();
    }
    catch (string ex) {}
    exit(0);
}
int m,M,n,N,sum,a[101][101],b[101][101],i,j;
int main()
{
    if ( !fout )
        Msg(0, "Nu exista fisierul echilibrare.out!");
	fok>>M;
	if(!(fout>>m))
        Msg(0, "Fisier de iesire incorect!");
    if(m!=M)
        Msg(0, "Incorect!");
    fin>>n;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            fin>>a[i][j];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(!(fout>>b[i][j]))
                Msg(0, "Matrice incompleta!");
            if(a[i][j]>b[i][j])
                Msg(0, "Eroare in matrice!");
            sum+=b[i][j];
        }
    if(sum!=M)
        Msg(0, "Matrice incorecta!");
    for(i=1;i<n;i++)
        for(j=1;j<n;j++)
            if(b[i][j]+b[i-1][j-1]!=b[i][j-1]+b[i-1][j])
                Msg(2, "Matrice neechilibrata!");
    Msg(7,"Corect!!!");
	return 0;
}
