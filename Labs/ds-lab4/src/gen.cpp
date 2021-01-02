#include <bits/stdc++.h>
using namespace std;
mt19937 gen(time(0));
inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}
vector<int> vc;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("data.in", "w", stdout);
    int n = 10000000, size = 0;
    cout << n << endl;
    for(int i = 1; i <= n; ++i) {
        int op = rand(1, 3);
        if(size < 1000) op = 1;
        if(op == 1) {
            ++size;
            int s = rand(0, 2147483647);
            vc.push_back(s);
            cout << 1 << ' ' << s << ' ' << rand(1, 1000000000) << endl;
        }
        if(op == 2) {
            int id = rand(0, size - 1);
            --size;
            cout << 2 << ' ' << vc[id] << endl;
        }
        if(op == 3) {
            int id = rand(0, size - 1);
            cout << 3 << ' ' << vc[id] << endl;
        }
    }
}