#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long


class OutBuffer {
    public:
        OutBuffer(int _dim) {
            dim = _dim;
            data = vector<char>(dim + 11, '\0');
            pos = 0;
        }
        
        ~OutBuffer() {
            flush();
        }
        
        OutBuffer& operator<<(char c) {
            data[pos++] = c;
            if (pos >= dim) flush();
        }
        
        OutBuffer& operator<<(int x) {
            vector<int> aux = {};
            while (x != 0) {
                aux.pb(x % 10);
                x /= 10;
            }
            if (aux.empty()) aux = {0};
            
            reverse(aux.begin(), aux.end());
            for (auto e : aux) 
                *this << (char)('0' + e);
            
            return *this;
        }
        
    private:
        int dim, pos;
        vector<char> data;
        
        void flush() {
            fwrite(&data[0], 1, pos, stdout);
            pos = 0;
        }
};


int main() {
    
   
    
    return 0;
}
