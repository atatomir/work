/*
 * Implementare main.cpp 
 * sursa comisie
 */

#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "header.h"

using namespace std;

#define DEBUG(...) if (1) { __VA_ARGS__;}

struct QueryAnswer {
    bool same_character;
    int max_len;
    long long count;
};

class Interaction {
  public:
    void Initialise(const string& file_name);
    
    bool SameChar(int r1, int r2);
    int MaxLen(int left, int right);
    long long Count(int left, int right);
    void Solution(const vector<int>& elements);

    int GetN() { return this->n; };
    long long GetK() { return this->k; };

    static Interaction& GetSingleton();
    void AnswerNotProvided();

  private:
    void Expect(bool condition, const string& message);

    int n;
    int max_len;
    long long k;
    vector<vector<QueryAnswer>> precomputed_answers;

    int num_queries;
    Interaction() { }
};

static Interaction& interaction = Interaction::GetSingleton();

bool sameCharacter(int pos1, int pos2) {
    return interaction.SameChar(pos1, pos2);    
};

int getMaxPalLength(int left, int right) {
    return interaction.MaxLen(left, right);
};

long long getMaxPalCount(int left, int right) {
    return interaction.Count(left, right);
};

void solution(int n, int positions[]) {
    vector<int> elements(n);
    for (int i = 0; i < n; i += 1) {
        elements[i] = positions[i];
    }

    interaction.Solution(elements);
}

Interaction& Interaction::GetSingleton() {
    static bool first_encounter = true;
    if (not first_encounter) {
        cerr << "Nu incercati sa declarati 2 singletoane, nu e fromos";
        exit(0);
    }

    static Interaction singleton;
    return singleton;
};

void Interaction::Expect(bool condition, const string& message) {
    if (not condition) {
        cerr << message << "\n";
        exit(1);
    }
};          

void Interaction::AnswerNotProvided() {
    cerr <<  "solution() was not called\n";
    exit(1);
}

bool Interaction::SameChar(int pos1, int pos2) {
    DEBUG(cerr << "[Query]\t" << "SameChar\t" << pos1 << '\t' << pos2 << '\n');
    Expect((0 <= pos1 and pos1 < n) and (0 <= pos2 and pos2 < n), 
            "wrong SameCharacter query");

    num_queries += 1;

    return precomputed_answers[pos1][pos2].same_character; 
};

int Interaction::MaxLen(int left, int right) {
    DEBUG(cerr << "[Query]\t" << "MaxLen\t" << left << '\t' << right << '\n');
    Expect((left <= right) and (0 <= left) and (right < n),
            "wrong getMaxPalLenght query");

    num_queries += 1;

    return precomputed_answers[left][right].max_len; 
};

long long Interaction::Count(int left, int right) {
    DEBUG(cerr << "[Query]\t" << "Count\t" << left << '\t' << right << '\n');
    Expect(((left <= right) and (right < n) and (0 <= left)), 
            "wrong getMaxPalCount query");

    num_queries += 1;

    return precomputed_answers[left][right].count; 
};

void Interaction::Solution(const vector<int>& positions) {
    ofstream out("solutie");
    for(auto p: positions)
      out << p << " ";
    out << "\n";
    out.close();
    exit(0);
}

void Interaction::Initialise(const string& file_name) {
    ifstream fin(file_name.c_str());
    string txt;
    fin >> txt;
    fin >> this->k;
    this->n = int(txt.size());
    
    precomputed_answers = vector<vector<QueryAnswer>>(n, vector<QueryAnswer>(n));

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            precomputed_answers[i][j].same_character = (txt[i] == txt[j]);
        }
    }

    for (int i = 0; i < n; i += 1) {
        precomputed_answers[i][i].count = 1;
        precomputed_answers[i][i].max_len = 1;
    }

    for (int i = 0; i + 1 < n; i += 1) {
        if (txt[i] == txt[i + 1]) {
            precomputed_answers[i][i + 1].count = 1;
            precomputed_answers[i][i + 1].max_len = 2;
        } else {
            precomputed_answers[i][i + 1].count = 2;
            precomputed_answers[i][i + 1].max_len = 1;
        }
    }

    auto Update = [&](QueryAnswer& lhs, QueryAnswer& rhs, int sign) -> void {
        if (rhs.max_len > lhs.max_len) {
            lhs.count = rhs.count;
            lhs.max_len = rhs.max_len;
        } else if (rhs.max_len == lhs.max_len) {
            assert(lhs.count < (1LL << 50));
            lhs.count += 1LL * rhs.count * sign;
            assert(lhs.count < (1LL << 50));
            assert(lhs.count > 0);
        }
        return ;
    };
    
    for (int l = 2; l < n; l += 1) {
        for (int left = 0, right = l; right < n; left += 1, right += 1) {
            if (txt[left] == txt[right]) {
                precomputed_answers[left][right].max_len = 
                    precomputed_answers[left + 1][right - 1].max_len + 2;
                 precomputed_answers[left][right].count = 
                    precomputed_answers[left + 1][right - 1].count;

                Update(precomputed_answers[left][right], precomputed_answers[left + 1][right], +1);
                Update(precomputed_answers[left][right], precomputed_answers[left][right - 1], +1);
            } else {
                Update(precomputed_answers[left][right], precomputed_answers[left + 1][right], +1);
                Update(precomputed_answers[left][right], precomputed_answers[left][right - 1], +1);
                Update(precomputed_answers[left][right], precomputed_answers[left + 1][right - 1], -1);
            }
        }
    }
 
    this->max_len = precomputed_answers[0][this->n - 1].max_len; 
};

int main() {
    interaction.Initialise("npalind.in");
    solve(interaction.GetN(), interaction.GetK());
    interaction.AnswerNotProvided();
    return 0;
}
