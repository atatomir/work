#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define maxGroup 3111
#define maxElem  3111

long n,A,B,P,Q,rA,rB,val,tmp,i,l,h,dim;
long Group[maxGroup],Elem[maxElem],ElemL[maxElem],GroupL[maxGroup];
long cGr,cEl;

long antProd;
long actProd;
long Answer,lAnswer;

inline long getA(long i){
    return ((A+P-1)^(B+1))%P;
}
inline long getB(long i){
    return ((A+P-1)|(B+1))%P;
}
inline long getVal(long i){
    return max(1L,((i % P) ^ (((A + 1) & (B + 1)) % P)) % P);
}
inline void Renew(long i){
    tmp = getA(i);
    B = getB(i);
    A = tmp;
    val = getVal(i);
}

int main()
{
    freopen("xp.in","r",stdin);
    freopen("xp.out","w",stdout);

    scanf("%ld %ld %ld %ld %ld",&n,&rA,&rB,&P,&Q);
    A = rA; B = rB; val = getVal(1);

    cEl = (long)sqrt(n);
    cGr = (n+cEl-1)/cEl;

    for(i=0;i<=cGr + 10;i++) Group[i] = GroupL[i] = 1;

    for(i=1;i<=n;i++){
        long actGr = (i-1) / cEl + 1;
        Group[actGr] = ((long long)Group[actGr]*(long long)val)%(long long)Q;

        Renew(i+1);
    }

    GroupL[1] = Group[1];
    for(i=1;i<cGr;i++)      GroupL[i+1] = ((long long)Group[i+1]*(long long)GroupL[i])%(long long)Q;
    for(i=cGr-2;i>=0;i--)   Group[i+1] = ((long long)Group[i+1]*(long long)Group[i+2])%(long long)Q;

    A = rA; B = rB; val = getVal(1);
    antProd = 1;

    for(long actGr = 0;actGr<cGr;actGr++){
        for(i=0;i<=cEl + 10;i++) Elem[i] = ElemL[i] = 1;

        l = actGr*cEl; h = (actGr+1)*cEl-1;
        if(h >= n) h = n-1;
        dim = h-l+1;

        for(i=0;i<dim;i++){
            Elem[i+1] = val;
            Renew(l+i+2);
        }
        ElemL[1] = Elem[1];
        for(i=1;i<dim;i++)    ElemL[i+1] = ((long long)Elem[i+1]*(long long)ElemL[i])%(long long)Q;
        for(i=dim-2;i>=0;i--) Elem[i+1] = ((long long)Elem[i+1]*(long long)Elem[i+2])%(long long)Q;

        for(i=0;i<dim;i++){
            lAnswer = ((((long long)GroupL[actGr] * (long long)Group[actGr+2])%(long long)Q) * (((long long)ElemL[i] * (long long)Elem[i+2])%(long long)Q))%(long long)Q;
            Answer = Answer ^ lAnswer;
        }

        antProd = ((long long)antProd * (long long)GroupL[dim])% Q;
    }

    printf("%ld",Answer);


    return 0;
}
