#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define eps 0.00001
#define maxN 555

struct Point{double x,y;};
struct Segm{Point f,s;double fSlo,sSlo;};

long n,i,nn;
Segm S[maxN];
double Slopes[maxN<<1];
double tmp,PI;

bitset< maxN<<1 >  eq[maxN],bTMP;
bool used[maxN<<1];
double how[maxN<<1];

bool abss(double x){
    if(x<0) return -x;
    return x;
}

double getAngle(Point p){
    double ans = atan2(p.y,p.x);
    ans = (ans*180.00)/PI;
    if(ans < 0.00) ans += 360.00;
    return ans;
}

bool isChanged(long aSegm,double ang){
    if(abss(ang-S[aSegm].sSlo)<=eps) return true;
    if(abss(ang-S[aSegm].fSlo)<=eps) return true;

    if(S[aSegm].sSlo-S[aSegm].fSlo <= 180.00+eps)
        return (S[aSegm].sSlo+eps>=ang && S[aSegm].fSlo-eps<=ang);
    else
        return !(S[aSegm].sSlo+eps>=ang && S[aSegm].fSlo-eps<=ang);
}
void Try(long id,double ang){
    for(long i=1;i<=n;i++){
        if(!isChanged(i,ang)) continue;
        eq[i][id] = 1;
    }
}

void Gauss(){
    long i,j,k,l;
    i=1;j=1;

    while(i<=n&&j<=nn){
        for(k=i;k<=n;k++)
            if(eq[k][j]==1) break;

        if(k==n+1) {j++;continue;}
        if(k>i){bTMP = eq[i]; eq[i] = eq[k]; eq[k] = bTMP;}

        for(k=i+1;k<=n;k++){
            if(!eq[k][j]) continue;
            for(l=j+1;l<=nn+1;l++) eq[k][l] = eq[k][l] ^ (eq[i][l]);
            eq[k][j] = 0;
        }

        i++; j++;
    }

    for(i=n;i;i--){
        for(j=1;j<=nn;j++){
            if(eq[i][j]==0) continue;

            long ans = eq[i][nn+1];
            for(l=j+1;l<=nn;l++) ans ^= eq[i][l]&used[l];
            used[j] = ans;

            break;
        }
    }

}

int main()
{
    freopen("laser.in","r",stdin);
    freopen("laser.out","w",stdout);

    PI = acos(-1.00);
    scanf("%ld",&n); nn=0;
    for(i=1;i<=n;i++){
        scanf("%lf %lf %lf %lf",&S[i].f.x,&S[i].f.y,&S[i].s.x,&S[i].s.y);
        S[i].fSlo = getAngle(S[i].f);
        S[i].sSlo = getAngle(S[i].s);

        if(S[i].fSlo > S[i].sSlo) {tmp=S[i].fSlo;S[i].fSlo=S[i].sSlo;S[i].sSlo=tmp;}
        Slopes[++nn] = S[i].fSlo;
        Slopes[++nn] = S[i].sSlo;
    }
    sort(Slopes+1,Slopes+nn+1);
    Slopes[nn+1] = Slopes[1]+360.00;

    for(i=1;i<=nn;i++){
        double ang = (Slopes[i]+Slopes[i+1])/2;
        if(ang >= 360.00-eps) ang-= 360.00;

        Try(i,ang);
        how[i] = ang;
    }

    for(i=1;i<=n;i++) {
        long mtmp;
        scanf("%ld",&mtmp);
        eq[i][nn+1] = mtmp;
    }

    Gauss();

    n = 0;
    for(i=1;i<=nn;i++)
        if(used[i]) n++;
    printf("%ld\n",n);

    for(i=1;i<=nn;i++){
        if(!used[i]) continue;
        printf("%.6lf\n",how[i]);
    }

    return 0;
}
