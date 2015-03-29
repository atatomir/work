#include <cstdio>

using namespace std;

int pr[11] = {0,3,5,7,11,13,17,19,23,29,31},k=10,i,n;
char v[40];
long long cont = 0;

void Rezolva(long pas,int ant) {
    int t;

    if (pas == n+1) {
        ant++;
        int gasit = 0;
        for(int i = 1;i<=k;i++)
            if (pr[i] == ant) {
              gasit = 1;
              break;
            }
        if (gasit) cont++;
    } else {
        for(int i=1;i<=k,pr[i]-ant <= n;i++) {
            if (pr[i] <= ant) continue;
            t = pr[i] - ant;

            if (v[t]) {
                v[t] = 0;
                Rezolva(pas+1,t);
                v[t] = 1;
            }
        }

    }

}

int main()
{
    freopen("inel.in","r",stdin);
    freopen("inel.out","w",stdout);

    scanf("%d",&n);

    for(i=1;i<=35;i++) v[i] = 1;

    v[1] = 0;
    Rezolva(2,1);

    printf("%lld",cont);

    return 0;
}
