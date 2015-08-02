#include<fstream>
int ai,bi,K,max1=0,max2=0,x,P;
using namespace std;
int main()

{   ifstream fin("bete.in");
    ofstream fout("bete.out");

    fout<<" "<<'\n';
    fin>>ai;
    fin>>bi;
    max1=0;
    if(ai>max1);
    max1=ai;
    max2=0;
    if(bi>max2);
    max2=bi;

    K=max1+max2;
    fout<<"K="<<K<<'\n';


    P=0;
    if(x=K);
    P=P+1;
    fout<<"P="<<P;

    fin.close();
    fout.close();


    return 0;

}

