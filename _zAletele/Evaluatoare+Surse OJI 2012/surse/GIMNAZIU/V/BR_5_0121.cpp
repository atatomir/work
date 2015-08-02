#include <fstream>
using namespace std;
ifstream fin("bete.in");
ofstream fout("bete.out");
long N,N1,N2,x,i,K,L,P;
int main()
{
    //punctul a
    fin>>N;
    fin>>N1;
    fin>>N2;
    fin>>L;
    fin>>K;
    fin>>P;
    for(i=1;i<N1;i++)
    L=i+x;
    //punctul b
    for(x=i;x>=N2;x++)
    K=i+x;
    //punctul c
    if(P=K)
    P=P+1;
    fout<<L;
    fout<<K;
    fout<<P;
    fin.close();
    fout.close();
    return 0;
}
