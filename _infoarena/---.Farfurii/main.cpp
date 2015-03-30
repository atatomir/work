#include <iostream>
#include <fstream>

using namespace std;

long long n,k,i,m;

int main()
{
    ifstream fin("farfurii.in");
    ofstream fout("farfurii.out");

    fin >> n >> k;

    m = 1;
    while(m*(m-1)<2*k) m++;

    k = (m*(m-1)/2)-k; k = n-k;
    for(i=1;i<=n-m;i++) fout << i << ' ';
    fout << k << ' ';
    for(i=n;i>n-m;i--)
        if(i!=k) fout<< i << ' ';

    return 0;
}
