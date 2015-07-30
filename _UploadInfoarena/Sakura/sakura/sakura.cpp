/**
 * Author: Andrei Heidelbacher
 * Expected score: 100 points
 */

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const char IN_FILE[] = "sakura.in";
const char OUT_FILE[] = "sakura.out";

class Graph {
  public:
    static const int NIL = -1;

    Graph(const int _V = 0):
      V(_V),
      G(vector< vector<int> >(V, vector<int>())) {}

    int getSize() const {
        return V;
    }

    vector<int> getAdjacent(const int x) const {
        return G[x];
    }

    void addEdge(const int x, const int y) {
        G[x].push_back(y);
        G[y].push_back(x);
    }

  protected:
    int V;
    vector< vector<int> > G;
};

class BipartiteGraph: public Graph {
  public:
    BipartiteGraph(const int _left, const int _right):
      Graph(_left + _right),
      left(_left),
      right(_right) {}

    int getLeftSize() const {
        return left;
    }

    int getRightSize() const {
        return right;
    }

    int maximumMatching() {
        vector<int> pairs = vector<int>(V, NIL);
        for (int change = 1; change != 0; ) {
            change = 0;
            vector<bool> used = vector<bool>(left, false);
            for (int x = 0; x < left; ++x)
                if (pairs[x] == NIL)
                    change |= pairUp(x, pairs, used);
        }
        int matchSize = 0;
        for (int x = 0; x < left; ++x)
            if (pairs[x] != NIL)
                ++matchSize;
        return matchSize;
    }

    bool perfectMatching() {
        return maximumMatching() == min(left, right);
    }

  private:
    int left, right;

    bool pairUp(const int x, vector<int> &pairs, vector<bool> &used) {
        if (used[x])
            return false;
        used[x] = true;
        for (const auto &y: G[x]) {
            if (pairs[y] == NIL || pairUp(pairs[y], pairs, used)) {
                pairs[x] = y;
                pairs[y] = x;
                return true;
            }
        }
        return false;
    }
};

class Tree: public Graph {
  public:
    Tree(const int _V, const int _root, const vector< pair<int, int> > &edges):
      Graph(_V),
      root(_root),
      father(vector<int>(_V, NIL)),
      size(vector<int>(_V, 1)),
      depth(vector<int>(_V, 0)) {
        for (const auto &e: edges)
            addEdge(e.first, e.second);
        DFS(root);
    }

    int getRoot() const {
        return root;
    }

    int getSubtreeSize(const int x) const {
        return size[x];
    }

    vector<int> getSons(const int x) const {
        vector<int> sons;
        for (const auto &y: G[x])
            if (y != father[x])
                sons.push_back(y);
        return sons;
    }

    vector< vector<int> > getLayeredNodes() const {
        int maxDepth = 0;
        for (int x = 0; x < V; ++x)
            maxDepth = max(maxDepth, depth[x]);
        vector< vector<int> > nodes = vector< vector<int> >(maxDepth + 1, vector<int>());
        for (int x = 0; x < V; ++x)
            nodes[depth[x]].push_back(x);
        return nodes;
    }

  private:
    int root;
    vector<int> father, size, depth;

    void DFS(const int x) {
        size[x] = 1;
        for (const auto &y: G[x]) {
            if (y != father[x]) {
                father[y] = x;
                depth[y] = depth[x] + 1;
                DFS(y);
                size[x] += size[y];
            }
        }
    }
};

bool ApproximatelyIsomorphic(Tree &A, Tree &B) {
    vector< vector<bool> > isomorphic = vector< vector<bool> >(A.getSize(), vector<bool>(B.getSize(), false));
    vector< vector<int> > nodesA = A.getLayeredNodes(), nodesB = B.getLayeredNodes();
    for (int depth = min(nodesA.size(), nodesB.size()) - 1; depth >= 0; --depth) {
        for (const auto &x: nodesA[depth]) {
            for (const auto &y: nodesB[depth]) {
                if (B.getSubtreeSize(y) == 1) {
                    isomorphic[x][y] = true;
                    continue;
                }
                if (A.getSubtreeSize(x) < B.getSubtreeSize(y) || int(A.getAdjacent(x).size()) < int(B.getAdjacent(y).size())) {
                    isomorphic[x][y] = false;
                    continue;
                }
                vector<int> left = A.getSons(x), right = B.getSons(y);
                BipartiteGraph graph = BipartiteGraph(int(left.size()), int(right.size()));
                for (int i = 0; i < int(left.size()); ++i)
                    for (int j = 0; j < int(right.size()); ++j)
                        if (isomorphic[left[i]][right[j]])
                            graph.addEdge(i, j + int(left.size()));
                isomorphic[x][y] = graph.perfectMatching();
            }
        }
    }
    return isomorphic[A.getRoot()][B.getRoot()];
}

Tree ReadTree(ifstream &in) {
    int v;
    in >> v;
    vector< pair<int, int> > edges = vector< pair<int, int> >(v - 1);
    for (int i = 0; i < v - 1; ++i)
        in >> edges[i].first >> edges[i].second;
    return Tree(v, 0, edges);
}

int main() {
    ifstream in(IN_FILE);
    ofstream out(OUT_FILE);
    int tests;
    in >> tests;
    for (; tests > 0; --tests) {
        Tree A = ReadTree(in);
        Tree B = ReadTree(in);
        int answer = -1;
        if (ApproximatelyIsomorphic(A, B))
            answer = A.getSize() - B.getSize();
        out << answer << "\n";
    }
    in.close();
    out.close();
    return 0;
}
