/**
 * Author: Andrei Heidelbacher
 * Expected score: 100 points
 */

#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

const char IN_FILE[] = "reversez.in";
const char OUT_FILE[] = "reversez.out";
const int NIL = -1;
const int MOD = 666013;

int SIGMA;

inline void AddEdge(vector< vector<int> > &graph, const int from, const int to) {
    graph[from].push_back(to);
}

vector< vector<int> > BuildEquivalenceGraph(const vector<int> &lcp) {
    int n = int(lcp.size());
    vector< vector<int> > graph = vector< vector<int> >(n, vector<int>());
    int covered = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = i + lcp[i] - 1; j > covered && j >= i; --j) {
            AddEdge(graph, j - i, j);
            AddEdge(graph, j, j - i);
        }
        if (i + lcp[i] - 1 > covered)
            covered = i + lcp[i] - 1;
    }
    return graph;
}

void EquivalenceDFS(const vector< vector<int> > &graph, const int x, const int classIndex, vector<int> &classes) {
    classes[x] = classIndex;
    for (const auto &y: graph[x])
        if (classes[y] == NIL)
            EquivalenceDFS(graph, y, classIndex, classes);
}

tuple<vector<int>, int> BuildEquivalenceClasses(const vector< vector<int> > &graph) {
    vector<int> classes = vector<int>(int(graph.size()), NIL);
    int classCount = 0;
    for (int x = 0; x < int(graph.size()); ++x)
        if (classes[x] == NIL)
            EquivalenceDFS(graph, x, classCount++, classes);
    return tie(classes, classCount);
}

void CountDFS(const vector< vector<int> > &tree, const int x, const int choices, int &count) {
    count = (1LL * count * choices) % MOD;
    for (const auto &y: tree[x])
        CountDFS(tree, y, choices - 1, count);
}

int Solve(const vector<int> &lcp) {
    int stringCount = 1;
    vector<int> classes;
    int classCount;
    tie(classes, classCount) = BuildEquivalenceClasses(BuildEquivalenceGraph(lcp));
    vector< vector<int> > tree = vector< vector<int> >(classCount, vector<int>());
    vector<int> father = vector<int>(classCount, NIL);
    for (int i = 1; i < int(lcp.size()); ++i)
        if (i + lcp[i] < int(lcp.size()) && classes[lcp[i]] < classes[i + lcp[i]])
            father[classes[i + lcp[i]]] = max(father[classes[i + lcp[i]]], classes[lcp[i]]);
    for (int x = 0; x < classCount; ++x)
        if (father[x] != NIL)
            AddEdge(tree, father[x], x);
    vector<bool> visited = vector<bool>(classCount, false);
    for (int x = 0; x < classCount; ++x)
        if (father[x] == NIL)
            CountDFS(tree, x, SIGMA, stringCount);
    return stringCount;
}

vector<int> Read() {
    ifstream cin(IN_FILE);
    int n;
    cin >> n >> SIGMA;
    vector<int> lcp = vector<int>(n);
    for (int i = 0; i < n; ++i)
        cin >> lcp[i];
    lcp[0] = 0;
    cin.close();
    return lcp;
}

void Print(const int stringCount) {
    ofstream cout(OUT_FILE);
    cout << stringCount << "\n";
    cout.close();
}

int main() {
    Print(Solve(Read()));
    return 0;
}
