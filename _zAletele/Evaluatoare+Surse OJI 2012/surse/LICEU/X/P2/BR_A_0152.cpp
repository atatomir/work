#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

bool P[53][53];
bool B[53][53];
int T[53][53];
int p = 0;
int n;

bool cond(int x, int y) {
    if(x<1||y<1||x>n+1||y>n+1) return false;
    return !P[x][y];
}

void fill(int x, int y) {
    if(x<1||y<1||x>n+1||y>n+1) return;
    if(!P[x][y]) return;
    if(B[x][y]) return;
    if(P[x+1][y+1]) p++;
    B[x][y] = true;
    fill(x+1,y);
    fill(x-1,y);
    fill(x,y+1);
    fill(x,y-1);
}

void resolve(int x, int y) {
    queue<int> q;
    int x0 = x, y0 = y;
    q.push((n+2)*x+y);
    while(!q.empty()) {
        x = q.front()/(n+2);
        y = q.front()%(n+2);
        q.pop();
        P[x][y] = true;
        if(cond(x+1,y)) q.push((n+2)*(x+1)+y);
        if(cond(x-1,y)) q.push((n+2)*(x-1)+y);
        if(cond(x,y+1)) q.push((n+2)*x+y+1);
        if(cond(x,y-1)) q.push((n+2)*x+y-1);
    }
    fill(x0,y0);
}

int main()
{
    ifstream fin("zona.in");
    ofstream fout("zona.out");
    int x,y,l;
    int ps[2502];
    fin>>x>>y>>n>>l;
    for(int i=1;i<=n+1;i++) {
        for(int j=1;j<=n+1;j++) {
            P[i][j] = false;
            B[i][j] = false;
            T[i][j] = -1;
        }
    }
    int x1 = x, y1 = y;
    P[x][y] = true;
    T[x][y] = 0;
    int k;
    bool start;
    for(int i=1;i<=l;i++) {
        fin>>ps[i];
        int x0 = x, y0 = y;
        switch(ps[i]) {
            case 1: x--; break;
            case 3: x++; break;
            case 2: y++; break;
            case 4: y--; break;
        }
        if(T[x][y]==-1) T[x][y] = T[x0][y0]+1;
        if(P[x][y]) start = false;
        else start = true;
        P[x][y] = true;
    }
    do {
        if(!start) break;
        switch(ps[l]) {
            case 1: x--; break;
            case 3: x++; break;
            case 2: y++; break;
            case 4: y--; break;
        }
        P[x][y] = true;
    } while(!P[x][y]);
    int f = T[x][y];
    int index = 0;
    while(f!=T[x1][y1]) {
        P[x1][y1] = false;
        switch(ps[++index]) {
            case 1: x1--; break;
            case 3: x1++; break;
            case 2: y1++; break;
            case 4: y1--; break;
        }
    }
    resolve(x,y);
    fout<<l-T[x][y]<<endl;
    fout<<p;
    return 0;
}
