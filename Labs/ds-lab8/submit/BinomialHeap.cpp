#include <bits/stdc++.h>

using namespace std;

struct node *null;
struct node{
    int deg;
    node *fa, *ch, *sib;
    int* val;
    inline node* binomialLink(node *x) {
        if(x == null) return null;
        x->fa = this;
        x->sib = ch;
        ch = x;
        ++deg;
        return this;
    }
    node() {
        fa = ch = sib = null;
        deg = 0;
        val = NULL;
    }
};

typedef node* BinomialHeap;

// 可视化
inline void dottify(BinomialHeap h,string filename, string capt) {
    queue<node*> q;
    node *hh = h;
    while(hh != null) q.push(hh), hh = hh->sib;
    ofstream os(filename + ".dot", ios::out);
    os << "digraph G{" << endl;
    os << "    graph [label=\"" << capt << "\"];\n";
    // os << "    L" << null << " [label=\"null\", style=\"filled\", fillcolor=\"gray\"];" << endl;
    while(!q.empty()) {
        node *c = q.front();
        q.pop();
        os << "    L" << c << " [style=\"filled\", fillcolor=";
        os << (c == h? "\"red\"":"\"gray\"");
        os << ", label=" << *c->val;
        os << "];" << endl;
        c = c->ch;
        while(c != null) q.push(c), c = c->sib;
    }
    hh = h;
    while(hh != null) {
        // os << "    L" << hh << " -> L" << hh->sib << " [color=\"red\"];\n";
        q.push(hh), hh = hh->sib;
    }
    while(!q.empty()) {
        node *c = q.front();
        q.pop();
        node *ch = c->ch;
        while(ch != null) {
            os << "    L" << c << " -> L" << ch << ";\n";
            q.push(ch);
            ch = ch->sib;
        }
    }
    os << "}";
    os.close();
    string ex = "dot " + filename + ".dot -Tpng -o " + filename + ".png";
    system(ex.c_str());
}

inline void init() {
    null = new node;
    null->val = new int(0);
    null->fa = null->ch = null->sib = null;
    null->deg = 0;
}

inline BinomialHeap mergeHeap(BinomialHeap a, BinomialHeap b) {
    if(a == null) return b;
    if(b == null) return a;
    node *fi, *p;
    if(a->deg < b->deg) 
        fi = p = a, a = a->sib;
    else 
        fi = p = b, b = b->sib;
    while(a != null && b != null) {
        if(a->deg < b->deg) 
            p->sib = a, p = a, a = a->sib;
        else 
            p->sib = b, p = b, b = b->sib;
    }
    if(a != null) p->sib = a;
    else p->sib = b;
    return fi;
}

inline BinomialHeap binomialHeapUnion(BinomialHeap a, BinomialHeap b) {
    BinomialHeap h = mergeHeap(a, b);
    if(h == null) return h;
    node *prev_x = null, *x = h, *next_x = x->sib;
    while(next_x != null) {
        if(x->deg != next_x -> deg || (next_x->sib != null && next_x->sib->deg == x->deg)) {
            prev_x = x;
            x = next_x;
        }
        else {
            if(*(x->val) <= *(next_x->val)) {
                x->sib = next_x->sib;
                x->binomialLink(next_x);
            }
            else {
                if(prev_x == null) h = next_x;
                else prev_x->sib = next_x;
                next_x->binomialLink(x);
                x = next_x;
            }
        }
        next_x = x->sib;
    }
    return h;
}

inline void binomialHeapInsert(BinomialHeap& h, int val) {
    BinomialHeap n = new node;
    n->val = new int(val);
    h = binomialHeapUnion(h, n);
}

inline void decreaseKey(BinomialHeap h, node* key, int val) {
    assert(*(key->val) >= val);
    while(key->fa != null) {
        if(*(key->val) < *(key->fa->val)) {
            swap(key->val, key->fa->val);
            key = key->fa;
        }
        else break;
    }
}

inline int extractMin(BinomialHeap &h) {
    int ret = 2147483647;
    node *hh = h;
    node *minh = null;
    while(hh != null) {
        if(*(hh->val) < ret) {
            ret = *(hh->val);
            minh = hh;
        }
        hh = hh->sib;
    }
    if(h != minh) {
        node *pre_minh = h;
        while(pre_minh->sib != minh) pre_minh = pre_minh->sib;
        pre_minh->sib = minh->sib;
    }
    else 
        h = minh->sib;
    node *newH = minh->ch, *pre = null;
    if(newH != null) newH->fa = null;
    while(newH != null) {
        node *nxt = newH->sib;
        newH->sib = pre;
        newH->fa = null;
        pre = newH;
        newH = nxt;
    }
    h = binomialHeapUnion(h, pre);
    delete minh->val;
    delete minh;
    return ret;
}

inline void binomialHeapErase(BinomialHeap& h, node *key) {
    decreaseKey(h, key, -2147483648);
    extractMin(h);
}



int main() {
    init();
    BinomialHeap bh = null;
    int n;
    cin >> n;
    while(n--) {
        int op;
        cin >> op;
        if(op == 1) { // Insert
            int x;
            cin >> x;
            binomialHeapInsert(bh, x);
            dottify(bh, "bh", "Insert " + to_string(x));
        }
        else { // Extract_min
            int x = extractMin(bh);
            cout << x << endl;
            dottify(bh, "bh", "Extract_Min = " + to_string(x));
        }
        // system("sleep 1s");
    }
}