// #define MANUAL_INPUT

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <ctime>
using namespace std;

mt19937_64 gen(time(0));
const int maxn = 500000005;
inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}

struct data{
    int x;
    long long r;
    inline bool operator < (const data &b) const {
        return r < b.r;
    }
};

inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}

inline void random_selection(int s[], int n, int k) {
    static data d[maxn];
    for(int i = 1; i <= n; ++i) {
        int rnd = rand(1, 1ll * n * n * n);
        d[i].x = s[i];
        d[i].r = rnd;
    }
    sort(d + 1, d + 1 + n);
    for(int i = 1; i <= n; ++i) s[i] = d[i].x;
}

int main() {
    int n = read(), k = read();
    static int s[maxn];

    #ifdef MANUAL_INPUT
    for(int i = 1; i <= n; ++i) s[i] = read();
    #else
    for(int i = 1; i <= n; ++i) s[i] = i;
    #endif
    
    int time1 = clock();
    random_selection(s, n, k);
    int time2 = clock();
    int token = 0;
    for(int i = 1; i <= k; ++i) token ^= s[i];
    cout << "[1a] Time elapsed: " << 1000.0 * (time2 - time1) / CLOCKS_PER_SEC << "ms" << endl;
    cout << "Token=" << token << endl;
/*
    for(int i = 1; i <= k; ++i)
        cout << s[i] << endl;
*/  
}