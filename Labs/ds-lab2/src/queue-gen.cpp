#include <bits/stdc++.h>
using namespace std;
mt19937 gen(time(0));

inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}

int main() {
    freopen("heap.txt", "w", stdout);
    int ops = 10000;
    printf("%d\n", ops);
    int cur_size = 0;
    for(int i = 1; i <= ops; ++i) {
        int op = rand(1, 3);
        if(cur_size < 10) op = 1;
        if(op == 1) ++cur_size;
        if(op == 2) --cur_size;
        if(op == 1) {
            printf("1 %d\n", rand(-1e9, 1e9));
        }
        else printf("%d\n", op);
    }
}