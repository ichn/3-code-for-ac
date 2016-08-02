#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
typedef long long LL;
const int maxn = 10000 + 20;
int n, m, sum, a[maxn], INF = 0x3f3f3f3f;
struct treap_node {
    treap_node *ch[2];
    int key, fix, cnt, size;
    treap_node() {
        ch[0] = ch[1] = NULL;
    }
    treap_node(int _key) {
        ch[0] = ch[1] = NULL;
        key = _key;
        size = cnt = 1;
        fix = rand();
    }
} *T[maxn << 2];
inline void maintain(treap_node *t) {
    t->size = t->cnt;
    if(t->ch[0]) t->size += t->ch[0]->size;
    if(t->ch[1]) t->size += t->ch[1]->size;
}
void rot(treap_node *&t, int d) {
    treap_node *p = t->ch[d ^ 1];
    t->ch[d ^ 1] = p->ch[d], p->ch[d] = t;
    maintain(t), maintain(p);
    t = p;
}
void insert(treap_node *&t, int val) {
    if(t == NULL) {
        t = new treap_node(val);
    } else {
        if(val < t->key) {
            insert(t->ch[0], val);
            if(t->ch[0]->fix < t->fix) rot(t, 1);
        } else if(t->key < val) {
            insert(t->ch[1], val);
            if(t->ch[1]->fix < t->fix) rot(t, 0);
        } else
            ++t->cnt;
    }
    maintain(t);
}
void del(treap_node *&t, int val) {
    if(t->key == val) {
        if(t->cnt == 1) {
            if(!t->ch[0] || !t->ch[1]) {
                treap_node *p = t;
                if(!p->ch[0]) p = t->ch[1];
                else p = t->ch[0];
                delete t;
                t = p;
            } else {
                int d = t->ch[0]->fix < t->ch[1]->fix;
                rot(t, d);
                del(t->ch[d], val);
            }
        } else --t->cnt;
    } else del(t->ch[t->key < val], val);
    if(t) maintain(t);
}
int select(treap_node *t, int val) {
    if(t == NULL) return 0;
    if(val < t->key) return select(t->ch[0], val);
    int p = (t->ch[0]) ? t->ch[0]->size + t->cnt : t->cnt;
    if(t->key < val) p += select(t->ch[1], val);
    return p;
}
bool ok;
void query(int l, int r, int rt, int ql, int qr, int val) {
    if(ql <= l && r <= qr) {
        sum += select(T[rt], val);
        return ;
    } else {
        int mid = (l + r) >> 1;
        if(ql <= mid) query(l, mid, rt << 1, ql, qr, val);
        if(mid < qr) query(mid + 1, r, rt << 1 | 1, ql, qr, val);
    }
}
void seg_del(int l, int r, int rt, int pos, int val) {
    del(T[rt], val);
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(pos <= mid) seg_del(l, mid, rt << 1, pos, val);
    else if(mid < pos) seg_del(mid + 1, r, rt << 1 | 1, pos, val);
}
void seg_insert(int l, int r, int rt, int pos, int val) {
    insert(T[rt], val);
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(pos <= mid) seg_insert(l, mid, rt << 1, pos, val);
    else if(mid < pos) seg_insert(mid + 1, r, rt << 1 | 1, pos, val);
}
 
char gchar() {
    char ret = getchar();
    for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar());
    return ret;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin), freopen("data.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    srand(n * m + 258 + 17);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        seg_insert(1, n, 1, i, a[i]);
    }
    ok = false;
    for(int i = 1, p, b, c, d; i <= m; ++i) {
        d = gchar();
        if(d == 'C') {
            scanf("%d%d", &p, &b);
            seg_del(1, n, 1, p, a[p]);
            a[p] = b;
            seg_insert(1, n, 1, p, a[p]);
        } else {
            scanf("%d%d%d", &b, &c, &p);
            LL l = 0, r = INF;
            while(l < r) {
                LL mid = (l + r) >> 1;
                sum = 0;
                query(1, n, 1, b, c, mid);
                if(sum < p) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            printf("%lld\n", l);
        }
    }
    return 0;
}
