#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

ifstream in("cartite.in");
ofstream out("cartite.out");
int p, m, n, g, k;
int cx, cy;
int rx, ry;

short mat[102][102];

void init();
void first();
void second(int x, bool show);

struct node {
    vector<int> a;
};

vector<node> gr;

vector< pair<int, int> > verif;

int main()
{
    in>>p;
    init();
    if(p==1) first();
    else {
        second(rx*(n+1)+ry,0);
        second(rx*(n+1)+ry,1);
    }
    return 0;
}

void init() {
    in>>m>>n;

    for(int i=0;i<=m+1;i++)
        for(int j=0;j<=n+1;j++) {
            if(i==0||j==0||i==m+1||j==n+1) {mat[i][j]=-1;continue;}
            mat[i][j] = 0;
        }

    in>>cx>>cy;
    in>>k;
    for(int i=1;i<=k;i++) {
        int x,y,r;
        in>>x>>y>>r;
        switch(r) {
            case 0: mat[x][y] = 1; break;
            case 1: mat[x][y] = 1;
                    mat[x-1][y] = 1;
                    mat[x+1][y] = 1;
                    mat[x][y-1] = 1;
                    mat[x][y+1] = 1;
                    break;
            case 2: mat[x][y] = 1;
                    mat[x-1][y] = 1;
                    mat[x+1][y] = 1;
                    mat[x][y-1] = 1;
                    mat[x][y+1] = 1;
                    mat[x-2][y] = 1;
                    mat[x+2][y] = 1;
                    mat[x][y-2] = 1;
                    mat[x][y+2] = 1;
                    mat[x+1][y+1] = 1;
                    mat[x-1][y+1] = 1;
                    mat[x+1][y-1] = 1;
                    mat[x-1][y-1] = 1;
                    break;
        }
    }

    in>>g;
    node temp;
    gr.resize(m*(n+1), temp);
    for(int i=1;i<=g;i++) {
        int a,b,c,d;
        in>>a>>b>>c>>d;
        int x = a*(n+1)+b;
        int y = c*(n+1)+d;
        verif.push_back(make_pair(x,y));

        gr[x].a.push_back(y);
        gr[y].a.push_back(x);
        rx = a;
        ry = b;

        if(mat[a][b]==0) mat[a][b] = 2;
        if(mat[c][d]==0) mat[c][d] = 2;
    }
}

bool check(int x, int y) {
    if(mat[x][y]==-1||mat[x][y]==1) return false;
    return true;
}

void first() {
    queue< pair<int,int> > q;
    queue<int> v;
    q.push(make_pair(cx,cy));
    v.push(0);

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        int c = v.front();
        q.pop();
        v.pop();

        if(mat[x][y]==2) {
            out<<x<<" "<<y<<" "<<c<<'\n';
            break;
        }

        if(check(x-1,y)) {
            q.push(make_pair(x-1,y));
            v.push(c+1);
        }
        if(check(x+1,y)) {
            q.push(make_pair(x+1,y));
            v.push(c+1);
        }
        if(check(x,y+1)) {
            q.push(make_pair(x,y+1));
            v.push(c+1);
        }
        if(check(x,y-1)) {
            q.push(make_pair(x,y-1));
            v.push(c+1);
        }
    }
}

bool check2(int a, int b) {
    for(vector< pair<int,int> >::iterator i=verif.begin();i!=verif.end();i++) {
        if(((*i).first==a&&(*i).second==b)||((*i).first==b&&(*i).second==a)) {
            verif.erase(i);
            return true;
        }
    }
    return false;
}

void second(int x, bool show) {
    for(int i=0;i<(int)gr[x].a.size();i++) {
        if(check2(x, gr[x].a[i])) {
            second(gr[x].a[i],0);
            out<<gr[x].a[i]/(n+1)<<" "<<gr[x].a[i]%(n+1)<<endl;
            break;
        }
    }
    if(show) out<<x/(n+1)<<" "<<x%(n+1)<<endl;
}
