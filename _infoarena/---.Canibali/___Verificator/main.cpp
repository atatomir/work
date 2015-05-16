#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

string conv(long n){
    string ans="";
    long pow=1,nn=n;
    while(n){
        n/=10;
        pow*=10;
    }pow/=10; n=nn;
    while(pow){
        ans = ans + (char)((n/pow)%(pow*10)+'0');
        pow/=10;
    }
    return ans;
}

bool Verif(){
    long n,i,nn;

    time_t t = clock();
    system("canibali.exe");
    time_t t2 = clock();
    long dT = difftime(t,t2);
    cout << "Time: " << -dT << "ms - ";

    ifstream fout("canibali.out");
    ifstream fok("canibali.ok");

    fout >> n;
    fok >> nn;
    if(n!=nn){
        cout << "Gresit " << n << " != " << nn;
        cin >> n;
        return 0;
    }
    cout << "Good !";

    fout.close();
    fok.close();
    return 1;
}

int main()
{
    string dfileIn="-canibali.in";
    string dfileOk="-canibali.ok";
    string fileIn;
    string fileOk;
    for(int test=1;test<=20;test++){
        string str = conv(test);
        fileIn = str+dfileIn;
        fileOk = str+dfileOk;
        long n,i,x,y,z,t;

            ifstream sour(fileIn.c_str());
            ofstream dest("canibali.in");

            sour >> n; dest << n << '\n';
            for(i=1;i<=n;i++){
                sour >> x >> y >> z >> t;
                dest << x << ' ' << y << ' ' << z << ' ' << t << '\n';
            }

            sour.close(); dest.close();

            sour.open(fileOk.c_str());
            dest.open("canibali.ok");
            sour >> n; dest << n;
            sour.close();dest.close();

            cout << "Test " << str << " | ";
            Verif();
            cout << '\n';
    }

    long n;
    cin >> n;

    return 0;
}
