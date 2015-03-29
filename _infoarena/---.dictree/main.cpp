

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

long n,i,k;
char s[25011][111];
unsigned long sll[25011][26],v;
long ind[25011],size[25011];
long Ans=1;

#define maxBuf 100000
char Buff[maxBuf];
long pos;

inline bool isLetter(char c){
    c = c | 0x20;
    return (c>='a'&& c<='z') ;
}

inline char codeLetter(char c){
    if (c < 'A') return 0;
    if (c <= 'Z') return c-'A'+1;
    return c - 'a' + 27;
}

long readS(long dest){
    while(!isLetter(Buff[pos])){
        pos++;
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    long posS=0;
    while(isLetter(Buff[pos])){
        s[dest][posS++] = Buff[pos++];
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }

    }
    return posS-1;
}

inline bool isDigit(char c){
    return c>='0' && c <= '9';
}
long readN(){
    while(!isDigit(Buff[pos])){
        pos++;
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    long ans=0;
    while(isDigit(Buff[pos])){
        ans = ans*10 + Buff[pos++] - '0';
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }

    }
    return ans;
}


bool cmp(long x,long y){
    long i,j;
    j = min(size[x],size[y]);
    for(i=0; sll[x][i] == sll[y][i] && i <= (j+4)/5;i++) ;
    return sll[x][i] < sll[y][i];

   // return memcmp(&s[x][0],&s[y][0],j+1)<0;
}

long getDif(long sour,long dest){
    long i,j;
    j = size[dest];
    for(i=-1;s[sour][i+1] == s[dest][i+1] && i<j;i++);
    return j-i;
}


int main()
{
    freopen("dictree.in","r",stdin);
    freopen("dictree.out","w",stdout);

    fread(Buff,1,maxBuf,stdin);

    n = readN();
    for(i=1;i<=n;i++) {
        size[i] = readS(i);
        ind[i] = i;
        for(k=0;k<20;k++){
            v = codeLetter(s[i][5*k]) << 24;
            v = v | (codeLetter(s[i][5*k+1]) << 18);
            v = v | (codeLetter(s[i][5*k+2]) << 12);
            v = v | (codeLetter(s[i][5*k+3]) << 6);
            v = v | (codeLetter(s[i][5*k+4]));
            sll[i][k] = v;
        }
    }

    sort(ind+1,ind+n+1,cmp);

    for(i=1;i<=n;i++){
        Ans += getDif(ind[i-1],ind[i]);
    }

    printf("%ld\n",Ans);
    //for(i=1;i<=n;i++) printf("%s\n",s[ind[i]]);

    return 0;
}

