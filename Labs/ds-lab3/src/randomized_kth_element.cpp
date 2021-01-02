#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <random>
using namespace std;

inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}

mt19937 gen(time(0));

inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}

template<class T>
int randomized_partition(T a[], int L, int R) {
    int p = rand(L, R);
    if(p != R) swap(a[p], a[R]);
    int i = L - 1;
    for(int j = L; j < R; ++j) {
        if(a[j] <= a[R]) {
            ++i;
            swap(a[j], a[i]);
        }
    }
    swap(a[R], a[i + 1]);
    return i + 1;
}

template<class T>
T randomized_select(T a[], int L, int R, int k) {
    if(L == R) return a[L];
    int p = randomized_partition(a, L, R);
    if(p - L + 1 == k) return a[p];
    else if(p - L + 1 > k) return randomized_select(a, L, p, k);
    else return randomized_select(a, p + 1, R, k - (p - L + 1));
}

int a[100000005];
int main() {
    // freopen("1.in", "r", stdin);
    int n = read(), m = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    cout << randomized_select(a, 1, n, m) << endl;
}