#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN (1<<20)

class Buffer{
    public:
        Buffer(string name,int _dim){
            freopen(name.c_str(),"r",stdin);
            dim = _dim; data.resize(dim);
            reFill();
        }
        Buffer& operator>>(int &dest){
            while (!isDigit(data[pos])){
                if(++pos==dim) reFill();
            }
            dest = 0;
            while (isDigit(data[pos])){
                dest = dest*10 + data[pos]-'0';
                if(++pos==dim) reFill();
            }
            return *this;
        }

    private:
        int dim,pos;
        vector<char> data;

        void reFill(){
            memset(&data[0],0,dim); pos = 0;
            fread(&data[0],1,dim,stdin);
        }
        bool isDigit(char c){
            return ('0'<=c)&&(c<='9');
        }
};

class Stack{
    public:
        void init(pair<int,int> *_data){
            n = 0;
            data = _data;
        }
        int operator<<(pair<int,int> Elem){
            while (n>0) {
                auto act = data[n];
                if (Elem.second < act.second) break;
                n--;
            }

            data[++n] = Elem;
            if (n==1) return 1;
            return data[n-1].first;
        }
        int Find(int val){
            int l = 1,r=n,mid;

            if (n==0) return 1;
            if (val >= data[1].second) return 1;

            while (l<=r){
                mid = (l+r)>>1;
                if ( val >= data[mid].second )
                    r = mid-1;
                else
                    l = mid+1;
            }

            return data[r].first;
        }

    private:
        int n;
        pair<int,int> *data;
        //! first - pos
        //! second - val
};

int n,i;
int v[maxN];
Stack S;
vector<int> whoDepends[maxN];
long long allView;
int canSee[maxN];
long long finalAnswer;
pair<int,int> __data[maxN];

int main()
{
    Buffer fin("turnuri.in",1<<20);
    freopen("turnuri.out","w",stdout);

    fin >> n;
    for (i=1;i<=n;i++) fin >> v[i];

    S.init(__data);
    for (i=1;i<=n;i++){
        int id = (S<< mp(i,v[i]) );

        if (i!=1) whoDepends[id].pb( i );
        allView += 1LL*( i-id );
        canSee[i] = i-id;
    }

    S.init(__data);
    for (i=1;i<=n;i++){
        long long ans = allView-canSee[i];
        for (auto elem:whoDepends[i]){
            ans += i - S.Find( v[elem] );
        }

        finalAnswer += ans;

        S<< mp(i,v[i]);
    }

    printf("%lld",finalAnswer-allView);

    return 0;
}
