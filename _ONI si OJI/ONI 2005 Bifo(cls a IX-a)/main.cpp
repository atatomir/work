#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxC 222
char s[maxC];
class bNumber{
    public:
        long c[maxC],cnt;

        void init(long val){
            memset(c,0,sizeof(c)); cnt=0;
            while(val){
                c[++cnt] = val%10;
                val /=10;
            }
            if(cnt==0) cnt++;
        }
        bool Greater(bNumber& tmp){
            if(cnt > tmp.cnt) return true;
            if(cnt < tmp.cnt) return false;
            for(long i=cnt;i;i--)
                if(c[i]>tmp.c[i]) return true; else
                if(c[i]<tmp.c[i]) return false;
            return false;
        }
        void sum(bNumber& tmp){
            cnt = max(cnt,tmp.cnt);
            for(long i=1;i<=cnt;i++) c[i] += tmp.c[i];
            for(long i=1;i<=cnt;i++) {c[i+1] += c[i]/10; c[i]%=10;}
            while(c[cnt+1]!=0) cnt++;
        }
        void getVal(){
            memset(s,0,sizeof(s)); cnt=0;
            scanf("%s\n",s+1);
            long len = strlen(s+1);
            for(long i=len;i;i--) c[++cnt] = s[i]-'0';
        }
        void Minus(bNumber& tmp){
            long i;
            for(i=1;i<=tmp.cnt;i++) c[i] -= tmp.c[i];
            for(i=1;i<=cnt;i++){
                while(c[i]<0) {
                    c[i] += 10;
                    c[i+1]--;
                }
            }
            while(c[cnt]==0&& cnt) cnt--;
            if(cnt==0) cnt++;
        }
        long getLong(){
            long ans=0;
            for(long i=cnt;i;i--) ans = ans*10 + c[i];
            return ans;
        }
};

char A1[maxC],A2[maxC];
long n,i;

bNumber lung[1000],nr;

char solve(long pas){
    if(pas<=2){
        long val = nr.getLong();
        if(pas==1) return A1[val];
        return A2[val];
    }

    if(!nr.Greater(lung[pas-2])){
        solve(pas-2);
    }else{
        nr.Minus(lung[pas-2]);
        solve(pas-1);
    }
}

int main()
{
    freopen("bifo.in","r",stdin);
    freopen("bifo.out","w",stdout);

    scanf("%s\n%s\n%ld\n",A1+1,A2+1,&n);

    lung[1].init(strlen(A1+1));
    lung[2].init(strlen(A2+1));

    for(i=3;lung[i-1].cnt<=100;i++){
        lung[i].init(0);
        lung[i].sum(lung[i-1]);
        lung[i].sum(lung[i-2]);
    }

    for(;n;n--){
        nr.init(0);
        nr.getVal();

        for(i=1;nr.Greater(lung[i]);i++)
            nr.Minus(lung[i]);

        printf("%c",solve(i));
    }

    return 0;
}
