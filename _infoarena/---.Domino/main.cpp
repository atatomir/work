#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define mp make_pair
#define dir first
#define rev second
#define v1 first
#define v2 second

long n,i,x,y;
vector<long> list[15];
vector<pair<long,long> > G;
long neigh[15];
vector<long> diff;

vector<long> dom[10][10];

vector<long> ans;

void DFS(long nod){
    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i];
        long rez = newNod;
        if(G[newNod].v1 == -1) {
            list[nod][i] = list[nod][list[nod].size()-1];
            list[nod].pop_back(); i--;
            continue;
        }
        if(nod == G[newNod].v1) newNod = G[newNod].v2;
        else newNod = G[newNod].v1;

        G[rez].v1 = -1;
        list[nod][i] = list[nod][list[nod].size()-1];
        list[nod].pop_back(); i--;
        DFS(newNod);
    }
    if(nod != 10) ans.push_back(nod);
}

int main()
{
    freopen("domino.in","r",stdin);
    freopen("domino.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&x,&y);
        G.push_back(mp(x,y));
        list[x].push_back(i-1); neigh[x]++;
        list[y].push_back(i-1);  neigh[y]++;

        dom[x][y].push_back(i);
    }

    for(i=0;i<10;i++){
        if(neigh[i] & 1){
            diff.push_back(i);
        }
    }

    if(diff.size() != 0 && diff.size() != 2){
        printf("0");
        return 0;
    }

    if(diff.size()){
        long x1 = diff[0],x2=diff[1];
        G.push_back(mp(x1,10));
        list[x1].push_back(n);  neigh[x1]++;
        list[10].push_back(n);  neigh[10]++;
        G.push_back(mp(x2,10));
        list[x2].push_back(n+1);   neigh[x2]++;
        list[10].push_back(n+1);  neigh[10]++;

        DFS(10);
    } else {
        for(i=0;i<10;i++)
            if(neigh[i]){
                DFS(i);
                break;
            }
    }

    if(ans.size() != n+1){
        printf("0");
    } else {
        printf("1\n");
        for(i=0;i<n;i++){
            long x1 = ans[i],x2=ans[i+1];
            long dim = dom[x1][x2].size();
            if(dim){
                printf("%ld 0\n",dom[x1][x2][dim-1]);
                dom[x1][x2].pop_back();
            } else {
                dim = dom[x2][x1].size();
                printf("%ld 1\n",dom[x2][x1][dim-1]);
                dom[x2][x1].pop_back();
            }
        }
    }

    return 0;
}
