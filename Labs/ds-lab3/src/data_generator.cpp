#include <bits/stdc++.h>
using namespace std;
mt19937 gen(time(0));
inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}
int main() {
    freopen("data.in", "w", stdout);
    int n = 100000000, m;
    m = rand(1, n);
    printf("%d %d\n", n, m);
    for(int i = 1; i <= n; ++i) printf("%d ", rand(-2000000000, 2000000000));
}