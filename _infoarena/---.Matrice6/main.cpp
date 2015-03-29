#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#define mod 666013;

using namespace std;

ifstream fin("matrice6.in");
ofstream fout("matrice6.out");

long n,i,v[7],nrc,j,curent;
map<vector<int>,int> M;
vector<int> aux;
vector<int> conf[100]; // 81 sunt utilizati
long long sol[100][100],ans[100][100],rezultat,m;

void down(int pas){
    if(pas > n){
        aux.clear();
        for(int i=1;i<=n;i++) aux.push_back(v[i]);
        if(M[aux] == 0){
            nrc++;
            for(int i=0;i<n;i++) conf[nrc].push_back(aux[i]);
            M[aux] = nrc;
        }
    } else {
        v[pas] = v[pas-1];
        down(pas+1);
        v[pas] = v[pas-1]-1;
        if(v[pas] >= 0)down(pas+1);
        v[pas] = v[pas-1]+1;
        down(pas+1);
    }
}

void up(int pas){
    if(pas <= 0){
        down(i+1);
    } else {
        v[pas] = v[pas+1];
        up(pas-1);
        v[pas] = v[pas+1]-1;
        if(v[pas]>= 0) up(pas-1);
        v[pas] = v[pas+1]+1;
        up(pas-1);
    }
}

void Back(int pas){
    if(pas >= n){
        int minim = 100;
        for(int i =0;i<n;i++) minim = min(minim,aux[i]);
        for(int i =0;i<n;i++) aux[i] -= minim;

        long h = M[aux];
        if(h){
            sol[curent][h] ++; sol[curent][h] %= mod;
        }
    } else {
        Back(pas+1);

        aux[pas] += 1;
        Back(pas+1);
        aux[pas] -= 1;

        aux[pas] -= 1;
        Back(pas+1);
        aux[pas] += 1;
    }
}

inline void multiplicate(long long a[100][100],long long b[100][100]) {
    static long long aux[100][100];
    for(int i=1;i<=nrc;i++)
        for(int j=1;j<=nrc;j++) aux[i][j] = 0;

    for(int i=1;i<=nrc;i++){
        for(int j=1;j<=nrc;j++){
            for(int dim=1;dim<=nrc;dim++) aux[i][j] = (aux[i][j] + a[i][dim]*b[dim][j])% mod;
        }
    }
    for(int i=1;i<=nrc;i++){
        for(int j=1;j<=nrc;j++){
           a[i][j] = aux[i][j];
        }
    }
}

int main()
{
    fin >> n >> m;

    for(i=1;i<=n;i++) v[i] = 0,up(i-1);

    if(m==1){
        fout << nrc;
        fin.close();
        fout.close();
        return 0;
    }

    for(i=1;i<=nrc;i++){
        curent = i;
        aux.clear();
        for(j=0;j<n;j++) aux.push_back(conf[i][j]);
        Back(0);
    }

    for(i=1;i<=nrc;i++) ans[i][i] = 1;

    m--;
    while(m){
        if(m&1){
            multiplicate(ans,sol);
        }
        multiplicate(sol,sol);
        m >>= 1;
    }

    rezultat = 0;
    for(i=1;i<=nrc;i++)
        for(j=1;j<=nrc;j++){
                rezultat = (rezultat + ans[i][j])% mod;
            }

    fout << rezultat << '\n';

    /*for(i=1;i<=nrc;i++)
        for(j=1;j<=nrc;j++) fout << ans[i][j] << ' ';*/

    fin.close();
    fout.close();
    return 0;
}
