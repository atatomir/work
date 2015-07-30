#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct liquid {
    long v;
    long id;
    liquid operator()(long vl,long idl){
        v = vl; id = idl;
        return *this;
    }
}elem;

struct answer{
    long long pos;
    char op;
}start,stop,aux;

long n,i,targ;
vector<liquid> S,D,a;
char op;
long long sum,act,x;

void getPos(answer& ans,long long x){
    if(x < sum){
        ans.op = 'S';
        ans.pos = sum - x;
    } else
    if(x > sum)
    {
        ans.op = 'D';
        ans.pos = x - sum;
    } else {
        ans.op = 'N';
        ans.pos = 0;
    }
}

int main()
{
    freopen("vase.in","r",stdin);
    freopen("vase.out","w",stdout);

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++){
        scanf("%lld %c",&x,&op);
        if(op == 'D')
            D.push_back(elem(x,i));
        else
        if(op == 'S')
            S.push_back(elem(x,i));
        sum += x / 2;
    }
    scanf("%ld",&targ);

    for(i=S.size()-1;i>=0;i--) a.push_back(S[i]);
    for(i=0;i<D.size();i++) a.push_back(D[i]);

    printf("%lld\n",sum);

    for(i=0;i<a.size();i++){
        if(a[i].id == targ){
            getPos(start,act);
            getPos(stop,act+a[i].v);

            if (start.op == 'N') start.op = stop.op;
            else
            if (stop.op == 'N') stop.op = start.op;

            if((start.op == stop.op)&&(start.pos < stop.pos)){
                aux=start;start=stop;stop=aux;
            }

            printf("%lld %c\n%lld %c\n",start.pos,start.op,stop.pos,stop.op);

            return 0;
        } else
            act = act + a[i].v;
    }

    return 0;
}
