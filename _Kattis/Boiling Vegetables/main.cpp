#include <iostream>
#include <queue>

using namespace std;

#define val first
#define cuts second
#define mp make_pair

typedef pair<long,long> Vegetable;

struct cmp{
    bool operator()(const Vegetable& a,const Vegetable& b){
        return a.val * b.cuts < b.val * a.cuts;
    }
};

long n,i,x;
double T;
priority_queue<Vegetable,vector<Vegetable>,cmp> H;
long cont;
bool need;
Vegetable v;
double minim = 1000000000;

int main()
{
    cin >> T >> n;
    for(i=1;i<=n;i++){
        cin >> x;
        if(x < minim) minim = x;
        H.push(mp(x,1));
    }

    need = true;
    while(need){
        v = H.top();
        if(minim/(v.val / v.cuts) >= T) {need = false;break;}

        H.pop();
        v.cuts++; cont++;
        if(minim > v.val/v.cuts) minim = v.val/v.cuts;
        H.push(v);
    }

    cout << cont;

    return 0;
}
