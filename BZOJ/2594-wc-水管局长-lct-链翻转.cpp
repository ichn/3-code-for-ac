
#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
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
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
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
};
using namespace my_useful_tools;

const int maxn = 100000 + 10;
const int maxq = 100000 + 10;
const int maxm = 1000000 + 10;
 
int n, m, q;

#define ln lct_node
#define lc ch[0]
#define rc ch[1]
class LCT_rev_chain {
	public:
	struct lct_node {
		ln *fa, *ch[2], *mx;
		int val, rev;
		lct_node() {
			fa = lc = rc = NULL;
			mx = this;
			rev = 0;
			val = 0;
		}
		inline int d() {
			return this==fa->ch[0];
		}
		inline bool is_root() {
			return fa==NULL || (fa->lc!=this && fa->rc!=this);
		}
		inline void push_up() {
			mx = this;
			if (lc) {
				if (mx->val < lc->mx->val)
					mx = lc->mx;
			}
			if (rc) {
				if (mx->val < rc->mx->val)
					mx = rc->mx;
			}
		}
		inline void push_down() {
			if (rev) {
				if (lc) lc->rev^=1;
				if (rc) rc->rev^=1;
				swap(lc, rc);
				rev ^= 1;
			}
		}
	} t[maxn*2], *loc;
	inline void rot(ln*x) {
		ln *y=x->fa, *z=y->fa;
		y->push_down(),
		x->push_down();
		int d = x->d();
		y->ch[d^1] = x->ch[d];
		if (x->ch[d]) x->ch[d]->fa = y;
		if (!y->is_root()) z->ch[z->ch[1]==y] = x;
		x->ch[d]=y, y->fa=x;
		x->fa = z;
		y->push_up();
	}
	inline void splay(ln*x) {
		for(x->push_down(); !x->is_root(); rot(x))
			if (!x->fa->is_root()) {
				if (x->fa->d() == x->d())
					rot(x->fa);
				else rot(x);
			}
		x->push_up();
	}
	inline ln*access(ln*x, ln*y=NULL) {
		for (; x; y=x, x=x->fa) {
			splay(x);
			x->ch[1] = y;
			x->push_up();
		}
		return y;
	}
	inline void evert(ln*u) {
		access(u)->rev ^= 1;
	//	printf("%d\n", u->is_root());
	//	u->push_down();
		splay(u);
	}
	inline void link(ln*u, ln*v) {
		evert(v);
		v->fa = u;
		access(v);
	}
	inline void cut(ln*u, ln*v) {
		evert(u);
		access(v);
		splay(v);
		v->ch[0]=NULL, u->fa=NULL;
		u->push_up(), v->push_up();
	}
	inline int query(ln*u, ln*v) {
		evert(u);
		access(v);
		splay(u);
		return u->mx->val;
	}
} lct;

// 给出的边
struct Edge {
	int u, v, w;
	Edge() {
	}
	inline void read() {
		fr(u, v, w);
		if (v < u)
			swap(u, v);
	}
	Edge(int u, int v, int w):u(u), v(v), w(w) {
	}
	bool operator < (const Edge&rhs) const {
		return u<rhs.u || (u==rhs.u && v<rhs.v);
	}
} E[maxm];

bool exi[maxm];
int ope[maxq], a[maxq], b[maxq], pos[maxq];

int fa[maxn];
inline int findfa(int x) {
	return fa[x]==x ? x : fa[x]=findfa(fa[x]);
}

void add_edge(int i) {
	int a=E[i].u, b=E[i].v, w=E[i].w;
	LCT_rev_chain::ln *u=lct.t+a, *v=lct.t+b;
	if (findfa(a) != findfa(b)) {
		LCT_rev_chain::ln *e = ++lct.loc;
		e->val = w;
		lct.link(u, e);
		lct.link(v, e);
		fa[findfa(a)] = findfa(b);
	} else {
		lct.evert(u);
		lct.access(v);
		lct.splay(u);
		if (u->mx->val > w) {
			LCT_rev_chain::ln *e = u->mx;
			lct.cut(u, e);
			lct.cut(v, e);
			e->val = w;
			lct.link(e, u);
			lct.link(e, v);
		}
	}
}

vector<int> ans;
 
int main() {
#ifdef love_lhy
	file(2594);
#endif

	fr(n, m, q);
	rep(i, 1, m) {
		E[i].read();
		exi[i] = true;
	}
	sort(E+1, E+m+1);
	for (int i=1; i<=q; ++i) {
		fr(ope[i], a[i], b[i]);
		if (b[i] < a[i])
			swap(a[i], b[i]);
		if (ope[i] == 2) {
			exi[pos[i] = lower_bound(E+1, E+m+1, Edge(a[i], b[i], 0))-E] = false;
		}
	}
	rep(i, 1, n) fa[i] = i;
	lct.loc = lct.t+n+1;
	for (int i=1; i<=m; ++i) {
		if (exi[i]) {
			add_edge(i);
		}
	}
	red (i, q, 1) {
		if (ope[i] == 1) {
			ans.pb(lct.query(lct.t+a[i], lct.t+b[i]));
		} else {
			add_edge(pos[i]);
		}
	}
	//return 0;
	for (int i=ans.size()-1; 0<=i; --i)
		printf("%d\n", ans[i]);
 
	return 0;
}

