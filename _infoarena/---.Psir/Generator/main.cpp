#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int n,i,lim;

int main()
{
    ofstream fout("psir.in");
    ifstream fin("data.in");
    srand(time(NULL));

    cerr << "n = "; fin >> n;
    cerr << "lim = "; fin >> lim;
    cerr << "Generating...\n";

    fout << n << '\n';
    for (i=1;i<=n;i++) fout << rand()%lim+1 << ' ';

    return 0;
}
