#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}

int s[5000005], n, m;

int main() {
    // freopen("1.in", "r", stdin);
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) s[i] = read();
    nth_element(&s[1], &s[m], &s[n + 1]);
    cout << s[m] << endl;
}