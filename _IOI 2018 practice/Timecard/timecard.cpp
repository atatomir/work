#include "timecard.h"

static int N;

void init(int n) {
    N = n;
}

std::string convert(std::string s) {
    for (auto& e : s)
        if (e < 'a')
            e -= 'A' - 'a';
    return s;
}
