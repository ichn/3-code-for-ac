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

const int maxn = 100000 + 100;
 
#define sqr(x) ((x) * (x))
#define lc ch[0]
#define rc ch[1]
struct splay_node {
	splay_node *fa, *ch[2];
	int val, size, mx, mn;
	bool rev;
	LL sum, sum2;
	splay_node() {
		fa = ch[0] = ch[1] = NULL;
		val = size = sum = sum2 = 0;
		rev = 0;
	}
	void push_up() {
		sum = val, size = 1, sum2 = sum * sum, mx = val, mn = val;
		if(lc)
			sum += lc->sum, size += lc->size, sum2 += lc->sum2, mx = max(mx, lc->mx), mn = min(mn, lc->mn);
		if(rc)
			sum += rc->sum, size += rc->size, sum2 += rc->sum2, mn = min(mn, rc->mn), mx = max(mx, rc->mx);
	}
	void push_down() {
		if(rev) {
			swap(lc, rc);
			if(lc) lc->rev ^= 1;
			if(rc) rc->rev ^= 1;
			rev = 0; // notice
		}
	}
	int d() {
		return this == this->fa->ch[0]; // notice: x->fa may be NULL wocaonimashoujiannaocan
	}
} T[maxn], *loc = T, *root;
void print(splay_node *t) {
	if(t == NULL) return ;
	t->push_down();
	print(t->lc);
	printf("this:%d fa:%d ch:%d %d size:%d val:%d\n", t, t->fa, t->lc, t->rc, t->size, t->val);
	print(t->rc);
}
void rot(splay_node *x) {
	splay_node *y = x->fa, *z = y->fa;
	if(z) z->push_down();
	y->push_down(), x->push_down(); // notice: Dot forget push_down()!
	int d = x->d();
	y->ch[d^1] = x->ch[d];
	if(x->ch[d]) x->ch[d]->fa = y;
	x->ch[d] = y, y->fa = x;
	x->fa = z;
	if(z) z->ch[z->ch[1] == y] = x;
	y->push_up();
}
void splay(splay_node *x, splay_node *goal = NULL) {
	if(x == goal) return ;
	while(x->fa != goal) {
		if(x->fa->fa == goal) rot(x);
		else {
			if(x->d() == x->fa->d())
				rot(x->fa);
			else {
				rot(x);
			}
			rot(x);
		}
	}
	x->push_up();
	if(goal == NULL) root = x;
}
void select(int k, splay_node *goal = NULL) {
	splay_node *u = root;
	int lsz;
	for(;;) {
		u->push_down();
		lsz = u->lc ? u->lc->size : 0;
		if(k <= lsz)
			u = u->lc;
		else if(lsz+1<k)
			k -= lsz+1, u = u->rc;
		else break;
	}
	splay(u, goal);
}

splay_node *lb, *rb, *tmp;
int n, q, v[maxn];
void build(int l, int r, splay_node *&x) {
	if(r < l) return ;
	int mid = r+l>>1;
	x = loc++;
	build(l, mid-1, x->lc);
	build(mid+1, r, x->rc);
	if(x->lc) x->lc->fa = x; // notice: Dot forget set ch->fa
	if(x->rc) x->rc->fa = x;
	x->val = v[mid];
	x->push_up();
}
void init() {
	fr(n, q);
	rep(i, 1, n) fr(v[i]);
	lb = loc++, rb = loc++;
	lb->size = 2, rb->size = 1, lb->rc = rb, rb->fa = lb, lb->val = rb->val = 0;
	root = lb;
	build(1, n, rb->lc);
	rb->lc->fa = rb; // notice: hehe
	rb->push_up(), lb->push_up(); // notice: Dot forget push_up()!
	//print(root);
}

DB calc(splay_node *x, LL v) {
	DB ave = (DB)(x->sum-v) / (x->size-1);
	return (DB)(x->sum2 - sqr(v) - (x->size-1) * sqr(ave)) / x->size;
}

void solve() {
	int l, r;
	while(q--) {
		if(gchar() == 'r') {
			fr(l, r);
			select(l), select(r+2, root);
			tmp = root->rc->lc;
			tmp->rev ^= 1;
			tmp->push_down();
		} else {
			fr(l, r);
			select(l);
			select(r+2, root);
			tmp = root->rc->lc;
			DB ans = min(calc(tmp, tmp->mx), calc(tmp, tmp->mn));
			printf("%lf\n", ans);
		}
	}
}

int main() {
	file(cheat);
	init();
	solve();
 
	return 0;
}


