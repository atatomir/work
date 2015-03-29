#include <fstream>
#include <queue>

using namespace std;

long n,p,i,a[100005],minim,last;
long long sum=0;

struct heapElem{
    long id,cid;
    long long time;
    heapElem operator()(long lid,long lcid,long long ltime) {
        id = lid; cid=lcid; time = ltime;
        return *this;
    }
} elem;


struct compare {
    bool operator()(const heapElem& a,const heapElem& b){
        if(a.time != b.time)
            return a.time > b.time;
        else
            return a.cid > b.cid;
    }
};

priority_queue<heapElem,vector<heapElem>,compare> h;

int main()
{
    ifstream fin("roata.in");
    ofstream fout("roata.out");

    fin >> n >> p ;
    for(i=1;i<=p;i++) {
        fin >> a[i];
        sum += 1LL*a[i];
    }
    fout << sum << '\n';

    minim = n; if (minim > p) minim = p;
    for(i=1;i<=minim;i++){
        h.push(elem(i,i,a[i]));
    }

    for(i=minim+1;!h.empty();i++){
        elem = h.top(); h.pop();
        fout << elem.id << ' ';
        last = elem.cid;

        if(i <= p) {
            h.push(elem(i,last,elem.time+a[i]));
        }
    }

    fout << '\n' << last << '\n';

    fin.close();
    fout.close();
    return 0;
}
