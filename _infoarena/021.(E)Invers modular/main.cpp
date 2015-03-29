#include <fstream>

using namespace std;

long long a,x,p,phi;

    ifstream fin("inversmodular.in");
    ofstream fout("inversmodular.out");

inline long long getPhi(long long x){
    long long curr=x,i;
    for(i=2;i*i<=x;i++){
        if(x % i == 0){
            while(x % i == 0) x /= i;
            curr = (curr /i)*(i-1);
        }
    }
    if(x != 1) curr = (curr/x)*(x-1);
    return curr;
}

int main()
{
    fin >> a >> p;

    phi = getPhi(p)-1;

    x=1;
    while(phi > 0){
        if(phi & 1) x = (x*a)% p;
        a = (a*a)% p;
        phi >>=1;
    }

    fout << x;

    fin.close();
    fout.close();
    return 0;
}
