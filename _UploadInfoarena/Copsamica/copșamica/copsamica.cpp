#include <bits/stdc++.h>
using namespace std;
#define VI vector<int>
#define PII pair<int, int>
#define f first
#define s second
#define mp make_pair
const int MAXVAL = 20000 + 1;
vector<bool> isPairCount(1000 * 1000 + 1, 0);
vector<int> dad;

int father(int node) {
    if(dad[node] == node)
        return node;
    return dad[node] = father(dad[node]);
}

void unite(int a, int b) {
    dad[a] = dad[b];
}

vector<pair<PII, int>> solve(vector<VI> &C) {
    
    vector<vector<PII>> order(MAXVAL, vector<PII>());
    int n = C.size();

    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            order[C[i][j]].push_back(mp(i, j));

    dad = vector<int> (n, -1);
    for(int i = 0; i < n; ++i)
        dad[i] = i;
    
    vector<VI> G(n, VI());
    int counter = 0;
    
    for(int value = MAXVAL - 1; value >= 0; --value) {
        for(auto edge : order[value]) {
            int fa = father(edge.f), fb = father(edge.s);
            if(fa != fb && G[edge.f].size() < 2 && G[edge.s].size() < 2) {
                unite(fa, fb);
                G[edge.f].push_back(edge.s);
                G[edge.s].push_back(edge.f);
                counter++;
            }
            if(counter == n - 1)
                break;
        }

        if(counter == n - 1)
            break;
    } 

    vector<pair<PII, int>> answer;

    for(int i = 0; i < n; ++i)
        for(auto temp : G[i])
            if(i < temp)
                answer.push_back(mp(mp(i, temp), C[i][temp]));

    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            if((int) G[i].size() == 1 && (int) G[j].size() == 1) {
                answer.push_back(mp(mp(i, j), 0));
                return answer;
            }

    return answer;
}

int main() {
    ifstream cin("copsamica.in");
    ofstream cout("copsamica.out");

    int t; cin >> t;
    
    for(;t--;) {
        int n; cin >> n;
        vector<VI> cap(n, VI(n, 0));

        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                cin >> cap[i][j];
                cap[j][i] = cap[i][j];
            }
        
       vector<pair<PII, int>> solution = solve(cap);

        if(solution[0].f.f == -1)
            cout << 0 << "\n";
        else {
            for(auto edge : solution) {
                cout << edge.f.f + 1 << " " << edge.f.s + 1 << " " << edge.s << "\n";
            }
        }
    }
}
