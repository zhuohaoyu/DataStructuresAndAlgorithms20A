/*
    于倬浩 2019201409
    2020/12/20
    Fibonacci Heap
*/

#ifndef _MY_FIB_H_
#define _MY_FIB_H_

#include <cassert>
#include <exception>
#include <stdexcept>

struct node *null;
struct node {
    bool mark;
    int deg;
    int val;
    node *p, *ch, *l, *r;
    node() {
        mark = deg = val = 0;
        p = ch = null;
        l = r = this;
    }
};

struct Fibonacci_Heap {
    node *min;
    int n;
    Fibonacci_Heap() {
        min = null;
        n = 0;
    }
};

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

inline void dottify(Fibonacci_Heap h, string filename, string capt) {
    queue<node *> q;
    node *hh = h.min, *end = h.min;
    ofstream os(filename + ".dot", ios::out);
    os << "digraph G{" << endl;
    os << "    graph [label=\"" << capt << "\"];\n";
    os << "    subgraph roots{\n";
    os << "        rank=\"same\";\n";
    if (h.min == null) {
        os << "};\n";
    } else {
        do {
            os << "        L" << hh << " [style=" << (hh->mark ? "\"filled, dashed\"" : "\"filled\"");
            os << ", fillcolor=" << (hh == h.min ? "\"red\"" : "\"gray\"");
            os << ", label=" << hh->val;
            os << "];" << endl;
            os << "        L" << hh << " -> L" << hh->l << "[style=\"dashed\", color=\"red\", label=\"L\"];\n";
            os << "        L" << hh << " -> L" << hh->r << "[style=\"dashed\", color=\"green\", label=\"R\"];\n";
            node *hc = hh->ch, *hend = hc;
            if (hc != null) {
                do {
                    q.push(hc);
                    hc = hc->r;
                } while (hc != hend);
            }
            hh = hh->r;
        } while (hh != end);
        os << "    }\n";
    }

    while (!q.empty()) {
        node *c = q.front();
        q.pop();
        os << "    L" << c << " [style=" << (c->mark ? "\"filled, dashed\"" : "\"filled\"");
        os << ", fillcolor=\"white\"";
        os << ", label=" << c->val;
        os << "];" << endl;
        c = c->ch;
        if (c == null) continue;
        end = c;
        do {
            q.push(c), c = c->r;

        } while (c != end);
    }
    hh = h.min;
    end = hh;
    do {
        q.push(hh), hh = hh->r;
    } while (hh != end);

    while (!q.empty()) {
        node *c = q.front();
        q.pop();
        node *ch = c->ch;
        if (ch == null) continue;
        end = ch;
        do {
            os << "    L" << c << "->"
               << "L" << ch << ";\n";
            q.push(ch);
            ch = ch->r;
        } while (ch != end);
    }
    os << "}";
    os.close();
    string ex = "dot " + filename + ".dot -Tpng -o " + filename + ".png";
    system(ex.c_str());
    // cerr << "DOT Done\n";
}

inline void init() {
    null = new node;
    null->l = null->r = null->p = null->ch = null;
    null->deg = null->val = null->mark = 0;
}

inline node *fibHeapInsert(Fibonacci_Heap &h, int val) {
    node *x = new node;
    x->p = x->ch = null;
    x->l = x->r = x;
    x->deg = 0, x->val = val;
    x->mark = false;
    ++h.n;
    if (h.min == null) {
        h.min = x;
    } else {
        x->l = h.min, x->r = h.min->r;
        h.min->r->l = x;
        h.min->r = x;
        if (x->val < h.min->val) h.min = x;
    }
    return x;
}

inline Fibonacci_Heap fibHeapUnion(Fibonacci_Heap &a, Fibonacci_Heap &b) {
    if (a.min == null) return b;
    if (b.min == null) return a;
    Fibonacci_Heap ret;
    ret.min = a.min;
    node *p1 = a.min->r, *p2 = b.min->l;
    a.min->r = b.min, b.min->l = a.min;
    p1->l = p2, p2->r = p1;
    if (b.min->val < a.min->val) ret.min = b.min;
    ret.n = a.n + b.n;
    return ret;
}

