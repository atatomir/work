#include <cstdio>
inline int myabs(int x){
    if(x<0) return -x;
    else return x;
}
inline int max2(int a, int b){
    if(a>b) return a;
    else return b;
}
inline int min2(int a, int b){
    if(a<b) return a;
    else return b;
}
int main(){
    int ans, t, a, b, x1, x2, y1, y2;
    FILE *fin, *fout;
    fin=fopen("taxi.in", "r");
    fout=fopen("taxi.ok", "w");
    fscanf(fin, "%d", &t);
    for(; t; t--){
        fscanf(fin, "%d%d%d%d%d%d", &a, &b, &x1, &y1, &x2, &y2);
        if((myabs(x1-x2)+myabs(y1-y2))%2==1){
            ans=0;
        }else if(myabs(x1-x2)+myabs(y1-y2)==0){
            ans=(a+1)*(b+1);
        }else if(x1==x2){
            ans=a+1;
        }else if(y1==y2){
            ans=b+1;
        }else if(myabs(x1-x2)==myabs(y1-y2)){
            if((int)(min2(x1, x2)==x1)+(int)(min2(y1, y2)==y1)==1) ans=myabs(x1-x2)-1+(min2(x1, x2)+1)*(min2(y1, y2)+1)+(a-max2(x1, x2)+1)*(b-max2(y1, y2)+1);
            else ans=myabs(x1-x2)-1+(min2(x1, x2)+1)*(b-max2(y1, y2)+1)+(min2(y1, y2)+1)*(a-max2(x1, x2)+1);
        }else if(myabs(x1-x2)<myabs(y1-y2)){
            ans=a+1;
        }else{
            ans=b+1;
        }
        fprintf(fout, "%d\n", ans);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

/*
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int t, n, i, j;
ll A, B, xx1, yy1, xx2, yy2, ans;

ll dist(ll xx1, ll yy1, ll xx2, ll yy2) {
    xx1 -= xx2;
    if (xx1 < 0) xx1 = -xx1;

    yy1 -= yy2;
    if (yy1 < 0) yy1 = -yy1;

    return xx1 + yy1;
}

int main()
{
    freopen("taxi.in","r",stdin);
    freopen("taxi.ok","w",stdout);

    for (scanf("%d", &t); t > 0; t--) {
        scanf("%lld%lld%lld%lld%lld%lld", &A, &B, &xx1, &yy1, &xx2, &yy2);

        ans = 0;
        for (i = 0; i <= A; i++)
            for (j = 0; j <= B; j++)
                if (dist(xx1, yy1, i, j) == dist(xx2, yy2, i, j))
                    ans++;

        printf("%lld\n", ans);
    }



    return 0;
}
*/
