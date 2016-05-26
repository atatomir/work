#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <string>
#include <map>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

#define MaxN 2100
#define INF 0x3f3f3f3f

struct Edge {
    int v, cost;

    Edge(int v, int cost) {
        this->v = v;
        this->cost = cost;
    }

    bool operator<(const Edge &e) const {
        return make_pair(cost, v) < make_pair(e.cost, e.v);
    }
};

int N, M;
vector<Edge> vec[MaxN];
int bestCycle[MaxN];
int subTree[MaxN];
int parent[MaxN];
int minEdge[MaxN]; //minimum cost edge for each node

void ReadInput() {
    scanf("%d %d", &N, &M);
    memset(minEdge, 0x3f, 4 * N);
    for (int i = 0; i < M; i++) {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);
        x--; y--;
        vec[x].push_back(Edge(y, c));
        vec[y].push_back(Edge(x, c));
        minEdge[x] = min(minEdge[x], c);
        minEdge[y] = min(minEdge[y], c);
    }
}

struct CostManager {
    int sizeHeap;
    int cost[MaxN];
    int poz[MaxN];
    pair<int, int> heap[MaxN];

    CostManager(int N, int source) {
        for (int i = 0; i < N; i++) {
            cost[i] = INF;
            heap[i + 1] = make_pair(cost[i], i);
            updatePoz(i + 1);
        }
        sizeHeap = N;
        heap[sizeHeap + 1].first = INF;
        relax(source, 0);
    }

    int get(int index) const {
        return cost[index];
    }

    void updatePoz(int hIndex) {
        poz[heap[hIndex].second] = hIndex;
    }

    void swapHeap(int a, int b) {
        swap(heap[a], heap[b]);
        updatePoz(a);
        updatePoz(b);
    }
	
    void relax(int index, int value) {
        int curPoz = poz[index];
        cost[index] = value;
        heap[curPoz].first = value;
        while (curPoz > 1 && heap[curPoz].first < heap[curPoz / 2].first) {
            swapHeap(curPoz, curPoz / 2);
            curPoz /= 2;
        }
    }

    pair<int, int> popMin() {
        pair<int, int> rez = make_pair(heap[1].second, heap[1].first); //TODO: change
        int curPoz = 1;
        swapHeap(1, sizeHeap);
        heap[sizeHeap--].first = INF;
        while (2 * curPoz <= sizeHeap) {
            int leftSon = 2 * curPoz;
            int rightSon = 2 * curPoz + 1;
            if (heap[leftSon].first < heap[curPoz].first || heap[rightSon].first < heap[curPoz].first) {
                if (heap[leftSon] < heap[rightSon]) {
                    swapHeap(curPoz, leftSon);
                    curPoz = leftSon;
                } else {
                   swapHeap(curPoz, rightSon);
                   curPoz = rightSon;
                }
            } else {
               break;
            }
        }
        return rez;
    }
};


void Expand(CostManager &costManager, int source, int node, int curCost) {
    if (curCost + minEdge[node] >= bestCycle[source]) {
        return;
    }
    for (int i = 0; i < (int)vec[node].size(); i++) {
        const int v = vec[node][i].v;
        const int costEdge = vec[node][i].cost;
        const int curCostV = costManager.get(v);

        //Incearca intai sa formezi un ciclu
        //Trateza si cazul in care ne legam direct de radacina, care se rezolva automat
        if (parent[node] != v && subTree[node] != subTree[v] && curCost + curCostV + costEdge < bestCycle[source]) {
            bestCycle[source] = curCost + curCostV + costEdge;
            if (source == 6) {
                int cycleCost = Reconst(source, node) + Reconst(source, v) + GetCost(node, v);
                fprintf(stderr, "Am gasit %d %d %d %d %d %d\n", node, v, curCost, curCostV, costEdge, cycleCost);
            }
        }

        //relaxeaza toti vecinii
        if (curCost + costEdge < curCostV) {
            costManager.relax(v, curCost + costEdge);
            parent[v] = node;
            if (node == source) {
                subTree[v] = v;
            } else {
                subTree[v] = subTree[node];
            }
        }

    }
}

void Dijkstra(int source) {
    bestCycle[source] = INF;
    subTree[source] = source;
    CostManager costManager(N, source);
    for (int i = 0; i < N; i++) {
        pair<int, int> minVal = costManager.popMin();
        Expand(costManager, source, minVal.first, minVal.second);
        if (minVal.second >= bestCycle[source]) break;
    }
}

int main() {
    freopen("dbz.in", "rb", stdin);
    freopen("dbz.out", "wb", stdout);
    double start = clock();
    ReadInput();
    for (int i = 0; i < N; i++) {
        Dijkstra(i);
        printf("%d ", (bestCycle[i] != INF) ? bestCycle[i] : -1);
    }
    fprintf(stderr, "Duration: %.3f sec\n", (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
