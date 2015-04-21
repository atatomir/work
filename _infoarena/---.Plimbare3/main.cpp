#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Buffer{
    public:
        long maxBuf,pos;
        vector<char> Buff;

        Buffer(char fileName[],long buffSize){
            freopen(fileName,"r",stdin);
            maxBuf = buffSize; Buff.resize(maxBuf);
            reFill();
        }

        Buffer& operator>>(long &dest){
            while(!isDigit(Buff[pos])){
                pos++;
                if(pos == maxBuf) reFill();
            }
            dest = 0;
            while(isDigit(Buff[pos])){
                dest = dest*10 + Buff[pos++] - '0';
                if(pos == maxBuf) reFill();
            }
            return *this;
        }

    private:
        bool isDigit(char c){
            return c >= '0' & c <= '9';
        }
        void reFill(){
            fread(&Buff[0],1,maxBuf,stdin); pos = 0;
        }
};

#define maxN 200033
#define itt vector<long>::iterator
#define myIterator(nodee) vector<long>::iterator it=list[(nodee)].begin();it!=list[(nodee)].end();it++
#define cin fin

long n,i,act;
vector<long> list[maxN];
pair<long,long> G[maxN];

bool us[maxN];
long A[maxN],B[maxN],C[maxN],D[maxN],Dad[maxN];
vector<long> indA[maxN],indB[maxN];
bool diff[maxN];

bool cmpA(long a ,long b){
    static long son1,son2;
    son1 = list[act][a];
    son2 = list[act][b];

    return A[son1] > A[son2];
}

bool cmpB(long a ,long b){
    static long son1,son2;
    son1 = list[act][a];
    son2 = list[act][b];

    return B[son1] > B[son2];
}

long getFirstA(long Dad,long Son){
    if(list[Dad][ indA[Dad][0] ] == Son){
        if(list[Dad].size()==1) return -1;
        return list[Dad][ indA[Dad][1] ];
    } else
    return list[Dad][ indA[Dad][0] ];
}

long getFirstADuo(long Dad,long Son,long _Son){
    if(list[Dad][ indA[Dad][0] ] == Son || list[Dad][ indA[Dad][0] ] == _Son){
        if(list[Dad].size()==1) return -1;
        if(list[Dad][ indA[Dad][1] ] == Son || list[Dad][ indA[Dad][1] ] == _Son){
            if(list[Dad].size()==2) return -1;
            return list[Dad][ indA[Dad][2] ];
        }
    } else
    return list[Dad][ indA[Dad][0] ];
}

long getFirstB(long Dad,long Son){
    if(list[Dad][ indB[Dad][0] ] == Son){
        if(list[Dad].size()==1) return -1;
        return list[Dad][ indB[Dad][1] ];
    } else
    return list[Dad][ indB[Dad][0] ];
}

void Organise(long node){
    us[node]=true;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];

        if(us[newNode]){
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back(); Dad[node] = newNode;
            i--;
        } else {
            Organise(newNode);
        }
    }
}

void Dfs_A(long node){
    if(list[node].size()==0){A[node]=0; return;}

    long ans=-1;
    for( myIterator(node) )  {Dfs_A(*it); ans = max(ans,A[*it]);}
    A[node] = ans+1;

    //! Sortam elementele
    indA[node].resize(list[node].size());
    for(long i=0;i<indA[node].size();i++) indA[node][i] = i;
    act = node;
    sort(indA[node].begin(),indA[node].end(),cmpA);
}

void Dfs_B(long node){
    if(list[node].size()==0){B[node]=0; return;}

    long ans = -1;
    for( myIterator(node) ) {Dfs_B(*it); ans = max(ans,B[*it]);}
    if(indA[node].size()>=1) ans = max(ans,A[list[node][indA[node][0]] ]+1);
    if(indA[node].size()>=2) ans = max(ans,2 + A[ list[node][indA[node][0]] ] + A[ list[node][indA[node][1] ]] );
    B[node]=ans;

    //! Sortam elementele
    indB[node].resize(list[node].size());
    for(long i=0;i<indB[node].size();i++) indB[node][i] = i;
    act = node;
    sort(indB[node].begin(),indB[node].end(),cmpB);
}

void Dfs_C(long node){
    if(node==1) {D[1]=0; for( myIterator(node) ) Dfs_C(*it); return;}

    long ans = C[Dad[node]] + 1;
    long id = getFirstA(Dad[node],node);
    if(id!=-1) ans = max(ans,2 + A[id]);
    C[node] = ans;

    for( myIterator(node) ) Dfs_C(*it);
}

void Dfs_D(long node){
    if(node==1) {D[1]=0; for( myIterator(node) ) Dfs_D(*it); return;}

    long ans = D[Dad[node]];
    long idA1 = getFirstA(Dad[node],node);
    long idA2 = getFirstADuo(Dad[node],node,idA1);
    long idB  = getFirstB(Dad[node],node);

    if(idA1 != -1) ans = max(ans,C[Dad[node]] + A[idA1] + 1);
    if(idB  != -1) ans = max(ans,B[idB]);
    if(idA2 != -1) ans = max(ans,2 + A[idA1] + A[idA2] );

    if(C[node] > ans){
        diff[node] = true;
        ans = C[node];
    }

    D[node] = ans;

    for( myIterator(node) ) Dfs_D(*it);
}

int main()
{
    Buffer cin("plimbare3.in",1014*1024);
    freopen("plimbare3.out","w",stdout);

    cin >> n;
    for(i=1;i<n;i++){
        cin >> G[i].first >> G[i].second;
        list[G[i].first].push_back(G[i].second);
        list[G[i].second].push_back(G[i].first);
    }

    Organise(1);
    Dfs_A(1);
    Dfs_B(1);
    Dfs_C(1);
    Dfs_D(1);

    for(i=1;i<n;i++){
        long from = G[i].first;
        long to   = G[i].second;

        if(Dad[from]==to) swap(from,to);
        if(diff[to]) printf("%ld\n",B[to] + D[to]);
        else         printf("%ld\n",B[to] + D[to] + 1);
    }

    return 0;
}
