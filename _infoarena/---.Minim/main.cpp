#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("minim.in");
ofstream fout("minim.out");

long n,i,a[1005],jump[1005],cont;
long minim,mini,minj,act,acti,source,acts,ant;

int main()
{
    fin >> n;
    for(i=1;i<=n;i++){
        fin >> a[i];
        jump[i] = 1;
    }
    jump[0] = 1;


    cont = n; minim = 1e7 + 5; act= 5; acti = 1;
    while(cont){
        minim = 1e7 + 5; act= 5; acti = 1; acts = 0; ant = 0;
        for(i=jump[0];i<=n;i = i+ jump[i]){
            if(act < 0){
                act += a[i];
            } else {
                act = a[i]; acti = i; acts = ant;
            }

            if((act < minim)||((act == minim)&&(minj-mini+1 > i-acti+1))){
                    minim = act; mini = acti; minj = i;
                    source = acts;
            }

            ant = i;
        }
        fout << minim << ' ' << mini << ' ' << minj << '\n';
        cont -= minj-mini+1;
        jump[source] += minj-mini + jump[minj];
    }


    fin.close();
    fout.close();
    return 0;
}
