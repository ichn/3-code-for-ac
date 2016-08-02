#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
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


const int maxn = 3e5 + 100;
const int mod = 51061;

#define ln lct_node
#define lc ch[0]
#define rc ch[1]
struct lct_node {
	ln*fa, *ch[2];
	int val, sum, sz, mv, av;
	bool rev;
	bool is_r() {
		return !fa || (this!=fa->lc && this!=fa->rc);
	}
	int d() {
		return fa->ch[0] == this;
	}
	void set_c(ln*son, int p) {
		ch[p] = son;
		if (son) son->fa = this;
	}
	void up() {
		sum = val;
		sz = 1;
		if (lc) {
			sum += lc->sum;
			sum %= mod;
			sz += lc->sz;
		}
		if (rc) {
			sum += rc->sum;
			sum %= mod;
			sz += rc->sz;
		}
	}
	void down() {
		if (rev) swap(lc, rc);
		if (lc) lc->rev ^= rev;
		if (rc) rc->rev ^= rev;
		rev = false;
		rep(i, 0, 1)
			if (ch[i]) {
				ch[i]->val = (LL)ch[i]->val*mv % mod;
				ch[i]->sum = (LL)ch[i]->sum*mv % mod;
				ch[i]->mv = (LL)ch[i]->mv*mv % mod;
				ch[i]->av = (LL)ch[i]->av*mv % mod;

				ch[i]->val = (ch[i]->val+av) % mod;
				ch[i]->sum = (ch[i]->sum+av*ch[i]->sz%mod) % mod;
				ch[i]->av = (ch[i]->av+av) % mod;
			}
		av = 0;
		mv = 1;
	}
} np[maxn], *loc = np;

void rot(ln*x) {
	ln*y = x->fa;
	int d = x->d();
	y->set_c(x->ch[d], d^1);
	x->fa = y->fa;
	if (!y->is_r())
		y->fa->ch[y->fa->ch[1]==y] = x;
	x->set_c(y, d);
	y->up();
}

ln* stk[maxn];
int top;
void splay(ln*x) {
	for (stk[top=1]=x; !stk[top]->is_r(); ++top, stk[top]=stk[top-1]->fa);
	for (; 0<top; stk[top]->down(), --top);
	for (ln*y = x->fa; !x->is_r(); rot(x), y=x->fa) {
		if (!y->is_r()) {
			if (y->d() == x->d())
				rot(y);
			else rot(x);
		}
	}
	x->up();
}

ln*access(ln*x) {
	ln*y = NULL;
	for (; x; y=x, x=x->fa) {
		splay(x);
		x->set_c(y, 1);
		x->up();
	}
	return y;
}

void make_root(ln*x) {
	access(x);
	splay(x);
	x->rev^=1;
}

void link(ln*x, ln*y) {
	make_root(x);
	x->fa = y;
}

ln* find_root(ln*x) {
	while (!x->is_r()) x = x->fa;
	return x;
}

void cut(ln*x, ln*y) {
	make_root(x);
	access(y);
	splay(x);
	if (x->ch[1] == y) {
		x->ch[1] = y->fa = NULL;
		x->up();
	}
}

void modify(ln*x, int val) {
	access(x);
	splay(x);
	x->val = val;
	x->up();
}

int n, m, a, b;
ln* x, * y;

int e;
int h[maxn], t[maxn*2], nxt[maxn*2];
void addEdge(int u, int v) {
	nxt[e]=h[u],t[e]=v,h[u]=e++;
	nxt[e]=h[v],t[e]=u,h[v]=e++;
}
void dfs(int u, int fa) {
	for (int i=h[u]; i != -1; i=nxt[i]) {
		if (t[i] != fa) {
			np[t[i]].fa = &np[u];
			dfs(t[i], u);
		}
	}
}
int main() {
	freopen("2631.in", "r", stdin);
	freopen("2631.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif

	fr(n, m);
	for (int i = 1; i <= n; ++i) {
		np[i].lc = np[i].rc = np[i].fa = NULL;
		np[i].rev = 0;
		np[i].av = 0, np[i].mv = 1, np[i].sz = 1;
		np[i].val = np[i].sum = 1;
	}
	e = 0, pse(h, -1);
	rep(i, 2, n) {
		addEdge(fr(), fr());
	}
	dfs(1, -1);
	int u, v, c;
	while (m--) {
		char ope = gchar();
		if (ope == '+') {
			fr(u, v, c);
			make_root(&np[u]);
			access(&np[v]);
			splay(&np[v]);
			c %= mod;
			np[v].av += c;
			np[v].val += c;
			np[v].sum += (LL)np[v].sz*c%mod;
			np[v].av %= mod;
			np[v].val %= mod;
			np[v].sum %= mod;
		}
		if (ope == '-') {
			fr(u, v);
			cut(&np[u], &np[v]);
			fr(u, v);
			link(&np[u], &np[v]);
		}
		if (ope == '*') {
			fr(u, v, c);
			make_root(&np[u]);
			access(&np[v]);
			splay(&np[v]);
			c %= mod;
			np[v].mv = (LL)np[v].mv*c%mod;
			np[v].val = (LL)np[v].val*c%mod;
			np[v].sum = (LL)np[v].sum*c%mod;
			np[v].av = (LL)np[v].av*c%mod;
		}
		if (ope == '/') {
			fr(u, v);
			make_root(&np[u]);
			access(&np[v]);
			splay(&np[v]);
			printf("%d\n", np[v].sum%mod);
		}
	}

	return 0;
}
