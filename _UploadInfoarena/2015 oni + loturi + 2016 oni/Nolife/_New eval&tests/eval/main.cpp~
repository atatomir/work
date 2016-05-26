#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;

#define newScoreType
//! comment if you want to use real score

const double MAX_UNOPTIONAL = 0.9;
const double SCORE_HALFLIFE = 0.25;

double sumResults = 0;
int nrGood = 0;
double _sumResults = 0;
int _nrGood = 0;

int N, M, nrQ;
map<pair<int, int>, int> edges;
vector<pair<int, int> > queries;
vector<int> bestSolution;
double authorPoints;

void Result(char msg[], int p)
{
    fprintf(stderr, "%s", msg);
    printf("%d", p);
    exit(0);
}

void ResultOK(){
    if(sumResults<=0.00000001) {
        fprintf(stderr, "Nu ai rezolvat niciun query...", 0);
        printf("0");
        exit(0);
    }

    double pts = 10.00 * (sumResults/_sumResults);
    double cPts = pts;
    #ifdef newScoreType
        pts = 10.00*(pts/authorPoints);
    #endif // newScoreType
    int ipts = (int)pts;

    if(pts >= 1.00*ipts+0.499999) ipts++;

    ipts = min(ipts,10);
    fprintf(stderr, "Corect / Real points : %.2lf / Evaluation points : %.2lf", cPts ,pts);
    printf("%d", ipts);
    exit(0);
}


void SetCost(int x, int y, int cost) {
    pair<int, int> p = make_pair(min(x, y), max(x, y));
    if (edges.find(p) != edges.end()) {
        Result("Input invalid", 0);
    }
    edges[p] = cost;
}

int GetCost(int x, int y) {
    pair<int, int> p = make_pair(min(x, y), max(x, y));
    if (edges.find(p) == edges.end()) {
        Result("Muchie invalid in input", 0);
    }
    return edges[p];
}

void ReadInput(const char *fileName) {
    FILE *input = fopen(fileName, "rb");
    fscanf(input, "%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int x, y, c;
        fscanf(input, "%d %d %d", &x, &y, &c);
        SetCost(x, y, c);
    }
    fscanf(input, "%d", &nrQ);
    queries.resize(nrQ);
    for (int i = 0; i < nrQ; i++) {
        fscanf(input, "%d %d", &queries[i].first, &queries[i].second);
    }
    fclose(input);
}

void ReadOk(const char *fileName) {
    FILE *input = fopen(fileName, "rb");

    fscanf(input,"%lf",&authorPoints); //! addet by me

    bestSolution.resize(nrQ);
    for (int i = 0; i < nrQ; i++) {
        fscanf(input, "%d", &bestSolution[i]);
    }
    fclose(input);
}

void CheckSolution(const char *fileName) {
    FILE * input = fopen(fileName, "rb");
    for (int query = 0; query < nrQ; query++) {
        int nrNodes = 0;
        fscanf(input, "%d", &nrNodes);
        if (nrNodes == 0) {
            continue;
        }
        if (nrNodes < 0 || nrNodes > N) {
            Result("Path invalid", 0);
        }
        vector<int> nodes(nrNodes);
        for (int i = 0; i < nrNodes; i++) {
            fscanf(input, "%d", &nodes[i]);
        }
        if (nodes[0] != queries[query].first || nodes[nodes.size() - 1] != queries[query].second) {
            Result("Extremitati invalide", 0);
        }
        int curCost = 0;
        for (int i = 1; i < (int)nodes.size(); i++) {
            curCost += GetCost(nodes[i - 1], nodes[i]);
        }
        if (curCost < bestSolution[query]) {
            Result("Solutie geniala!", 10);
        }

        _nrGood++;
        if (curCost == bestSolution[query]) {
            nrGood++;
        } else {
            double offBy = (double)(curCost - bestSolution[query]) / bestSolution[query];
            double halfings = offBy / SCORE_HALFLIFE;
            sumResults += MAX_UNOPTIONAL * pow(2, -halfings);
        }
    }
    fclose(input);
}

int main() {
    ReadInput("nolife.in");
    ReadOk("nolife.ok");
    CheckSolution("nolife.out");
    sumResults += nrGood;
    _sumResults += _nrGood;

    ResultOK();
    return 0;
}
