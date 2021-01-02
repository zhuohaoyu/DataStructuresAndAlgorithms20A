// #define MANUAL_INPUT

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

const int maxn = 500000005;
mt19937 gen(19260817);

inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}
inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}

inline void random_selection(int s[], int n, int k) {
    for(int i = 1; i <= k; ++i) {
        swap(s[i], s[rand(i, n)]);
    }
}


int s[maxn], n, k;
int main() {
    n = read(), k = read();

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
    cout << "[1b] Time elapsed: " << 1000.0 * (time2 - time1) / CLOCKS_PER_SEC << "ms" << endl;
    cout << "Token=" << token << endl;
/*
    for(int i = 1; i <= k; ++i)
        cout << s[i] << endl;
*/
}