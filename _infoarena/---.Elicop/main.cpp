#include <fstream>

#define repeat(n) for(long rn = (n);rn;rn--)

using namespace std;

long n,m,i,j,sol[100],k,l1,c1,l2,c2,p,danger,sum,neafect=0,y;
long a[105][105];

    ifstream fin("elicop.in");
    ofstream fout("elicop.out");

int check() {
    long i,j,i2,j2;

    if(c1 > c2) {
       y = l1; l1 = l2; l2 = y;
       y = c1; c1 = c2; c2 = y;
    }

    if (p == 1) {
        if (l1<l2){
            i = l1-1; j = c1;
            i2 = l1; j2 = c1;
            danger = ((l2-l1+1)*(l2-l1+2))/2;
            danger = danger/2+1;

            sum = 0;
            repeat(l2-l1+1){
                sum += a[i2][j2] - a[i][j];
                if (sum >= danger) return 0;
                i2++; j2++;
                j++;
            }
        } else {
            i = l2-1; j = c2;
            i2 = l2 ; j2 = c2;
            danger = ((l1-l2+1)*(l1-l2+2))/2;
            danger = danger/2+1;

            sum = 0;
            repeat(l1-l2+1){
                sum += a[i2][j2] - a[i][j];
                if (sum >= danger) return 0;
                i2++; j2--;
                j--;
            }
        }
    } else {
        if (l1<l2){
            i = l1-1; j = c1;
            i2 = l2; j2 = c1;
            danger = ((l2-l1+1)*(l2-l1+2))/2;
            danger = danger/2+1;

            repeat(l2-l1+1){
                sum += a[i2][j2] - a[i][j];
                if (sum >= danger) return 0;
                i++; j++;
                j2++;
            }
        } else {
            i = l2-1; j = c2;
            i2 = l1 ; j2 = c2;
            danger = ((l1-l2+1)*(l1-l2+2))/2;
            danger = danger/2+1;

            sum = 0;
            repeat(l1-l2+1){
                sum += a[i2][j2] - a[i][j];
                if (sum >= danger) return 0;
                i++; j--;
                j2--;
            }
        }
    }

    if (sum == 0) neafect++;
    return 1;
}

int main()
{

    fin >> n >> m;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            fin >> a[i][j]; a[i][j] ^= 1;
            a[i][j] += a[i-1][j];
        }
    }

    fin >> k;
    for(i=1;i<=k;i++) {
        fin >> l1 >> c1 >> l2 >> c2 >> p;
        sum = 0;
        if (!check()){
            sol[++sol[0]] = i;
        }
        //fout << sum << "!\n";
    }

    fout << neafect << '\n' << sol[0] << ' ';
    for(i=1;i<=sol[0];i++) fout << sol[i] << ' ';

    /*fout << '\n';
    for (i=1;i<=n;i++) {
        for (j=1;j<=m;j++) fout << a[i][j] << ' ';
        fout << '\n';
    }*/

    fin.close();
    fout.close();
    return 0;
}
