#include <bits/stdc++.h>
using namespace std;
mt19937 gen(time(0));

inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}


int main() {
    freopen("sort.txt", "w", stdout);
    int n = 100000;
    printf("%d\n", n);
    for(int i = 1; i <= n; ++i) printf("%d\n", rand(-10000000, 100000000));
}