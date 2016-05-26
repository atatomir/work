/**
 * Author: Andrei Heidelbacher
 * Task: Clasament
 * Time complexity: O(N * logN + Q * logN)
 * Space complexity: O(N)
 * Expected score: 100 points
 */

#include <cstdlib>
#include <ctime>

#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const char IN_FILE[] = "clasament.in";
const char OUT_FILE[] = "clasament.out";

class Treap {
 public:
  Treap():
   treapRoot(NULL),
   nil(Node::buildSentinel()) {
    treapRoot = nil;
  }

  void insert(const int64_t key, const int value) {
    auto newRoots = split(treapRoot, key);
    auto newNode = new Node(key, value, rand(), nil, nil);
    treapRoot = merge(newRoots.first, merge(newNode, newRoots.second));
  }

  void erase(const int64_t key) {
    auto newRoots = split(treapRoot, key - 1);
    treapRoot = merge(newRoots.first, split(newRoots.second, key).second);
  }

  vector<int> getHash() const {
    auto hash = vector<int>(Node::BASE_COUNT);
    for (int i = 0; i < Node::BASE_COUNT; ++i)
      hash[i] = treapRoot->hash[i];
    return hash;
  }

 private:
  class Node {
   public:
    static const int NIL_PRIORITY = -1;
    static const int BASE_COUNT = 2;
    static const int BASE[BASE_COUNT];
    static const int MOD = 1000000007;

    int64_t key;
    int value, priority, size;
    Node *left, *right;
    int hash[BASE_COUNT];

    Node(const int64_t _key, const int _value, const int _priority, Node *_left, Node *_right):
     key(_key),
     value(_value),
     priority(_priority),
     size(1),
     left(_left),
     right(_right) {
      update();
    }

    void update() {
      if (priority == NIL_PRIORITY)
        return;
      size = 0;
      for (int i = 0; i < BASE_COUNT; ++i)
        hash[i] = 0;
      if (left != NULL) {
        size += left->size;
        for (int i = 0; i < BASE_COUNT; ++i)
          hash[i] = left->hash[i];
      }
      ++size;
      for (int i = 0; i < BASE_COUNT; ++i)
        hash[i] = (1LL * hash[i] * BASE[i] + value) % MOD;
      if (right != NULL) {
        size += right->size;
        for (int i = 0; i < BASE_COUNT; ++i)
          hash[i] = (1LL * hash[i] * basePow(i, right->size) + right->hash[i]) % MOD;
      }
    }

    static Node *buildSentinel() {
      Node *sentinel = new Node(0, 0, NIL_PRIORITY, NULL, NULL);
      sentinel->size = 0;
      for (int i = 0; i < BASE_COUNT; ++i)
        sentinel->hash[i] = 0;
      sentinel->left = sentinel->right = sentinel;
      return sentinel;
    }

   private:
    static int basePow(const int i, const int p) {
      static vector<int> BASE_POW[BASE_COUNT];
      if (BASE_POW[i].empty())
        BASE_POW[i].push_back(1);
      while (int(BASE_POW[i].size()) <= p)
        BASE_POW[i].push_back((1LL * BASE_POW[i].back() * BASE[i]) % MOD);
      return BASE_POW[i][p];
    }
  };

  Node *treapRoot, *nil;

  Node *merge(Node *left, Node *right) {
    if (left == nil && right == nil)
      return nil;
    if (left->priority < right->priority) {
      right->left = merge(left, right->left);
      right->update();
      return right;
    } else {
      left->right = merge(left->right, right);
      left->update();
      return left;
    }
  }

  pair<Node*, Node*> split(Node *root, const int64_t key) {
    if (root == nil)
      return make_pair(nil, nil);
    if (root->key <= key) {
      auto partialSplit = split(root->right, key);
      root->right = partialSplit.first;
      root->update();
      return make_pair(root, partialSplit.second);
    } else {
      auto partialSplit = split(root->left, key);
      root->left = partialSplit.second;
      root->update();
      return make_pair(partialSplit.first, root);
    }
  }
};

const int Treap::Node::BASE[Treap::Node::BASE_COUNT] = {100003, 666013};

int main() {
  srand(time(0));
  ifstream in(IN_FILE);
  ofstream out(OUT_FILE);
  int n, q;
  in >> n >> q;
  auto key = vector<int64_t>(n);
  auto treap = Treap();
  for (int i = 0; i < n; ++i) {
    int score, time = 0;
    in >> score;
    key[i] = 1LL * (q + 1) * score + q - time;
    treap.insert(key[i], i);
  }
  auto hashCount = multiset<vector<int>>();
  hashCount.insert(treap.getHash());
  for (int time = 1; time <= q; ++time) {
    int i, score;
    in >> i >> score;
    --i;
    treap.erase(key[i]);
    key[i] = 1LL * (q + 1) * score + q - time;
    treap.insert(key[i], i);
    out << hashCount.count(treap.getHash()) << "\n";
    hashCount.insert(treap.getHash());
  }
  return 0;
}
