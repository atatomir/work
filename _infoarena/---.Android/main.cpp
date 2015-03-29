#include <iostream>
#include <fstream>

#define mod 666013

using namespace std;

ifstream fin("android.in");
ofstream fout("android.out");

long n,m,i,j;
long pre[30][30];


long def,lim,conf,endc,endcp,aconf,endac;
long sol[1 << 22][23],answer;


inline long cmmdc(long a,long b){
    long t;

    if(a<0) a*=-1;
    if(b<0) b*=-1;

    if(a < b) {t=a;a=b;b=t;}
    while(b){
        a = a % b;
        t=a;a=b;b=t;
    }
    return a;
}

inline void preCalc(){
    long lim = n*m,i,j,x1=1,x2,y1,y2,dim,xp,yp,posi,posj,p,id;
    for(i=1;i<lim;i++){
        for(j=i+1;j<=lim;j++){
            x1 = (i+m-1) / m;
            y1 = i % m; if(y1 == 0) y1 = m;

            x2 = (j+m-1) / m;
            y2 = j % m; if(y2 == 0) y2 = m;

            dim = cmmdc(x2-x1,y2-y1);
            xp = (x2-x1)/dim; yp = (y2-y1)/dim;

            posi = x1; posj = y1;
            id = (posi-1)*m + posj;
            xp = xp*m+yp;

            for(p=1;p<dim;p++){
                id+= xp;
                pre[i][j] |=(1 << (id-1));
            };
        }
    }
}

inline int check(long conf,int pos1,int pos2){

    if(pos1 > pos2 ) {int t = pos1; pos1=pos2; pos2 = t;}

    if ( ( pre[pos1][pos2] & conf ) !=  pre[pos1][pos2]) return 0;
    return 1;
}

int main()
{
    fin >> n >> m;

    preCalc();

    lim = n*m;
    def = 1 << lim;

    for(conf=1;conf<def;conf++){
        endcp = 1;
        for(endc=1;endc<=lim;endc++){
            if(conf & endcp){
                aconf = conf ^ endcp;
                if(aconf == 0) {
                    sol[conf][endc] = 1;
                    answer ++;
                    break;
                }

                for(endac=0;endac<lim;endac++){
                    if(aconf&(1 << endac)){
                        if(check(aconf,endc,endac+1)){
                            sol[conf][endc] = sol[conf][endc] + sol[aconf][endac+1];
                        }
                    }
                }
                if(sol[conf][endc] > mod)sol[conf][endc] %= mod;
                answer += sol[conf][endc];
                //if(answer > mod)answer -= mod;
            };
            endcp <<=1;
            if(endcp > conf) break;
        }
        if(answer > mod)answer %= mod;
    }

    fout << answer% mod << '\n';

   /*for(i=0;i<=lim;i++) fout << i << ' '; fout << '\n';
    for(i=1;i<=def;i++){
        fout << i << '|';
        for(j=1;j<=lim;j++) fout << sol[i][j] << ' ';
        fout << '\n';
    }*/

    fin.close();
    fout.close();
    return 0;
}
