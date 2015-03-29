#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

#define cin fin
#define cout fout

#define inf 1000000000

long a,b,v,i,j,n;
long c[105][105];

int main()
{
    cin >> n;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            cin >> c[i][j];
            if(i != j && c[i][j] == 0) c[i][j] = inf;
        }
    }

    for(v=1;v<=n;v++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(c[i][v] && c[v][j] && c[i][j] > c[i][v] + c[v][j])
                    c[i][j] = c[i][v] + c[v][j];


    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++) cout << c[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
