#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct node *null;

struct node {
    node *c[2], *p;
    int sz, val;
    bool red;
    node() {
        c[0] = c[1] = p = null;
        red = true;
    }
    inline void pushup() {
        if (this == null) return;
        sz = c[0]->sz + c[1]->sz + 1;
    }
} * root;

inline void init() {
    null = new node;
    null->c[0] = null->c[1] = null->p = null;
    null->sz = 0, null->val = 0, null->red = false;
}

#define isrc(x) ((x)->p->c[1] == (x))

inline void rotate(node *x, bool d) {  //d=0 left, d=1 right
    node *y = x->c[d ^ 1];
    if (y->c[d] != null) y->c[d]->p = x;
    if (x->p == null)
        root = y;
    else
        x->p->c[isrc(x)] = y;
    y->p = x->p, x->p = y;
    x->c[d ^ 1] = y->c[d], y->c[d] = x;
    x->pushup(), y->pushup();
}

inline void rb_insert_fixup(node *z) {
    while (z->p->red) {
        int d = isrc(z->p);
        node *uncle = z->p->p->c[d ^ 1], *father = z->p;
        if (uncle->red) {
            father->red = uncle->red = false;
            father->p->red = true;
            z = father->p;
        } else {
            if (isrc(z) ^ d) {
                z = z->p;
                rotate(z, d);
            }
            z->p->red = false;
            z->p->p->red = true;
            rotate(z->p->p, d ^ 1);
        }
    }
    root->red = 0;
}

inline void insert(node *&rt, int val) {
    node *x = rt, *y = null;
    while (x != null) {
        y = x;
        if (val < x->val)
            x = x->c[0];
        else
            x = x->c[1];
    }
    node *z = new node;
    z->p = y;
    z->val = val, z->sz = 1;
    if (y == null)
        rt = z;
    else if (val < y->val)
        y->c[0] = z, y->pushup();
    else
        y->c[1] = z, y->pushup();
    rb_insert_fixup(z);
}

inline void dfs(ofstream &os, node *x) {
    if (x == null) return;
    dfs(os, x->c[0]);
    os << "    L" << x << " [style=\"filled\", fillcolor=";
    if (x->red)
        os << "\"red\"";
    else
        os << "\"gray\"";
    os << ", label=" << x->val;
    os << "];" << endl;
    dfs(os, x->c[1]);
}

inline void dfs2(ofstream &os, node *x) {
    if (x == null) return;
    dfs2(os, x->c[0]);
    os << "    L" << x << " -> L" << x->c[0] << ";\n";
    os << "    L" << x << " -> L" << x->c[1] << ";\n";
    dfs2(os, x->c[1]);
}

inline void dottify(string filename) {
    ofstream os(filename + ".dot", ios::out);
    os << "digraph G{" << endl;
    os << "    graph [ordering=\"out\"];" << endl;
    os << "    L" << null << " [label=\"null\", style=\"filled\", fillcolor=\"gray\"];" << endl;
    dfs(os, root);
    os << endl;
    dfs2(os, root);
    os << "}";
    os.close();
    string ex = "dot " + filename + ".dot -Tpng -o " + filename + ".png";
    system(ex.c_str());
}

int main() {
    init();
    root = null;
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        insert(root, x);
        dottify("test");
        getchar();
    }
    //41 38 31 12 19 8
}