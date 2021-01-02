#include <iostream>
#include <cstdio>
using namespace std;

const int M = 1048576 << 5;
const int mod = 998244353;

struct data{
    bool deleted;
    int key;
    int val;
    data() {
        deleted = false;
        val = key = -1;
    }
    data(bool deleted, int key, int val) : deleted(deleted), key(key), val(val) {}
};

struct hash_table{
    data s[M];
    inline void insert(int key, int val) {
        int pos = key % M, cnt = 0;
        while(s[pos].key != -1 && s[pos].deleted == false) {
            ++cnt;
            pos = (pos + cnt) % M;
        }
        s[pos] = data(false, key, val);
    }
    inline void erase(int key) {
        int pos = key % M, cnt = 0;
        while(s[pos].key != key || (s[pos].key == key && s[pos].deleted == true)) {
            if(s[pos].key == -1) return;
            ++cnt;
            pos = (pos + cnt) % M;
            if(cnt >= M) return;
        }
        s[pos].deleted = true;
    }
    inline data* find(int key) {
        int pos = key % M, cnt = 0;
        while(s[pos].key != key || (s[pos].key == key && s[pos].deleted == true)) {
            if(s[pos].key == -1) return NULL;
            ++cnt;
            pos = (pos + cnt) % M;
            if(cnt == M) return NULL;
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
            tb.insert(s, val);
        }
        else if(op == 2) {
            tb.erase(s);
        }
        else {
            data *res = tb.find(s);
            if(res != NULL) 
                cout << res->val << endl;
            else
                cout << -1 << endl;
        }
    }
}