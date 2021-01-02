#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    #define rnd() rand()
    struct Data{
        int v, r;
        inline bool operator < (const Data &b) { 
            return v == b.v ? r < b.r : v > b.v;
        }
    };
    struct node{
        node *l,*r;
        int sz;
        Data v;
        inline void pushup(){
            if(sz == 0) return;
            sz = l->sz + r->sz + 1;
        }
    }*root, *null;
    struct pii{
        node *a,*b;
        pii(){}
        pii(node *x,node *y){a=x,b=y;}
    };
    inline node* merge(node *a,node *b) {
        if(a==null) return b; if(b==null) return a;
        if(rnd()%(a->sz+b->sz)<a->sz) {
            a->r = merge(a->r, b), a->pushup();
            return a;
        }
        else {
            b->l = merge(a, b->l), b->pushup();
            return b;
        }
    }
    inline pii split(node *x,int k) {
        if(k <= 0) return pii(null,x);
        if(x==null||k==x->sz) return pii(x,null);
        pii ret;
        if(x->l->sz>=k) ret = split(x->l,k), x->l = ret.b, x->pushup(), ret.b = x;
        else ret = split(x->r,k - x->l->sz - 1), x->r = ret.a, x->pushup(), ret.a = x;
        return ret;
    }
    inline void insert(int pos, Data v) {
        pii p = split(root, pos);
        node *cur = new node;
        cur->l = cur->r = null, cur->sz = 1, cur->v = v;
        root = merge(p.a, merge(cur, p.b));
    }
    int cnt;
    inline void dfs(node *x, vector<vector<int>>& people) {
        if(x == null) return;
        dfs(x->l, people);
        people[cnt][0] = x->v.v, people[cnt][1] = x->v.r;
        ++cnt;
        dfs(x->r, people);
    }
    inline void treap_init() {
        null = new node;
        null->l = null->r = null;
        null->sz = 0;
        root = null;
        cnt = 0;
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<Data> ppl;
        ppl.resize(people.size());
        for(int i = 0; i < ppl.size(); ++i) 
            ppl[i].v = people[i][0], ppl[i].r = people[i][1];    
        sort(ppl.begin(), ppl.end());
        treap_init();
        for(int i = 0; i < ppl.size(); ++i)
            insert(ppl[i].r, ppl[i]);
        dfs(root, people);
        return people;
    }
};

int main() {
    freopen("1.in", "r", stdin);
    Solution sol;
    int n;
    vector<vector<int>> vec;
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; ++i) {
        int h, k;
        cin >> h >> k;
        vec[i].push_back(h), vec[i].push_back(k);
    }
    sol.reconstructQueue(vec);
}