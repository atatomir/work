#include <iostream>
#include <vector>
#include <bitset>
#include <cstring>

using namespace std;

#define maxCiur 1011
#define maxT 111
#define maxCont 55

class bNumber{
    private:
        long C[maxCont];
        long pos;

    public:
        void init(){
            memset(C,0,sizeof(C));
            C[1] = 1; pos = 1;
        }
        void shl(){
            for(long i=1;i<=pos;i++){
                C[i]<<=1;
            }
            for(long i=1;i<=pos;i++){
                C[i+1] += C[i]/10; C[i] %= 10;
            }
            if(C[pos+1]) pos++;
        }
        void dec(){
            C[1] -= 1;
            for(long i=1;i<=pos;i++){
                if(C[pos]>=0) break;
                C[pos] += 10; C[pos+1]--;
            }
            while(C[pos]==0&&pos>1) pos--;
        }
        void write(){
            for(long i=pos;i;i--) cout << C[i];
        }
};

long t,n,i,j,x,cnt;
bool Ciur[maxCiur+10];
vector<long> prm;

bitset<maxT> eq[maxT],tmp;
long usedTo;

void make_ciur(){
    for(long i=2;prm.size()<t;i++){
        if(Ciur[i]) continue;
        prm.push_back(i);
        for(long j=i*i;j<=maxCiur;j+=i) Ciur[j]=true;
    }
}

void deBUG(){
    cerr << "----------------------------------\n";
    for(long pp=1;pp<=t;pp++){
        for(long ff=1;ff<=n;ff++) cerr << eq[pp][ff] ;
        cerr << '\n';
    }
    cerr << "----------------------------------\n";
}

void Gauss(){
    long i,j,k,l;
    i=1;j=1;

    while(i<=t&&j<=n){
        for(k=i;k<=t;k++)
            if(eq[k][j]==1) break;

        if(k==t+1){j++;continue;}
        if(k!=i){
            tmp = eq[i]; eq[i] = eq[k]; eq[k] = tmp;
        }

        for(k=i+1;k<=t;k++){
            if(eq[k][j]==0) continue;
            for(l=j+1;l<=n+1;l++) eq[k][l] = eq[k][l] ^ eq[i][l];
            eq[k][j] = 0;
        }

        i++;j++;
    }

    for(i=t;i;i--){
        for(j=1;j<=n;j++){
            if(eq[i][j]==0) continue;

            cnt += usedTo-j-1;
            usedTo = j;

            break;
        }
    }
}

int main()
{
    cin >> t >> n;
    make_ciur();

    for(i=1;i<=n;i++){
        cin >> x;
        for(j=0;j<t;j++){
            long fct = prm[j];
            while(x%(fct*fct)==0) x/=fct*fct;
            eq[j+1][i] = (x%fct==0);
        }
    }

    usedTo = n+1;
    Gauss();
    cnt += usedTo-1;

    bNumber ans; ans.init();
    while(cnt){ans.shl();cnt--;}
    ans.dec();

    ans.write();

    return 0;
}
