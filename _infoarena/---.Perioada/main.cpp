#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class SuffixArrays{
    private:
        struct Triple{
            long x,y,id;
            bool operator<(const Triple& who) const{
                if(x==who.x) return y<who.y;
                return x < who.x;
            }
        };
        vector<vector<long> > pr;

    public:
        SuffixArrays(const string& S){
            long log=0; while(1<<(log+1) <= S.size()) log++; log++;
            pr = vector<vector<long> >(log,vector<long>(S.size()));

            long i,j;
            for(i=0;i<S.size();i++) pr[0][i] = S[i]-'a';

            vector<Triple> T(S.size());
            for(i=1;i<pr.size();i++){
                for(j=0;j<S.size();j++){
                    if(j+(1<<(i-1)) < S.size())
                        T[j] = {pr[i-1][j],pr[i-1][j+(1<<(i-1))],j};
                    else
                        T[j] = {pr[i-1][j],-1,j};
                }
                sort(T.begin(),T.end());


                for(j=0;j<T.size();j++){
                    if(j==0 || T[j-1]<T[j])
                        pr[i][T[j].id] = j;
                    else
                        pr[i][T[j].id] = pr[i][T[j-1].id];
                }
            }
        }

        long lcp(long s1,long s2){
            long Ans = 0;
            for(long i=pr.size()-1;i>=0;i--){
                if(pr[i][s1]==pr[i][s2]){
                    Ans += (1<<i);
                    s1  += (1<<i);
                    s2  += (1<<i);
                }
            }
            return Ans;
        }

};

long n,m,i,x,y,ans;
string S;

int main()
{
    ifstream cin("perioada.in");
    ofstream cout("perioada.out");

    cin >> n; cin >> S;
    SuffixArrays Sa(S);

    cin >> m;
    for(;m;m--){
        cin >> x >> y; ans=0; x--; y--;
        long L = y-x+1;
        for(i=1;i*i<=L;i++){
            if(L%i != 0) continue;
            if(Sa.lcp(x,x+i) >= L-i)
                ans++;

            if(i==1 || i*i==L) continue;
            if(Sa.lcp(x,x+(L/i)) >= L-(L/i))
                ans++;
        }

        cout << ans << '\n';
    }



    return 0;
}
