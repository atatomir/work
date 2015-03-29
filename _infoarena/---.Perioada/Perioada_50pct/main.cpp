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

        char getChar(){
            while(Buff[pos]<'a' || Buff[pos]>'z'){
                pos++;
                if(pos == maxBuf) reFill();
            }
            char ans = Buff[pos++];
            if(pos == maxBuf) reFill();
            return ans;
        }

    private:
        bool isDigit(char c){
            return c >= '0' & c <= '9';
        }
        void reFill(){
            fread(&Buff[0],1,maxBuf,stdin); pos = 0;
        }
};

struct query{
    long to,id;
};
query mp(long _to,long _id){
    query ans;
    ans.to=_to; ans.id=_id;
    return ans;
}
bool cmp(const query& a,const query& b){return a.to<b.to;}

#define cin fin
#define maxN 100011
#define pb push_back
#define itt vector<query>::iterator

long n,m,i;
char s[maxN];
vector<query> Q[maxN];
vector<query> qTemp;

long ans[maxN],pr[maxN],how[maxN],still[maxN];
bool usedL[maxN],usedR[maxN];
long c1,c2;

void make_pr(long l,long r){
    long q=0; pr[l] = 0;
    for(long i=l+1;i<=r;i++){
        while(q && s[i]!=s[l+q]) q = pr[l-1+q];
        if(s[i]==s[l+q]) q++;
        pr[i]=q;
    }
}

void make_how(){
    long i,j;
    for(i=1;i<=n;i++) how[i]=1,still[i]=i;;

    for(i=2;i<=n;i++){
        if(how[i]!=1) continue;
        how[i] = 2;
        for(j=2*i;j<=n;j++){
            long cnt = 0;
            while(still[j]%i==0) {still[j]/=i; cnt++;}
            how[j] *= cnt+1;
        }
    }
}

int main()
{
    Buffer cin("perioada.in",1024*1024);
    freopen("perioada.out","w",stdout);

    cin >> n ;
    for(i=1;i<=n;i++) s[i] = cin.getChar();
    cin >> m ; qTemp.resize(m);
    for(i=0;i<m;i++) {
        cin >> qTemp[i].to >> qTemp[i].id; //! retin query
        if(usedL[qTemp[i].to]==false) c1++;
        if(usedR[qTemp[i].id]==false) c2++;

        usedL[qTemp[i].to]=usedR[qTemp[i].id]=true;
    }

    make_how();

    for(i=0;i<m;i++){
        if(c1 <= c2){
            Q[qTemp[i].to].pb(mp(qTemp[i].id,i+1));
        } else {
            Q[qTemp[i].id].pb(mp(qTemp[i].to,i+1));
        }
    }

    for(i=1;i<=n;i++){
        if(Q[i].empty()) continue;
        sort(Q[i].begin(),Q[i].end(),cmp);
        make_pr(i,Q[i][Q[i].size()-1].to);

        for(itt it=Q[i].begin();it!=Q[i].end();it++){
            long aPr = pr[(*it).to];
            long lung = (*it).to-i+1;

            if(lung%(lung-aPr)==0 && aPr>0){
                ans[(*it).id] = how[lung/(lung-aPr)]-1;
            } else {
                ans[(*it).id] = 0;
            }
        }
    }

    for(i=1;i<=m;i++) printf("%ld\n",ans[i]);

    return 0;
}