inline void fibHeapLink(Fibonacci_Heap &h, node *y, node *x) {
    y->r->l = y->l, y->l->r = y->r;
    if (x->ch != null) {
        y->l = x->ch->l, y->r = x->ch, x->ch->l->r = y, x->ch->l = y;
    } else
        x->ch = y, y->l = y->r = y;
    y->p = x;
    ++x->deg;
    y->mark = false;
}

inline void Consolidate(Fibonacci_Heap &h) {
    node **a = new node *[h.n + 1];
    for (int i = 0; i <= h.n; ++i) a[i] = null;
    node *x = h.min, *end = h.min;
    int cnt = 0;
    do {
        ++cnt;
        x = x->r;
    } while (x != end);
    node **rootList = new node *[cnt];
    x = h.min, end = h.min, cnt = 0;
    do {
        rootList[cnt++] = x;
        x = x->r;
    } while (x != end);
    for (int i = 0; i < cnt; ++i) {
        x = rootList[i];
        int d = x->deg;
        while (a[d] != null) {
            node *y = a[d];
            if (x->val > y->val) {
                node *tmp = x;
                x = y, y = tmp;
            }
            fibHeapLink(h, y, x);
            a[d] = null;
            ++d;
        }
        a[d] = x;
    }
    h.min = null;
    for (int i = 0; i <= h.n; ++i) {
        if (a[i] != null) {
            if (h.min == null) {
                h.min = a[i];
                h.min->l = h.min->r = h.min;
            } else {
                h.min->l->r = a[i], a[i]->l = h.min->l;
                a[i]->r = h.min, h.min->l = a[i];
                if (a[i]->val < h.min->val) h.min = a[i];
            }
        }
    }
    delete a;
    delete rootList;
}

inline int fibHeapExtractMin(Fibonacci_Heap &h) {
    if (h.n <= 0) throw std::runtime_error("Heap Empty.");
    node *z = h.min, *x, *end;
    int ret = h.min->val;
    end = z->ch, x = z->ch;
    if (x != null) {
        do {
            node *nxt = x->r;
            x->p = null;
            x->l = z, x->r = z->r;
            z->r->l = x, z->r = x;
            x = nxt;
        } while (x != end);
    }
    z->l->r = z->r, z->r->l = z->l;
    if (z == z->r)
        h.min = null;
    else {
        h.min = z->r;
        Consolidate(h);
    }
    --h.n;
    delete z;
    return ret;
}

inline void Cut(Fibonacci_Heap &h, node *x, node *y) {
    if (x->r == x) {
        y->ch = null;
    } else {
        if (y->ch == x) y->ch = x->r;
        x->l->r = x->r, x->r->l = x->l, --y->deg;
    }

    x->p = null;
    x->l = h.min, x->r = h.min->r;
    h.min->r->l = x, h.min->r = x;
    x->mark = false;
    if (x->val < h.min->val) h.min = x;
}

inline void CascadingCut(Fibonacci_Heap &h, node *y) {
    node *z = y->p;
    if (z != null) {
        if (y->mark == false)
            y->mark = true;
        else {
            Cut(h, y, z);
            CascadingCut(h, z);
        }
    }
}

inline void fibHeapDecreaseKey(Fibonacci_Heap &h, node *x, int val) {
    if (val > x->val) throw std::runtime_error("New key is greater than current key");
    x->val = val;
    node *y = x->p;
    if (y != null && y->val > x->val) {
        Cut(h, x, y);
        CascadingCut(h, y);
    }
    if (x->val < h.min->val) h.min = x;
}

inline void fibHeapDelete(Fibonacci_Heap &h, node *key) {
    fibHeapDecreaseKey(h, key, -2147483648);
    fibHeapExtractMin(h);
}

#endif