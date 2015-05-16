#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

#define maxN 1011
#define pb push_back
#define itt vector<long>::iterator
#define vec vector<long>

long n,i,j;
bitset<maxN> com[maxN][maxN];
bitset<maxN> ec[maxN],tmp;
bitset<maxN> sol;
bitset<maxN> ans[maxN];

inline void push(long id,bitset<maxN>& s){
    ec[id] = ec[id] ^ s;
}

void gauss(){
    long i,j,k,l;
    i=j=1;

    while(i<=n&&j<=n){
        for(k=i;k<=n;k++)
            if(ec[k][j]==1) break;
        if(k==n+1){
            j++;
            continue;
        }

        tmp = ec[i]; ec[i] = ec[k]; ec[k] = tmp;
        for(k=i+1;k<=n;k++){
            if(ec[k][j]==0) continue;
            ec[k] = ec[k] ^ec[i];
        }
        i++;j++;
    }

    for(i=n;i;i--){
        for(j=1;j<=n;j++){
            if(ec[i][j]==1){
                sol[j] = ec[i][n+1];
                for(l=j+1;l<=n;l++)
                    if(ec[i][l]==1)
                        sol[j] = sol[j]^sol[l];
                break;
            }
        }
    }
}

inline void setVal(long i,long j){
    ans[i][j] = ans[i-1][j]^ans[i-1][j-1]^ans[i-1][j+1]^ans[i-2][j]^1;
}

int main()
{
    freopen("switch5.in","r",stdin);
    freopen("switch5.out","w",stdout);



    scanf("%ld",&n);
    for(i=1;i<=n;i++) com[1][i][i]=1;
    for(i=2;i<=n;i++){
        for(j=1;j<=n;j++){
            com[i][j] = com[i-1][j]^com[i-1][j-1]^com[i-1][j+1]^com[i-2][j];
            com[i][j][0] = com[i][j][0]^1;
        }

    }

    for(i=1;i<=n;i++){
        push(i,com[n][i]);
        push(i,com[n][i-1]);
        push(i,com[n][i+1]);
        push(i,com[n-1][i]);

        ec[i][n+1] = 1;
    }


    sol[0] = 1;
    for(i=1;i<=n;i++)
        if(ec[i][0]==1) ec[i][n+1] = ec[i][n+1]^1;
    gauss();

    for(i=1;i<=n;i++) {ans[1][i] = sol[i];if(ans[1].test(i)==true)printf("1");else printf("0");}
    printf("\n");
    for(i=2;i<=n;i++){
        for(j=1;j<=n;j++){
            setVal(i,j);
            if(ans[i].test(j)==true)
                printf("1");else printf("0");
        }
        printf("\n");
    }

    /*for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            long cnt=0;
            cnt = ans[i][j]+ans[i-1][j]+ans[i+1][j]+ans[i][j-1]+ans[i][j+1];
            if(cnt%2==0) {
                cerr << "Eroare : " << i << ' ' << j ;
                return 0;
            }
        }
    }*/

    return 0;
}
