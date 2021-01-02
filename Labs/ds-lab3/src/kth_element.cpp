#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

template<class T>
inline void insertion_sort(T a[], int L, int R) {
    for(int i = L + 1; i <= R; ++i) {
        T cur = a[i];
        int j = i - 1;
        while(j >= L && cur < a[j]) a[j + 1] = a[j], j--;
        a[j + 1] = cur;
    }
}

template<class T>
inline int partition(T a[], int L, int R, T pivot) {
    if(L >= R) return L;
    for(int i = L; i < R; ++i) if(a[i] == pivot) {
        swap(a[R], a[i]);
        break;
    }
    int i = L - 1;
    for(int j = L; j < R; ++j) {
        if(a[j] <= pivot) {
            ++i;
            swap(a[j], a[i]);
        }
    }
    swap(a[i + 1], a[R]);
    return i + 1;
}

template<class T>
inline T kth_element(T a[], int L, int R, int k) { //finds the kth element in [L, R]
    if(R - L <= 140) {
        insertion_sort(a, L, R);
        return a[L + k - 1];
    }
    int len = R - L + 1;
    for(int i = 0, j = len / 5; i < j; ++i) {
        insertion_sort(a, L + i * 5, L + i * 5 + 4);
        swap(a[L + i * 5 + 2], a[L + i]);
    }
    T MoM = kth_element(a, L, L + len / 5, len / 10);
    int pos = partition(a, L, R, MoM);
    if(pos - L + 1 >= k) return kth_element(a, L, pos, k);
    else return kth_element(a, pos + 1, R, k - (pos - L + 1));
}

inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}

int s[100000005], n, m;
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) s[i] = read();
    cout << kth_element(s, 1, n, m) << endl;
}