#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#line 5 "FoxJumping.cpp"

using namespace std;

#define maxR 1700
#define maxT 911
#define mod 10007

//! down...
long dp[2][maxR][maxT];
long tmp[maxT];

long dpb[maxR][maxT/10];

long C[maxR][maxR];
//! down...

class FoxJumping {
	private:
        //! first dp
        void fix(long& a){
            while(a<0)    a+= mod;
            while(a>=mod) a-= mod;
        }
        void fix(long long& a){
            while(a<0)    a+= mod;
            while(a>=mod) a-= mod;
        }

        void computeDP(long id,long R,long T,long M){
            long i,j;

            dp[id][0][0]=1;
            for(i=1;i<=T;i++) dp[id][0][i]=0;
            for(i=1;i<=R;i++){
                tmp[0] = dp[id][i-1][0]; //! calc sume partiale
                for(j=1;j<=T;j++) tmp[j] = (tmp[j-1]+dp[id][i-1][j])%mod;

                for(j=0;j<=T;j++){
                    dp[id][i][j] = tmp[j];
                    if(j>=M+1) dp[id][i][j] -= tmp[j-M-1];

                    fix(dp[id][i][j]);
                }
            }
        }

        //! second dp

        void computeDPB(long R,long T,vector<int>& bad){
            long i,j,k;

            dpb[0][0] = 1;
            for(i=1;i<=T;i++) dpb[0][i] = 0;

            for(i=1;i<=R;i++){ //! pas
                for(j=0;j<=T;j++){ //! pozitie
                    dpb[i][j]=0;

                    for(k=0;k<bad.size();k++){ //! element
                        long val = bad[k];
                        if(val > j+1) continue;

                        dpb[i][j] += dpb[i-1][ j-val ];
                        fix(dpb[i][j]);
                    }
                }
            }
        }

        //! Comb dp

        void computeComb(long R){
            long i,j;

            C[1][1] = 1; C[1][0]=1;
            for(i=2;i<=R;i++){
                C[i][1] = i; C[i][0]=1;
                for(j=2;j<=i;j++){
                    C[i][j] = C[i-1][j]+C[i-1][j-1];
                    fix(C[i][j]);
                }
                C[i][i+1]=0;
            }
        }

        //! get Answer

        int getAns( long R,long Tx,long Ty ){
            long i,j;
            long T = min(Tx,Ty)/10;

            long ans = 0;

            for(i=0;i<=R;i++){
                long sgn = (i&1?-1:1);
                for(j=0;j<=T;j++){
                    //cerr << i << ' ' << j << '\n';

                    long long tmp = 1LL*sgn*dpb[i][j];

                    //cerr << tmp << '\n';

                    tmp *= dp[0][R-i][Tx-j*10]; fix(tmp);

                    //cerr << tmp << '\n';

                    tmp *= dp[1][R-i][Ty-j*10]; fix(tmp);

                    //cerr << tmp << '\n';

                    tmp *= C[R][i];          fix(tmp);

                    //cerr << tmp << '\n';

                    ans += (int)tmp; fix(ans);
                }
            }

            return (int)ans;
        }


	public:

	void init(){
        memset(dp,0,sizeof(dp));
        memset(dp,0,sizeof(dpb));
        memset(dp,0,sizeof(tmp));
        memset(dp,0,sizeof(C));
	}

	int getCount(int Tx, int Ty, int Mx, int My, int R, vector <int> bad) {
        init();

        //! Compute first dp
        computeDP(0,R,Tx,Mx);
        computeDP(1,R,Ty,My);

        //! Compute second dp
        bad.push_back(0);
        for(long i=0;i<bad.size();i++) bad[i]/=10;
        computeDPB(R,min(Tx,Ty)/10,bad);

        //! Compute C(n,k)
        computeComb(R);

        return getAns( R ,Tx,Ty );

	}
};


int main(){
    FoxJumping fox;

    vector<int> vv ; vv.clear();
    for(long i=10;i<=50;i+=10) vv.push_back(i);
    cerr << fox.getCount(123,456,70,80,90,vv);

    vv.clear(); vv.push_back(10);
    cerr << ' '<<fox.getCount(11,11,11,11,2,vv);

    vv.clear();
    cerr << ' '<<fox.getCount(1,1,1,1,1600,vv);


    return 0;
}
