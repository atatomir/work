#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define x first
#define y second
#define maxN 511
#define maxM 5011

typedef pair<long,long> Comb;

long n,m,i,j;
vector<Comb> G;
vector<long> start[maxN];
vector<long> list[maxM];
long inCount[maxM];

bool keinProblem;
vector<long> Ans;

stack<long> S;

void addAns(long x,long y){
    if(Ans[Ans.size()-1] != y && y != -1) Ans.push_back(y);
    Ans.push_back(x);
}

void Euler(long node){
    S.push(node);

    while(!S.empty()){
        node = S.top();
        if(list[node].size()){
            long newNode = list[node][0];
            list[node][0] = list[node][list[node].size()-1];
            list[node].pop_back(); i--;
            S.push(newNode);
            continue;
        }
        addAns(G[node].x,G[node].y);
        S.pop();
    }

    /*for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];

        list[node][i] = list[node][list[node].size()-1];
        list[node].pop_back(); i--;
        Euler(newNode);
    }

    addAns(G[node].x,G[node].y);*/
}

int main()
{
    freopen("tester.in","r",stdin);
    freopen("tester.out","w",stdout);

    scanf("%ld %ld",&n,&m);

    G.resize(m);
    for(i=0;i<m;i++){
        scanf("%ld %ld",&G[i].x,&G[i].y);
        start[G[i].x].push_back(i);
    }

    for(i=0;i<m;i++){
        for(j=0;j<start[G[i].y].size();j++){
            list[i].push_back(start[G[i].y][j]);
            inCount[start[G[i].y][j]]++;
        }
    }

    G.push_back(make_pair(-1,-1));
    keinProblem = true;
    for(i=0;i<m;i++){
        if(list[i].size() == inCount[i]) continue;
        keinProblem = false;
        while(list[i].size() < inCount[i]) list[i].push_back(m);
        while(list[i].size() > inCount[i]) {
            list[m].push_back(i);
            inCount[i]++;
        }
    }

    Ans.push_back(-1);
    if(!keinProblem) Euler(m);
    for(i=0;i<m;i++){
        if(!list[i].size()) continue;
        Ans.push_back(-1);
        Euler(i);
    }

    long bg;
    for(bg=1;bg<Ans.size() && Ans[bg] == -1;bg++);
    long en;
    for(en=Ans.size()-1;en>=0 && Ans[en] == -1;en--);
    for(i=en;i>=bg;i--){
        if(Ans[i] == Ans[i-1] && Ans[i] == -1) continue;
        if(Ans[i] == -1) printf("R "); else
        printf("%ld ",Ans[i]);
    }

    return 0;
}
