#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define maxN 15003
#define ull unsigned long long
#define maxBuf 100000

long n,i,act,best,j,last;
long ind[maxN];

char Buff[maxBuf];
long pos=0;
char S[30003];

inline bool isLetter(char c){
    return c>='a' && c <= 'z';
}
void readS(){
    long tmp=0;
    while(!isLetter(Buff[pos])){
        pos++;
        if(pos == maxBuf) {
            pos = 0;
            memset(Buff,0,sizeof(Buff));
            fread(Buff,1,maxBuf,stdin);
        }

        if(++tmp > 3) return ;
    }
    long posS=0;
    while(isLetter(Buff[pos])){
        S[posS++] = Buff[pos++];
        if(pos == maxBuf) {
            pos = 0;
            memset(Buff,0,sizeof(Buff));
            fread(Buff,1,maxBuf,stdin);
        }
    }
    S[posS] = '\0';

    last = posS;
}

struct Word{
    long pos;
    unsigned long long v[2];

    char s[25];
    long Size;

    void setW(long p){
        v[p/64] |= (ull)1 << (p%64);
    }
    bool isBest(){
        if(best == -1) return true;
        return v[best/64] & ((ull)1 << (best%64));
    }
    void write(){
        for(long i=Size-1;i>=0;i--) printf("%c",s[i]);
        printf(" ");
    }
};

bool Check(char a[30],char b[30],long bSize){
    long n1= last,n2 = bSize;
    if(n1 != n2) return false;

    for(long i=0;i<n1;i++) if(a[i] != b[i]) return false;

    return true;
}

Word W[maxN];
vector<long> Ans;

bool cmp(long i1,long i2){
    if(W[i1].v[1] < W[i2].v[1]) return false;
    if(W[i1].v[1] > W[i2].v[1]) return true;

    if(W[i1].v[0] < W[i2].v[0]) return false;
    if(W[i1].v[0] > W[i2].v[0]) return true;

    return W[i1].pos < W[i2].pos;
}

int main()
{
    freopen("mesaje.in","r",stdin);
    freopen("mesaje.out","w",stdout);

    n = 0; gets(S);
    i = 0;
    j = strlen(S);

    while(i < j){
        while(S[i] == ' ') i++;
        if(S[i] >= 'a' && S[i] <= 'z'){
            n++;
            W[n].pos = n-1; W[n].v[0] = W[n].v[1] = 0; W[n].Size = 0;
            while(S[i] >= 'a' && S[i] <= 'z'){
                W[n].s[W[n].Size++] = S[i++];
            }
        }
    }


    act = 0; best = -1;
    fread(Buff,1,maxBuf,stdin);
    memset(S,0,sizeof(S));

    while(!feof(stdin) || pos < maxBuf){
        for(i=1;i<=n;i++){
            S[0] = '!';
            readS();
            if(!Check(S,W[i].s,W[i].Size)) continue;
            W[i].setW(act); best = act;
        }
        if(S[0] == '!') break;
        act++;
    }


    for(i=1;i<=n;i++) ind[i] = i;
    sort(ind+1,ind+n+1,cmp);
    for(i=1;i<=n;i++){
        if(!W[ind[i]].isBest()) break;
        Ans.push_back(ind[i]);
    }
    printf("%ld\n",Ans.size());
    for(i=0;i<Ans.size();i++) W[Ans[i]].write();

    return 0;
}
