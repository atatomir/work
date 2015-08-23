#include <iostream>
#include <cstdio>
#include <cstring>
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

int n,m,i,j,ans;
int matrix[maxN][maxN];
short expand[maxN<<1][maxN<<1];

stack< pair<int,int> > S; //! pos,val
short auxL[maxN<<1],auxR[maxN<<1];

short addStack(int pos,int val) {
    while ( val <= S.top().second ) S.pop();
    int ret = S.top().first;
    S.push( mp( pos,val ) );

    return ret;
}

int main()
{
    Buffer fin("jmenoasa.in",1<<20);
    freopen("jmenoasa.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++){
            fin >> matrix[i][j];

            expand[ i<<1 ][ j<<1 ] = expand[ (i<<1)-1 ][ (j<<1)-1 ] = 1;
            if (matrix[i][j] > matrix[i-1][j]) expand[ (i<<1)-1 ][ j<<1 ] = 1;
            if (matrix[i][j] > matrix[i][j-1]) expand[ i<<1 ][ (j<<1)-1 ] = 1;
        }
    }

    n <<= 1; m <<= 1;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (expand[i][j])
                expand[i][j] += expand[i-1][j];

    for (i = 2; i <= n; i+=2) {

        //! from left
        while(!S.empty()) S.pop();
        S.push( mp(0,-1) );
        for (j = 1; j <= m; j++) auxL[j] = addStack(j,expand[i][j]) + 1;

        //! from right
        while(!S.empty()) S.pop();
        S.push( mp(m+1,-1) );
        for (j = m; j >= 1; j--) auxR[j] = addStack(j,expand[i][j]) - 1;

        for (j = 1; j <= m; j++) {
            int le = auxL[j];
            int ri = auxR[j];
            int h  = expand[i][j];

            if ( h  % 2 == 0 ) h--;
            if ( le % 2 == 1 ) le++;
            if ( ri % 2 == 1 ) ri--;

            ans = max( ans, ((ri-le+2)*(h+1))/4  );
        }
    }

    printf("%d",ans);

    return 0;
}
