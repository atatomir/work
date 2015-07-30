#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream f("aparitii2.in");
ofstream g("aparitii2.out");

const int NMAX = 1e6+2;

string pattern, text, S;
int zValuesLeft[NMAX*2], cntPrefix[NMAX], zValuesRight[NMAX*2];

inline int compara(int x, int y){
    int cnt = 0;
    for(int i=x, j=y; j<(int)S.size(); ++i, ++j){
        if(S[i] != S[j]) return cnt;
        ++cnt;
    }
    return cnt;
}

void bagaZvalues(int z[]){
    z[0] = S.size();
    int L = -1; int R = -1;
    for(int i=1; i<S.size(); ++i){
        if (i > R){
            z[i] = compara(0, i);
            if (z[i] != 0){
                L = i; R = i + z[i]- 1;
            }
        }else {
            int lungA = R - L + 1; int lungB = R - i + 1;
            int R2 = 0 + lungA - 1; int i2 = R2 - lungB + 1;
            if (z[i2] < lungB){
                z[i] = z[i2]; continue;
            }
            z[i] = lungB + compara(lungB, R+1);
            if (i + z[i]-1 > R){
                L = i; R = i + z[i] - 1;
            }
        }
    }
}

void rezolva(){
    S = pattern + text;
    bagaZvalues(zValuesRight);

    reverse(pattern.begin(), pattern.end());
    reverse(text.begin(), text.end());
    S = pattern + text;
    bagaZvalues(zValuesLeft);

    reverse(zValuesLeft+pattern.size(), zValuesLeft+S.size());
    for(int i=pattern.size(); i<S.size(); ++i){
        zValuesLeft[i] = min(zValuesLeft[i], (int)pattern.size());
        zValuesRight[i] = min(zValuesRight[i], (int)pattern.size());
    }
    int maxLength = pattern.size() / 2;
    for(int i=pattern.size(); i<S.size(); ++i){
        int nextI = i + pattern.size() - 1;
        if (nextI >= S.size()) break;
        int minLength = min(maxLength, zValuesRight[i]);
        minLength = min( minLength, min(maxLength, zValuesLeft[nextI]) );
        if (minLength >= 1){
            cntPrefix[1]++;
            cntPrefix[minLength+1]--;
        }
    }

    for(int i=2; i<=maxLength; ++i){
        cntPrefix[i] += cntPrefix[i-1];
    }
    for(int i=1; i<=maxLength; ++i){
        g << cntPrefix[i] << "\n";
        //cout << i << " " << cntPrefix[i] << "\n";
    }
}

int main(){
    getline(f, text);
    getline(f, pattern);

    rezolva();

    return 0;
}
