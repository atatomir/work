#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const long def[10][6] = {   0,0,0,0,0,0,
                            4,1,2,4,5,0,
                            3,1,2,3,0,0,
                            4,2,3,5,6,0,
                            3,1,4,7,0,0,
                            5,2,4,5,6,8,
                            3,3,6,9,0,0,
                            4,4,5,7,8,0,
                            3,7,8,9,0,0,
                            4,5,6,8,9,0,
                       };
/*! ^Asta inseamna sa fi un tractorist^ ... dar se poate mult mai rau !*/

long n,i,j,how;
long cnt[10];
long a[10];
long tmp[10];

vector<long> ans,need;
long bAns=1<<29;

bool better(){
    if(how<bAns) return true;
    for(long i=0;i<need.size();i++){
        if(ans[i]<need[i]) return false;
        if(ans[i]>need[i]) return true;
    }
    return false;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    for(i=1;i<=9;i++) scanf("%ld",&a[i]);

    for(cnt[1]=0;cnt[1]<4;cnt[1]++)
    for(cnt[2]=0;cnt[2]<4;cnt[2]++)
    for(cnt[3]=0;cnt[3]<4;cnt[3]++)
    for(cnt[4]=0;cnt[4]<4;cnt[4]++)  /*! Doar pentru fericirea mea */
    for(cnt[5]=0;cnt[5]<4;cnt[5]++)  /*! de a nu folosi back       */
    for(cnt[6]=0;cnt[6]<4;cnt[6]++)
    for(cnt[7]=0;cnt[7]<4;cnt[7]++)
    for(cnt[8]=0;cnt[8]<4;cnt[8]++)
    for(cnt[9]=0;cnt[9]<4;cnt[9]++){
        for(i=1;i<=9;i++) tmp[i]=a[i]/3;

        for(i=1;i<=9;i++){
            for(j=1;j<=def[i][0];j++)
                tmp[ def[i][j] ] += cnt[i];
        }

        bool Alright = true;
        for(i=1;i<=9;i++)
            if(tmp[i]%4 != 0) Alright = false;

        if(Alright){
            how = 0;
            for(i=1;i<=n;i++) how += cnt[i];

            if(bAns < how) continue;

            need.clear();
            for(i=1;i<=9;i++){
                long ccnt = cnt[i];
                while( ccnt ){
                    ccnt--;
                    need.push_back(i);
                }
            }

            if(better()){
                ans = need;
                bAns = how;
            }

        }
    }

    for(i=0;i<ans.size();i++) printf("%ld ",ans[i]);


    return 0;
}
