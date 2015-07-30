#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

#define IN ".in"
#define OK ".ok"
#define DEF "grader_test"
#define itos IntToStr

string name;
long start,cnt,i,ccnt,result;

string IntToStr(long val){
    if(val==0) return "0";

    string dest;
    long cf=0,nr=0;
    while(val){
        cf++;
        nr = nr*10 + val%10;
        val /=10;
    }
    dest.clear();
    for(;cf;cf--){
        dest += nr%10 + '0';
        nr /= 10;
    }

    return dest;
}

int main()
{
    cout << "Name : "; cin >> name;
    cout << "Start : "; cin >> start;
    cout << "Cnt : "; cin >> cnt; ccnt=cnt;
    cout << "----------------------------------\n";

    for(i=start;cnt;i++,cnt--){
        string f1 = itos(i) + "-" + name + IN;
        string f2 = DEF + itos(i-start+1) + IN;

        result = rename(f1.c_str(),f2.c_str());
        cout << "Rename : " + f1 << "  ->  " << f2 << (result?" | Not found! ":" | Ok! ") <<'\n';
    }

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    for(i=start,cnt=ccnt;cnt;i++,cnt--){
        string f1 = itos(i) + "-" + name + OK;
        string f2 = DEF + itos(i-start+1) + OK;

        result = rename(f1.c_str(),f2.c_str());
        cout << "Rename : " + f1 << "  ->  " << f2 << (result?" | Not found! ":" | Ok! ") <<'\n';
    }

    cin>> start;

    return 0;
}
