#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

#define MaxN 100100
#define MaxQ 20100

#define MaxTime 9.500 //max time in seconds
double startTime = clock();

bool ShouldStop() {
    return clock() - startTime >= MaxTime * CLOCKS_PER_SEC;
}

struct Edge {
    int v, cost;
    Edge(const int a, const int b) {
        v = a;
        cost = b;
    }

    bool operator<(const Edge &e) const {
        return cost < e.cost;
    }
};

int N, M, nrQ;
vector<Edge> vec[MaxN];
vector<pair<int, int>> queryies;
vector<int> solutions[MaxQ];
int bestCurSolution[MaxQ];
int minCost[MaxN];
pair<int, int> t[MaxN];
bool mark[MaxN];

void ReadInput(const char *fileName) {
    FILE *input = fopen(fileName, "rb");
    fscanf(input, "%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int x, y, c;
        fscanf(input, "%d %d %d", &x, &y, &c);
        vec[x].push_back(Edge(y, c));
        vec[y].push_back(Edge(x, c));
    }
    for (int i = 0; i < N; i++) {
        sort(vec[i].begin(), vec[i].end());
    }
    fscanf(input, "%d", &nrQ);
    queryies.resize(nrQ);
    for (int i = 0; i < nrQ; i++) {
        fscanf(input, "%d %d", &queryies[i].first, &queryies[i].second);
    }
}

#define MaxQS MaxN
int st, fn;
int q[MaxQS];

int IncremCounter(int &poz) {
    poz++;
    if (poz == MaxQS) {
        poz = 0;
    }
    return poz;
}

void UpdateCost(int node, int prev, int newCost) {
    minCost[node] = newCost;
    t[node] = make_pair(prev, t[prev].second + 1);
    if (!mark[node]) {
        mark[node] = true;
        q[fn] = node;
        IncremCounter(fn);
    }
}

void Expand(const int node) {
    const int curCost = minCost[node];
    for (int i = 0; i < (int)vec[node].size(); i++) {
        if (curCost + vec[node][i].cost < minCost[vec[node][i].v]) {
            UpdateCost(vec[node][i].v, node, curCost + vec[node][i].cost);
        }
    }
    mark[node] = false;
}

void BFord(int start) {
    double startTime = clock();
    memset(mark, 0, N);
    memset(minCost, 0x3f, 4 * N);
    st = fn = 0;
    t[start] = make_pair(0, 0);
    UpdateCost(start, start, 0);
    int nr = 0;
    while (st != fn) {
        nr++;
        Expand(q[st]);
        IncremCounter(st);
    }
    fprintf(stderr, "Med: %.3f\n", (nr / (double)N));
    fprintf(stderr, "Durata single query: %.3f sec\n", (clock() - startTime) / CLOCKS_PER_SEC);
}

vector<int> nodesSrc, nodesDest;

void RecordTransition(int &x, vector<int> &nodes) {
    nodes.push_back(x);
    x = t[x].first;
}

int CostOnCurrentTree(int x, int y, bool doPrint = false) {
    if (minCost[x] == 0x3f3f3f3f || minCost[y] == 0x3f3f3f3f) {
        return 0x3f3f3f3f;
    }
    const int oldCost = minCost[x] + minCost[y];
    while (t[x].second > t[y].second) {
        RecordTransition(x, nodesSrc);
    }
    while (t[y].second > t[x].second) {
        RecordTransition(y, nodesDest);
    }
    while (x != y) {
        RecordTransition(x, nodesSrc);
        RecordTransition(y, nodesDest);
    }
    nodesSrc.push_back(x);
    return oldCost - 2 * minCost[x];
}

void ImproveCosts(const int startNode) {
    BFord(startNode);
    for (int i = 0; i < nrQ; i++) {
        nodesSrc.clear();
        nodesDest.clear();
        const int newCost = CostOnCurrentTree(queryies[i].first, queryies[i].second);
        if (newCost < bestCurSolution[i]) {
            bestCurSolution[i] = newCost;
            solutions[i] = nodesSrc;
            reverse(nodesDest.begin(), nodesDest.end());
            solutions[i].insert(solutions[i].end(), nodesDest.begin(), nodesDest.end());
        }
    }
}

int main() {
    ReadInput("nolife.in");
    memset(bestCurSolution, 0x3f, sizeof(bestCurSolution));
    int curQuery = 0;
    while (curQuery < nrQ && !ShouldStop()) {
        ImproveCosts(queryies[curQuery++].first);
    }
    fprintf(stderr, "Done %d paths\n", curQuery);
    FILE *output = fopen("nolife.out", "wb");
    for (int query = 0; query < nrQ; query++) {
        fprintf(output, "%d ", solutions[query].size());
        for (int i = 0; i < (int)solutions[query].size(); i++) {
            fprintf(output, "%d ", solutions[query][i]);
        }
        fprintf(output, "\n");
    }
    fclose(output);
}
