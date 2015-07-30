#include <iostream>
#include <queue>

using namespace std;


struct package{
    long long q,k,pos;
} m[100005];

struct heapElem{
    long pos;
    long long val;
};

struct compare {
    bool operator()(const heapElem& a,const heapElem& b) {
        return a.val < b.val;
    }
};

/////////////////////////////////////////////////////////////

long x,n,i,target,v,pos;
priority_queue<heapElem,vector<heapElem>,compare> h;
long long rez,put;
heapElem e;
int iesi;
long sol[100005];


////////////////////////////////////////////////////////////


void QSort(long l,long h) {
    long i=l,j=h,x=m[(i+j)/2].k;
    package y;
    do {
        while (m[i].k < x) i++;
        while (m[j].k > x) j--;
        if (i <= j) {
            y = m[i]; m[i] = m[j]; m[j] = y;
            i++; j--;
        }
    }   while(i<=j);
    if (l < j) QSort(l,j);
    if (i < h) QSort(i,h);
}

void heapClear() {
    h = priority_queue<heapElem,vector<heapElem>,compare>();
}

int main()
{
    while(!cin.eof()) {
        cin >> x >> n;
        if (cin.eof()) return 0;
        for(i=1;i<=n;i++) {
            cin >> m[i].k >> m[i].q;
            m[i].pos = i;
        }
        QSort(1,n); m[n+1].k = -1;
        heapClear();

        rez = 0; target = 0; put = 1; pos = 1; sol[0] = 0;

        while(x > 0) {
            v = x % 10; x /= 10;

            while(m[pos].k == target) {
                e.pos = m[pos].pos;
                e.val = put * m[pos].q;
                h.push(e);
                pos++;
            }

            iesi = 0;
            while (rez/put < v) {
                if (h.empty()) {
                    iesi = true;
                    break;
                }
                rez += h.top().val;
                sol[++sol[0]] = h.top().pos;
                h.pop();
            }

            if (iesi) break;

            rez -= put*v;

            target++; put *= 10;
        }

        if (iesi)
            cout << -1 << '\n';
        else {
            cout << sol[0] << '\n';
            for(i=1;i<=sol[0];i++) cout << sol[i] << ' ';
            cout << '\n';
        }

    }


    return 0;
}
