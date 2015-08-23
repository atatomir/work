#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

class Buffer{
    public:
        int maxBuf,pos;
        vector<char> Buff;

        Buffer(char fileName[],int buffSize){
            freopen(fileName,"r",stdin);
            maxBuf = buffSize; Buff.resize(maxBuf);
            reFill();
        }

        Buffer& operator>>(int &dest){
            while(!isDigit(Buff[pos])){
                pos++;
                if(pos == maxBuf) reFill();
            }
            dest = 0;
            while(isDigit(Buff[pos])){
                dest = dest*10 + Buff[pos++] - '0';
                if(pos == maxBuf) reFill();
            }
            return *this;
        }

    private:
        bool isDigit(char c){
            return c >= '0' & c <= '9';
        }
        void reFill(){
            fread(&Buff[0],1,maxBuf,stdin); pos = 0;
        }
};

Buffer fin("jmenoasa.in",1<<20);
ofstream fout("jmenoasa.out");

int n,m,i,j,ans;
int matrix[maxN][maxN];

short upBest[maxN][maxN]; //! good - left,up
short upGood[maxN][maxN]; //! good - up

stack< pair<int,int> > S; //! pos,val
short auxL[maxN],auxR[maxN];

short addStack(int pos,int val) {
    while ( val <= S.top().second ) S.pop();
    int ret = S.top().first;
    S.push( mp( pos,val ) );

    return ret;
}

int main()
{
    ans = 1;
    fin >> n >> m ;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++){
            fin >> matrix[i][j];
        }
    }

    /*
    //!--------------------------------
    n = m = 1000;
    int cnt = n*m;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++){
            matrix[i][j] = --cnt;
        }
    }
    //!--------------------------------
    */

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++){
            matrix[i][j]++;

            if (matrix[i][j] > matrix[i-1][j]) {
                upGood[i][j] = upGood[i-1][j]+1;
                if (matrix[i][j] > matrix[i][j-1])
                    upBest[i][j] = upBest[i-1][j]+1;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++){
            int how = upBest[i][j] ;
            if ( matrix[i-how][j] > matrix[i-how][j-1] ) upBest[i][j]++;
        }
    }

    for (i = 1; i <= n; i++) {
        while(!S.empty()) S.pop();
        S.push( mp(0,-1) );
        for (j = 1; j <= m; j++) auxL[j] = addStack(j,upBest[i][j])+1;

        while(!S.empty()) S.pop();
        S.push( mp(m+1,-1) );
        for (j = m; j >= 1; j--) auxR[j] = addStack(j,upBest[i][j])-1;

        for (j = 1; j <= m; j++) {
            int lf = auxL[j];
            int rh = auxR[j];
            int h  = upBest[i][j];

            ans = max( ans , (rh-lf+1)*h );
            ans = max( ans , (int) upGood[i][j] );

            h = min( h , (int) upGood[i][lf-1] + 1 );
            if(lf != 1) ans = max( ans , (rh-lf+2)*h );
        }
    }

    fout << ans;

    return 0;
}
