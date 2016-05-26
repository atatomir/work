#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

template <typename T>
using Matrix = vector<vector<T>>;

template <typename T>
void MakeParents(int n, int root, Matrix<T>& edges, function<int&(T&)> alias, vector<int>& heights) {
    heights = vector<int>(n, 0);
 
    vector<bool> visited(edges.size(), false);
    function<void(int)> Dfs;
    Dfs = [&](int nod) {
        T parent;
        bool found_parent = false;
        
        visited[nod] = true;
        while(not edges[nod].empty()) {
            auto& child = alias(edges[nod].back());
            if (visited[child]) {
                found_parent = true;
                parent = edges[nod].back();
            } else {
                heights[child] = heights[nod] + 1;
                Dfs(child); 
            }
            edges[nod].pop_back();
        }

        if (found_parent) {
            edges[nod].push_back(parent);
        }
    };
    Dfs(root);
}

vector<int> Solve(int n, Matrix<pair<int, char>> parent, vector<pair<int, int>> queries) {
    int root = 0;
    vector<int> heights;
    MakeParents<pair<int, char>>(n, root, parent,
            [](pair<int, char>& a) -> int& { return a.first; }, heights);
    
    for (auto& itr : queries) {
        if (heights[itr.first] > heights[itr.second]) {
            swap(itr.first, itr.second);
        }
    }

    unordered_map<string, int> counter;
    parent[root].push_back({-1, ' '});

    for (int i = 0; i < n; i += 1) {
        string current_word = "";
        int nod = i;
        while (parent[nod].front().first != -1) {
            current_word += parent[nod].front().second;
            counter[current_word] += 1;
            nod = parent[nod].front().first;
        }
    }

    vector<int> result;

    for (auto itr : queries) {
        string current_word = "";
        int nod = itr.second;
        while (nod != itr.first) {
            current_word += parent[nod].front().second;
            nod = parent[nod].front().first;
        }

        result.push_back(counter[current_word]);
    }

    return result;
}

int main() {
    int n, m; cin >> n >> m;
    Matrix<pair<int, char>> edges(n);
    for (int i = 1; i < n; i += 1) {
        int a, b; char c;
        cin >> a >> b >> c;
        a -= 1;
        b -= 1;
        edges[a].push_back({b, c});
        edges[b].push_back({a, c});
    }
    
    vector<pair<int, int>> queries(m);
    for (int i = 0; i < m; i += 1) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].first -= 1;
        queries[i].second -= 1;
    }

    auto result = Solve(n, edges, queries);
    for (auto itr : result) {
        cout << itr << '\n';
    }
    return 0;
}
