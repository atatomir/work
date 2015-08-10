#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

class Buffer{
    private:
        int dim,pos;
        vector<char> Buff;

        void reFill(){
            pos = 0;
            memset(&Buff[0],0,sizeof(Buff));
            fread(&Buff[0],1,dim,stdin);
        }
        bool isDigit(char c){
            return (c>='0')&&(c<='9');
        }

    public:
        Buffer(string name,int _dim){
            freopen(name.c_str(),"r",stdin);
            Buff.resize(_dim);
            dim = _dim; reFill();
        }
        Buffer& operator>>(int &dest){
            while( !isDigit(Buff[pos]) )
                if(++pos==dim) reFill();

            dest=0;
            while( isDigit(Buff[pos]) ){
                dest = dest*10 + Buff[pos]-'0';
                if(++pos==dim) reFill();
            }
            return *this;
        }
};

#define maxN 811
#define getId(x) id[x.first][x.second]

const int defX[4]={0,0,-1,1};
const int defY[4]={-1,1,0,0};

int n,m,d,i,j,how,pos,aux;
int mat[maxN][maxN],id[maxN][maxN];
vector< pair<int,int> > Cell;

int cnt[maxN*maxN];
int dad[maxN*maxN];
bool us[maxN][maxN];
int ans[maxN][maxN];

bool cmp(const pa(int,int)& a,const pa(int,int)& b){
    return mat[a.first][a.second] < mat[b.first][b.second];
}

int Find(int node){
    if(dad[node]==node) return node;
    dad[node] = Find(dad[node]);
    return dad[node];
}
void Merge(int R1,int R2){
    R1 = Find(R1); R2 = Find(R2);
    if(R1!=R2){
        cnt[R1] += cnt[R2];
        dad[R2] = dad[R1];
    }
}

/*int getId(pa(int,int) act){
    return id[act.first][act.second];
}*/
void addElem(int pos){
    pair<int,int> act = Cell[pos],tmp;
    int actId = getId(act),daddy=Find(actId);
    us[act.first][act.second]=true;

    for(int i=0;i<4;i++){
        tmp = act;
        tmp.first += defX[i]; tmp.second += defY[i];

        if(!us[tmp.first][tmp.second]) continue;
        Merge( daddy , getId(tmp) );
    }
}

int main()
{
    Buffer fin("mexc.in",1<<20);
    freopen("mexc.out","w",stdout);

    fin >> n >> m >> d;
    fordef(i,1,n){
        fordef(j,1,m){
            fin >> mat[i][j];
            Cell.pb(mp(i,j));
        }
    }
    sort(Cell.begin(),Cell.end(),cmp);

    fordef(i,1,n)
        fordef(j,1,m)
            id[i][j] = ++how;
    fordef(i,1,how) dad[i] = i;

    j = how-1;
    for(i=how-1;i>=0;i--){
        pos = i;
        while(pos>0 && mat[ Cell[i].first ][ Cell[i].second ] == mat[ Cell[pos-1].first ][ Cell[pos-1].second ])
            if(--pos==0) break;

        fordef(aux,pos,i) cnt[ Find( getId(Cell[aux]) ) ]++;
        if(j>=0)
        while(j>=0 && mat[ Cell[j].first ][ Cell[j].second ] >= mat[ Cell[i].first ][ Cell[i].second ]-d ){
            addElem(j--);
            if(j==-1) break;
        }

        fordef(aux,pos,i){
            int R = Find( getId(Cell[aux]) );
            ans[Cell[aux].first][Cell[aux].second] =  cnt[R];
        }
        i = pos;
    }

    fordef(i,1,n){
        fordef(j,1,m)
            printf("%d ",ans[i][j]);
        printf("\n");
    }

    return 0;
}
