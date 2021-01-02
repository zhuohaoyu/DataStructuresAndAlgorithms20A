#ifndef _MY_BST_HPP_
#define _MY_BST_HPP_

struct node* null;

struct node{
    node *c[2], *p;
    int sz;
    int val;
    node() {
        c[0] = c[1] = p = null;
        sz = 1;
    }
    inline void pushup() {
        if(this == null) return;
        sz = c[0]->sz + c[1]->sz + 1;
    }
};

inline void init() {
    null = new node;
    null->c[0] = null->c[1] = null->p = null;
    null->val = 0, null->sz = 0;
}


inline node* kth(node *x, int k) {
    while(x != null) { //本质是靠维护的子树大小sz，判断第k个元素位于左子树或是右子树
        if(x->c[0]->sz + 1 == k) return x;
        if(k > x->c[0]->sz + 1) 
            k -= x->c[0]->sz + 1, x = x->c[1];
        else x = x->c[0];
    }
    return null;
}
inline node* find(node *x, int val) {
    while(x != null) { //本质依据BST的性质，定位val节点应该所在的位置。如果最后无法定位，则节点不存在返回空
        if(x->val == val) return x;
        if(val < x->val) x = x->c[0];
        else x = x->c[1];
    }
    return null;
}

inline int rank(node *x, int val) {
    int ret = 0;
    while(x != null) { 
        if(x->val < val) { //本质是依靠维护的子树大小sz，计算出小于val的元素个数
            ret += x->c[0]->sz + 1;
            x = x->c[1];
        }
        else x = x->c[0];
    }
    return ret;
}

inline node* predecessor(node *x) {
    if(x->c[0] != null) { //左子树不为空，直接找最深的右儿子
        node *y = x->c[0];
        while(y->c[1] != null) y = y->c[1];
        return y;
    }
    else {
        node *y = x->p;
        while(y->p != null && y->c[0] == x) {
            x = y; //找到和x在同一条左链顶端节点的父亲
            y = y->p;
        }
        return y;
    }
    return null;
}

inline node* successor(node *x) {
    if(x->c[1] != null) { //右子树不为空，直接寻找最深的左儿子
        node *y = x->c[1];
        while(y->c[0] != null) y = y->c[0];
        return y;
    }
    else {
        node *y = x->p;
        while(y->p != null && y->c[1] == x) {
            x = y; //找到和x在同一条右链顶端的节点的父亲
            y = y->p;
        }
        return y;
    }
    return null;
}


inline void insert(node *&x, int val) { //在以x为根的子树中插入键值为val的节点。
    if(x == null) { 
        //已经遍历到哨兵节点，该位置即为待插入的位置，因此直接插入
        x = new node;
        x -> val = val;
        return;
    }
    if(val <= x -> val) //待插入值在当前节点的左子树，递归进入返回后，维护子节点的父亲节点。
        insert(x->c[0], val), x->c[0]->p = x;
    else //待插入节点在当前节点的右子树。
        insert(x->c[1], val), x->c[1]->p = x;
    x->pushup(); //完成子树的处理后，以O(1)代价维护当前节点信息（如子树大小）。
    return;
}

#define isrc(x) ((x)->p->c[1] == (x))
inline void erase(node *&x, int val) { //从以x为根的子树中删除值为val的节点
    node *t = find(x, val);
    //利用前述的find操作，寻找值为val的节点。
    if(t->c[0] == null && t->c[1] == null) { 
        //t为叶子节点，直接删除，并维护父亲节点的子树信息。
        if(t == x) x = null;
        else {
            t->p->c[isrc(t)] = null;
            t->p->pushup();
        }
        node *cur = t->p; 
        //维护当前节点到根一条链上的节点信息
        while(cur != null) cur->pushup(), cur = cur->p;
        delete t;
    }
    else if(t->c[0] == null || t->c[1] == null) { //t只有一个儿子。
        bool d = (t->c[1] == null) ^ 1; //确定非空的儿子
        if(t == x) { //分类讨论当前节点是否为根
            x = t->c[d];
            t->c[d]->p = null;
            t->c[d]->pushup();
        }
        else {
            t->p->c[isrc(t)] = t->c[d];
            t->p->pushup();
            t->c[d]->p = t->p;
        }
        node *cur = t->p;
        while(cur != null) cur->pushup(), cur = cur->p;
        delete t;
    }
    else {//t有两个儿子
        node *v = t->c[1];//找t的后继
        while(v->c[0] != null) v = v->c[0];
        v->p->c[0] = v->c[1];
        v->p->pushup();
        if(v->c[1] != null) v->c[1]->p = v->p; 
        t->val = v->val;//用找到的后继替换t
        node *cur = v->p;
        while(cur != null) cur->pushup(), cur = cur->p;
        delete v;
    }
}

#endif