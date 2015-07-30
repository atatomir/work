#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

class Buffer{
    private:
        vector<char> C;
        long maxBuf,pos;

        void reLoad(){
            fread(&C[0],1,maxBuf,stdin);
            pos=0;
        }
        inline bool isDigit(char c){
            return (c>='0')&&(c<='9');
        }

    public:
        Buffer(char name[],long dim){
            freopen(name,"r",stdin);
            C.resize(dim); maxBuf=dim;
            reLoad();
        }
        Buffer& operator>>(long & ans){
            while( !isDigit(C[pos]) ){
                if(++pos == maxBuf) reLoad();
            }
            ans=0;
            while( isDigit(C[pos]) ){
                ans = ans*10 + C[pos] - '0';
                if(++pos == maxBuf) reLoad();
            }
            return *this;
        }

};

#define maxN 1024
#define PI pair< long , pair<long,long> >
#define val first
#define from second.first
#define to second.second

vector<PI> Edge;
struct cmp{
    bool operator()(long& a,long& b){
      return Edge[a].val < Edge[b].val;
    }
};

long t,n,i,j,x;
vector< pair<long,long> > m[maxN];
priority_queue< long,vector<long>,cmp > H;

long gr[maxN];
vector<PI> ans;
vector<long> vv;

PI mpp(long x,long f,long t){
  return make_pair( x , make_pair(f,t) );
}

void addAll(long node){
  for(long i=0;i<m[node].size();i++){
      pair<long,long> act = m[node][i];

      if(node==act.first || gr[act.first]) {
          m[node][i] = m[node][ m[node].size()-1 ];
          m[node].pop_back();
          i--; continue;
      }

      Edge.push_back(mpp( act.second , node,act.first ));
      H.push(Edge.size()-1);
  }
}

int main()
{
    Buffer fin("copsamica.in",1<<20);
    freopen("copsamica.out","w",stdout);

    fin >> t;
    for(;t--;){
        fin >> n;

        //! init

        while(!H.empty()) H.pop();
        memset(gr,0,sizeof(gr));
        ans.clear(); vv.clear();
        for(i=1;i<=n;i++) m[i].clear();
        Edge.clear();

        //!!

        for(i=1;i<n;i++){
          for(j=i+1;j<=n;j++){
            fin >> x;
            m[i].push_back(make_pair(j,x));
            m[j].push_back(make_pair(i,x));
          }
        }


        addAll(1);
        while(!H.empty()){
            PI act = Edge[H.top()]; H.pop();
            if(gr[act.from]==2 || gr[act.to]) continue;

            gr[act.from]++;
            gr[act.to]++;
            ans.push_back(act);
            addAll(act.to);
        }

        for(i=1;i<=n;i++){
            if(gr[i]==1) vv.push_back(i);
        }
        ans.push_back(mpp(0,vv[0],vv[1]));

        for(i=0;i<ans.size();i++) printf("%ld %ld %ld\n",ans[i].from,ans[i].to,ans[i].val);
    }


    return 0;
}
