#include <iostream>
#include <cstdio>

using namespace std;

const int M = 40000029;
const int mod = 998244353;

typedef unsigned int ui;

struct data{
    bool deleted;
    int key1;
    int key2;
    int val;
    data() {
        deleted = false;
        val = key1 = key2 = -1;
    }
    data(bool deleted, int key1, int key2, int val) : deleted(deleted), key1(key1), key2(key2), val(val) {}
};

struct hash_table{
    data s[M];
    inline void insert(int key1, int key2, int val) {
        int pos = key1 % M;
        while(s[pos].key1 != -1 && s[pos].deleted == false) {
            pos = (pos + key2) % M;
        }
        s[pos] = data(false, key1, key2, val);
    }
    inline void erase(int key1, int key2) {
        int pos = key1 % M;
        while(s[pos].key1 != key1 || (s[pos].key1 == key1 && s[pos].deleted == true)) {
            if(s[pos].key1 == -1) return;
            pos = (pos + key2) % M;
        }
        s[pos].deleted = true;
    }
    inline data* find(int key1, int key2) {
        int pos = key1 % M, checked = 0;
        while(s[pos].key1 != key1 || (s[pos].key1 == key1 && s[pos].deleted == true)) {
            if(s[pos].key1 == -1) return NULL;
            pos = (pos + key2) % M;
            ++checked;
            if(checked == M) return NULL;
        }
        return &s[pos];
    }
}tb;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, op, val;
    int s;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> op >> s;
        if(op == 1) {
            cin >> val;
            tb.insert(s, 1 + s % mod, val);
        }
        else if(op == 2) {
            tb.erase(s, 1 + s % mod);
        }
        else {
            data *res = tb.find(s, 1 + s % mod);
            if(res != NULL) 
                cout << res->val << endl;
            else
                cout << -1 << endl;
        }
    }
}