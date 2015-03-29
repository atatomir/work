#include <iostream>
#include <fstream>

using namespace std;

#define cSec 86400

ifstream fin("momente.in");
ofstream fout("momente.out");

long cPal[cSec];
int sPal[10];
long luna[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
long t,ti;
long l,z,h,m,s,mom1,mom2,day1,day2,ans;


int isPal(long x){
    long h,m,s,pos=0,i;
    h = x / 3600; x %= 3600;
    m = x /   60; x %=   60;
    s = x;

    x = 10000*h + 100*m + s;
    while(x){
        sPal[++pos] = x % 10;
        x /= 10;
    }
    i=1;
    while(i < pos){
        if(sPal[i] != sPal[pos]) return 0;
        i++; pos--;
    }
    return 1;
}

void preCalc(){
    long i;
    cPal[0] = 1;
    for(long i=1;i<cSec;i++){
        cPal[i] = cPal[i-1] + isPal(i);
    }

    for(i=2;i<=12;i++) luna[i] += luna[i-1];
}

int main()
{
    preCalc();

    fin >> t;
    for(ti=1;ti<=t;ti++){
        fin >> l >> z >> h >> m >> s;
        day1 = luna[l-1] + z;
        mom1 =  h*3600 + m*60 + s;

        fin >> l >> z >> h >> m >> s;
        day2 = luna[l-1] + z;
        mom2 = h*3600 + m*60 + s;

        ans = cPal[cSec-1] * (day2-1-day1);
        ans += cPal[cSec-1] - cPal[mom1-1];
        ans += cPal[mom2];

        fout << ans << '\n';
    }

    return 0;
}
