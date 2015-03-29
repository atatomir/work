#include <fstream>

using namespace std;

struct {
    long c,a;
} sol[1005],y;

long n,a,b,i,j,ia,ib,t,c,cont=0;
long m[205][205],mars[205][205];
long x1,y1,x2,y2,maxim=0,aria,targ,p;

long indi[9]={0,1,1,-1,-1,1,0,0,-1};
long indj[9]={0,1,-1,-1,1,0,1,-1,0};

void normalizeaza() {
    x1 += ia; x2 += ia;
    y1 += ib; y2 += ib;
}

void Recurs(long i,long j){
    m[i][j] = -1; aria++;
    for(long p=1;p<=8;p++){
       if(m[i+indi[p]][j+indj[p]] == targ) {
            Recurs(i+indi[p],j+indj[p]);
       }
    }
}

void QSort(long l,long h){
    long i=l,j=h,x=sol[(i+j)/2].c,x2=sol[(i+j)/2].a;
    do {
        while ((sol[i].c < x)||((sol[i].c == x)&&(sol[i].a < x2))) i++;
        while ((sol[j].c > x)||((sol[j].c == x)&&(sol[j].a > x2))) j--;
        if (i<=j){
            y = sol[i]; sol[i] = sol[j]; sol[j] = y;
            i++; j--;
        }
    }   while(i<=j);
    if (l < j) QSort(l,j);
    if (i < h) QSort(i,h);
}

int main()
{
    ifstream fin("figuri.in");
    ofstream fout("figuri.out");


    fin >> b >> a >> n;
    ia = a / 2; ib = b / 2;

    for(i=1;i<=a;i++){
        for(j=1;j<=b;j++) m[i][j] = 1;
    }

    for(t=n;t;t--){
        fin >> y1 >> x1 >> y2 >> x2 >> c;
        x2--; y2--;
        normalizeaza();

        mars[x1+1][y1+1]++;
        mars[x2+2][y2+2]++;
        mars[x1+1][y2+2]--;
        mars[x2+2][y1+1]--;

        for(i=x1+1;i<=x2+1;i++){
            for(j=y1+1;j<=y2+1;j++) m[i][j] = c;
        }
    }

    for(i=1;i<=a;i++){
        for(j=1;j<=b;j++){
            mars[i][j] += mars[i-1][j] + mars[i][j-1] - mars[i-1][j-1];
            if (mars[i][j] > maxim) maxim = mars[i][j];
        }
    }

    for(i=1;i<=a;i++){
        for(j=1;j<=b;j++){
            if(m[i][j] > 0) {
                sol[++cont].c = m[i][j]; aria = 0; targ = m[i][j];
                Recurs(i,j);
                sol[cont].a = aria;
            }
        }
    }

    QSort(1,cont);

    for(i=1;i<=cont;i++) fout << sol[i].c << ' ' << sol[i].a << '\n';


    fout << maxim+1;


    fin.close();
    fout.close();
    return 0;
}
