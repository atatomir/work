#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    ifstream cin("echilibrare.in");
    ofstream cout("echilibrare.out");

    int N; cin >> N;
    vector< vector<int> > V(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> V[i][j];

    vector<int> line(N, 0), column(N, 0);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            line[i] = max(line[i], V[i][j]);

    vector<int> matchForCol(N, -1), // with which row the current column matches
                swapForCol(N, -1); // with whom to swap a column's match in case we need to

    for (int i = 0; i < N; ++i) { // match every row
        int currentRow = i, currentColumn = -1;
        vector<int> minDiff(N, numeric_limits<int>::max());
        vector<bool> used(N, false);

        do {
            if (currentColumn != -1)
                used[currentColumn] = true;
            int bestDiff = numeric_limits<int>::max(), where = -1;
            for (int j = 0; j < N; ++j)
                if (!used[j]) { // like hopcroft karp, w find an alternating chain, so we dont visit the same column twice
                    int currentDiff = line[currentRow] + column[j] - V[currentRow][j];
                    if (currentDiff < minDiff[j]) { // if we do change column j, then its match will change to the curent row match which is currentColumn
                        minDiff[j] = currentDiff;
                        swapForCol[j] = currentColumn;
                    }
                    if (minDiff[j] < bestDiff) {
                        bestDiff = minDiff[j];
                        where = j;
                    }
                }
            for (int j = 0; j < N; ++j)
                if (used[j]) { // column is in a matching, we want to saturate stuff though
                    // we can decrease its match line and increase its value on column, this way we wont desaturate anythign on those columns and rows,
                    // but we will definelty sature on our current column at least at one position
                    line[matchForCol[currentColumn]] -= bestDiff;
                    column[currentColumn] += bestDiff;
                } else { // not in matching, that means we improved them anyway
                    minDiff[j] -= bestDiff;
                }
            line[i] -= bestDiff; // update current line
            currentColumn = where; // next saturated column,
            currentRow = matchForCol[currentColumn]; // move to its column, we have to match it to something else now
        } while (matchForCol[currentColumn] != -1); // repeat until we find an empty column

        while (currentColumn != -1) {
            int nextColumn = swapForCol[currentColumn];
            if (nextColumn == -1) {
                matchForCol[currentColumn] = i;
                break;
            }
            matchForCol[currentColumn] = matchForCol[nextColumn]; // took what he had
            currentColumn = nextColumn;
        }
    }

    int answer = (accumulate(line.begin(), line.end(), 0) + accumulate(column.begin(), column.end(), 0)) * N;
    cout << answer << "\n";

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << line[i] + column[j] << " ";
        cout << "\n";
    }
}

