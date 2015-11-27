#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>

using namespace std;

#define maxQ 2000010
#define corr first.first
#define inco first.second
#define ques second
typedef pair<pair<long,long>,long> Query;

long n,i,t,h;
Query q[maxQ];
long maxH;
char c,s[10];

time_t fTime,lTime;
long secs,loc;

int main()
{
    cout << "In fisierul in care se afla acest exe e necesar sa existe:\n1. input-ul sub numele input.txt\n2. executabilul Question.exe\nTe rog sa astepti evaluarea...\n\n";

    // citire date
    ifstream input("input.txt");
    input >> n >> t;
    for(i=1;i<=t;i++) input >> q[i].corr >> q[i].inco >> q[i].ques;
    input.close();

    // creare fisier input pt A
    ofstream fout("question.in");
    fout << "1\n";
    fout << n << " " << t << '\n';
    for(i=1;i<=t;i++) fout << q[i].corr << ' ' << q[i].inco << '\n';
    fout.close();

    time(&fTime);
    system("Question.exe");
    time(&lTime);
    secs += difftime(fTime,lTime);

    // creare fisier input pt B
    ifstream fin("question.out");
    fout.open("question.in");
    fout << "2\n";
    fout << n << ' ' << t << '\n';
    for(i=1;i<=t;i++){
        fin >> h; maxH = max(maxH,h);
        fout << q[i].ques << ' ' << h << '\n';
    }
    fin.close();
    fout.close();

    time(&fTime);
    system("Question.exe");
    time(&lTime);
    secs += difftime(fTime,lTime);

    //verificare raspunsuri
    fin.open("question.out");
    cout << "maxH = " << maxH << '\n';
    for(i=1;i<=t;i++){
        if(q[i].corr == q[i].ques) c = 'Y'; else c = 'N';
        fin.getline(s,sizeof(s));
        if(s[0] != c){
            cout << "GRESIT!\n" ;
            fin.close();
            cin >> c;
            return 0;
        }
    }
    fin.close();

    cout << "Time : " << -secs << " seconds "<<'\n';
    cout << "CORECT\n";
    cin >> c;

    return 0;
}
