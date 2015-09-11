#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while(!isDigit(data[pos])) {
                if (++pos == dim) refill();
            }
            dest = 0;
            while (isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) refill();
            }
            return *this;
        }

    private:
        vector<char> data;
        int dim, pos;

        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }

        void refill() {
            memset(&data[0], 0, sizeof(data));
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

//! max sliding window
class SlidingWindow {
    public:
        void init(deque< pair<int, int> > *_data) {
            data = _data;
            while (!data -> empty()) data->pop_back();
        }

        void add(int pos, int value) {
            while (!data -> empty()) {
                auto last = data -> back();
                if (last.second > value) break;
                data -> pop_back();
            }
            data -> push_back(mp(pos, value));
        }

        void remove(int lim) {
            while (!data -> empty()) {
                auto last = data -> front();
                if (last.first > lim) break;
                data -> pop_front();
            }
        }

        int getBest() {
            if (data -> empty()) return 0;
            return data -> front().second;
        }

    private:
        deque< pair<int, int> > *data;
};

int n, R, C, i;
int height[maxN];

SlidingWindow sd_min, sd_max;
deque< pair<int, int> > aux_min, aux_max;
int pay[maxN];

bool can_group(int lim) {
    int need = R;

    for (i = C; i <= n; ) {
        if (pay[i] <= lim) {
            need--;
            i += C;
        } else {
            i++;
        }
    }

    return need <= 0;
}

int main()
{
    Buffer fin("easychoice.in", 1 << 20);
    freopen("easychoice.out","w",stdout);

    sd_min.init(&aux_min);
    sd_max.init(&aux_max);

    fin >> n >> R >> C;
    for (i = 1; i <= n; i++) fin >> height[i];
    sort(height + 1, height + n + 1);

    for (i = 1; i < C; i++) {
        sd_max.add(i,  height[i]);
        sd_min.add(i, -height[i]);
    }

    for (i = C; i <= n; i++) {
        sd_max.add(i,  height[i]);
        sd_min.add(i, -height[i]);

        sd_max.remove(i-C);
        sd_min.remove(i-C);

        pay[i] = sd_max.getBest() + sd_min.getBest();
    }

    int ans = -1;
    for (int step = 1 << 30; step > 0; step >>= 1) {
        int aux = ans + step;
        if (!can_group(aux)) ans = aux;
    }
    printf("%d", ans + 1);

    return 0;
}
