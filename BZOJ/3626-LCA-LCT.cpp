#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
    const int INF = 0x3f3f3f3f;
    typedef long long LL;
    typedef double DB;
    inline void pc(char c) { putchar(c); }
    template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
    template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
    template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
    template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
    template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
    inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
    template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
        if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
        ret = ret * flag;
    }
    inline int fr() { int x; fr(x); return x; }
    template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
    template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
        for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
        return ret;
    }
    const int maxv = 100, maxe = 100;
    struct Edge {
        int edge, head[maxv], to[maxe], next[maxe];
        Edge() { edge = 0; memset(head, -1, sizeof head); }
        void addedge(int u, int v) {
            to[edge] = v, next[edge] = head[u];
            head[u] = edge++;
        }
    };
};
using namespace my_useful_tools;
 
 
/*
 * 给一颗树，支持
 * 1. 链点加
 * 2. 询问链上权值和
 */
/*
 * lct编写指南
 * 1. 子关系高于父关系
 *  体现在以下几个方面
 *  1. 称节点x,y存在某关系，当且仅当x是y的某
 *  2. 存在子关系必定存在父关系
 *  3. 父关系只表示链接，子关系表示在同一颗splay内
 * 2. rot时先把爷爷干掉。。
 */
#define sn splay_node
const int maxn = 50000 + 1000;
#define lc ch[0]
#define rc ch[1]
struct lct {
    struct splay_node {
        sn *fa, *ch[2];
        int sz, v, s, a;
        sn(int v = 0):v(v) {
            fa=lc=rc=NULL, sz=a=0, s=v;
        }
        int d() {
            return this==this->fa->ch[0];
        }
        bool is_root() {
            return fa==NULL || (this!=fa->lc && this!=fa->rc);
        }
        void push_up() {
            s = v, sz = 1;
            if(lc) s += lc->s, sz += lc->sz;
            if(rc) s += rc->s, sz += rc->sz;
        }
        void push_down() {
            if(a) {
                if(lc) lc->a+=a, lc->s+=a*lc->sz, lc->v+=a;
                if(rc) rc->a+=a, rc->s+=a*rc->sz, rc->v+=a;
                a = 0;
            }
        }
    } *T[maxn];
    void rot(sn*x) {
        sn *y = x->fa, *z = y->fa;
        y->push_down(), x->push_down();
        int d = x->d();
        y->ch[d^1]=x->ch[d];
        if(x->ch[d]) x->ch[d]->fa=y;
        if(!y->is_root()) z->ch[z->ch[1]==y]=x;
        x->ch[d]=y, y->fa=x;
        x->fa=z;
        y->push_up();
    }
    void splay(sn*x) {
        x->push_down();
        for(;!x->is_root();) {
            if(x->fa->is_root()) rot(x);
            else {
                if(x->fa->d() == x->d())
                    rot(x->fa);
                else rot(x);
                rot(x);
            }
        }
        x->push_up();
    }
    sn*access(sn*x, sn*y=NULL) {
        for(; x; y=x, x=x->fa) {
            splay(x);
            x->ch[1] = y;
            if(y) y->fa = x;
            x->push_up();
        }
        return y;
    }
    public:
    lct() {
        for(int i = 0; i < maxn; ++i)
            T[i] = new splay_node();
    }
    void set_fa(int u, int f) {
        T[u]->fa = T[f];
    }
    void modify(int p, int add) {
        access(T[p]);
        splay(T[p]);
        T[p]->a += add;
        T[p]->v += add;
        T[p]->s += T[p]->s*add;
    }
    int query(int p) {
        access(T[p]);
        splay(T[p]);
        return T[p]->s;
    }
} l;
vector<int> has[maxn];
struct Querys {
    int l, r, z, ansl, ansr;
    void read(int id) {
        fr(l, r, z);
        ansl = ansr = 0;
        has[l].pb(id);
        has[r + 1].pb(id);
    }
    void upd(int ans) {
        ansl = ansr, ansr = ans;
    }
} Q[maxn];
int n, q, f[maxn];
int val[maxn], fa[maxn];
int main() {
    fr(n, q);
    fa[0] = -1;
    rep(i, 1, n - 1)
        l.set_fa(i + 1, fr()+1);
    rep(i, 1, q) Q[i].read(i);
    rep(i, 0, n - 1) {
        l.modify(i + 1, 1);
        if(has[i+1].size() != 0) {
            for(int j = 0, sz = has[i+1].size(); j < sz; ++j) {
                int v = has[i+1][j];
                int add = l.query(Q[v].z + 1);
                Q[v].upd(add);
            }
        }
    }
    //return 0;
    rep(i, 1, q) {
        printf("%d\n", (Q[i].ansr - Q[i].ansl + 201314) % 201314);
    }
 
    return 0;
}
