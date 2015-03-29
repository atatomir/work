#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

struct dequeElem{
    long v;
    long pos;
    dequeElem operator()(long vl,long posl){
        v = vl; pos = posl;
        return *this;
    }
}elem;

long n,i,k,maxi,maxj;
long maxim=-30005,x;
deque<dequeElem> dq;
char s[5000000];
long pos=0;

long getLong(){
    long ind=1,ans=0;;
    while(s[pos] == ' ') pos++;
    if(s[pos] == '-') ind=-1,pos++;
    while((s[pos] >= '0')&&(s[pos] <= '9')) {
        ans = ans*10 + s[pos]-'0';
        pos++;
    }
    return ans*ind;
}

int main()
{
    freopen("secventa.in","r",stdin);
    freopen("secventa.out","w",stdout);

    scanf("%ld %ld\n",&n,&k);
    gets(s);

    for(i=1;i<=n;i++) {
        x = getLong();

        if(!dq.empty())
        while(dq.back().v > x){
            dq.pop_back();
            if(dq.empty()) break;
        }
        dq.push_back(elem(x,i));
        while(dq.front().pos <= i-k) dq.pop_front();

        elem = dq.front();
        if((maxim < elem.v)&&(i >=k)){
            maxim = elem.v;
            maxj = i;
            maxi = i-k+1;
        }
    }

    printf("%ld %ld %ld \n",maxi,maxj,maxim);

    return 0;
}
