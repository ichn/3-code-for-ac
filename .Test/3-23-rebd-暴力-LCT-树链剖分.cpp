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
//#define generator_sbit

// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你所深爱着的
// 永远不要相信自己的意志力

const int maxn = 1e5 + 100;
const int maxe = maxn * 2;
int n, q;
double val[maxn];

int head[maxn], to[maxe], next[maxe], edge;
void init() {
	edge = 0;
	memset(head, -1, sizeof head);
}
void addEdge(int u, int v) {
	next[edge] = head[u], to[edge] = v, head[u] = edge++;
	next[edge] = head[v], to[edge] = u, head[v] = edge++;
}
char ope[10];
class bf {
	int fa[maxn];
	int size[maxn];

	void dfs(int u, int f) {
		for (int i = head[u]; i != -1; i = next[i]) {
			if (to[i] != f) {
				fa[to[i]] = u;
				dfs(to[i], u);
			}
		}
	}
	void add_val(int a, int b, double c) {
		dfs(a, -1);
		while (b != a) {
			val[b] += c;
			b = fa[b];
		}
		val[a] += c;
	}
	void add_val(int a, double c) {
		val[a] += c;
		for (int i = head[a];  i != -1; i = next[i]) {
			if (to[i] != fa[a]) {
				add_val(to[i], c);
			}
		}
	}
	void set_arv(int a, int b) {
		dfs(a, -1);
		double cnt = 0.0;
		int p = b;
		int sz = 0;
		while (b != a) {
			cnt += val[b];
			b = fa[b];
			++sz;
		}
		cnt += val[a];
		++sz;
		cnt /= sz;
		b = p;
		while (b != a) {
			val[b] = cnt;
			b = fa[b];
		}
		val[a] = cnt;
	}
	void get_sum(int a, double&cnt) {
		cnt += val[a];
		size[a] = 1;
		for (int i = head[a]; i != -1; i = next[i]) {
			if (to[i] != fa[a]) {
				get_sum(to[i], cnt);
				size[a] += size[to[i]];
			}
		}
	}
	void set_val(int a, double c) {
		val[a] = c;
		for (int i = head[a];  i != -1; i = next[i]) {
			if (to[i] != fa[a]) {
				set_val(to[i], c);
			}
		}
	}
	void set_arv(int a) {
		double cnt = 0.0;
		get_sum(a, cnt);
		cnt = cnt / size[a];
		set_val(a, cnt);
	}
	void solve_val(int a, int b) {
		fa[a] = -1;
		dfs(a, -1);
		double mx = -1e30, mn = 1e30, sum = 0.0;
		while (b != a) {
			mx = max(mx, val[b]);
			mn = min(mn, val[b]);
			sum += val[b];
			b = fa[b];
		}
		mx = max(mx, val[a]);
		mn = min(mn, val[a]);
		sum += val[a];
		printf("%lf %lf %lf\n", mn, mx, sum);
	}
	void solve_val_dfs(int a, double&mx, double&mn, double&sum) {
		mx = max(mx, val[a]), mn = min(mn, val[a]), sum += val[a];
		for (int i = head[a]; i != -1; i = next[i]) {
			if (to[i] != fa[a]) {
				solve_val_dfs(to[i], mx, mn, sum);
			}
		}
	}
	void solve_val(int a) {
		double mx = -1e30, mn = 1e30, sum = 0.0;
		solve_val_dfs(a, mx, mn, sum);
		printf("%lf %lf %lf\n", mn, mx, sum);
	}
	public:
	void solve() {
		int a, b;
		double c;
		for (int i = 1; i <= n; ++i) {
			val[i] = 0.0;
		}
		while (q--) {
			scanf("%s", ope);
			if (ope[0] == 'N') {
				if (ope[1] != 'N') {
					fr(a, b);
					scanf("%lf", &c);
					add_val(a, b, c);
				}
				if (ope[1] == 'N') {
					fr(a);
					scanf("%lf", &c);
					fa[1] = -1;
					dfs(1, -1);
					add_val(a, c);
				}
			} else if (ope[0] == 'F') {
				if (ope[1] != 'F') {
					fr(a, b);
					set_arv(a, b);
				}
				if (ope[1] == 'F') {
					fr(a);
					fa[1] = -1;
					dfs(1, -1);
					set_arv(a);
				}
			} else if (ope[0] == 'C') {
				if (ope[1] != 'C') {
					fr(a, b);
					solve_val(a, b);
				}
				if (ope[1] == 'C') {
					fr(a);
					fa[1] = -1;
					dfs(1, -1);
					solve_val(a);
				}
			}
		}
	}
};
const int maxNode = 1e5 + 10000;
#define ln lct_node
#define lc ch[0]
#define rc ch[1]
struct lct_node {
	ln *ch[2], *fa;
	double val, set_val, sum, mx, mn, add_val;
	bool ss, aa;
	int rev, size;
	bool is_r() {
		return !fa || (fa->lc != this && fa->rc != this);
	}
	int d() { // 很不自然的定义，不过我习惯了。。表示旋转后父亲是当前节点的什么儿子（0左，1右）
		return this == fa->ch[0];
	}
	void down() {
		if (rev) {
			if (lc) lc->rev ^= 1;
			if (rc) rc->rev ^= 1;
			swap(lc, rc);
			rev = 0;
		}

		if (aa) {
			if (lc) {
				lc->aa = 1;
				lc->add_val += add_val;
				lc->set_val += add_val;
				lc->val += add_val;
				lc->sum += add_val * lc->size;
				lc->mx += add_val;
				lc->mn += add_val;
			}
			if (rc) {
				rc->aa = 1;
				rc->add_val += add_val;
				rc->set_val += add_val;
				rc->val += add_val;
				rc->sum += add_val * rc->size;
				rc->mx += add_val;
				rc->mn += add_val;
			}
			aa = 0;
			add_val = 0;
		}
		if (ss) {
			if (lc) {
				lc->ss = 1;
				lc->aa = 0;
				lc->add_val = 0.0;
				lc->val = lc->set_val = set_val;
				lc->sum = set_val * lc->size;
				lc->mx = lc->mn = set_val;
			}
			if (rc) {
				rc->ss = 1;
				rc->aa = 0;
				rc->add_val = 0.0;
				rc->val = rc->set_val = set_val;
				rc->sum = set_val * rc->size;
				rc->mx = rc->mn = set_val;
			}
			ss = 0;
			set_val = 0.0;
		}
	}
	void up() {
		mx = mn = val;
		sum = val;
		size = 1;
		if (lc) {
			mx = max(mx, lc->mx);
			mn = min(mn, lc->mn);
			sum +=       lc->sum;
			size += lc->size;
		}
		if (rc) {
			mx = max(mx, rc->mx);
			mn = min(mn, rc->mn);
			sum +=       rc->sum;
			size += rc->size;
		}
	}
	void set_c(ln*son, int d) {
		ch[d] = son;
		if (son) son->fa = this;
	}
} np[maxNode];
class TreeChainFrac {
	void rot(ln*x) {
		ln*y = x->fa;
		int d = x->d();
		y->set_c(x->ch[d], d^1);
		x->fa = y->fa; // notice!
		if (!y->is_r())
			y->fa->set_c(x, y->fa->rc == y);
		x->set_c(y, d);
		y->up();
	}
	ln*stk[maxNode];
	int top;
	void splay(ln*x) {
		for (stk[top=1] = x; !stk[top]->is_r(); ++top, stk[top] = stk[top-1]->fa);
		for (; top; stk[top]->down(), --top);
		for (ln*y = x->fa; !x->is_r(); rot(x), y = x->fa) {
			if (!y->is_r()) {
				if (x->d() == y->d())
					rot(y);
				else rot(x);
			}
		}
		x->up();
	}
	ln*access(ln*x) {
		ln*y = NULL;
		for(; x; y=x, x=x->fa) {
			splay(x);
			x->set_c(y, 1);
			x->up();
		}
		return y;
	}
	void make_root(ln*x) {
		access(x);
		splay(x);
		x->rev ^= 1;
	}
	void link(ln*x, ln*y) {
		make_root(x);
		x->fa = y;
	}
	void cut(ln*x, ln*y) {
		make_root(x);
		access(y);
		splay(x);
		x->ch[1] = y->fa = NULL;
		x->up();
	}
	ln* find_root(ln* x) {
		while (!(x->is_r()))
			x = x->fa;
		return x;
	}

	int f[maxn];
	void dfs_f(int u, int ff) {
		for (int i = head[u]; i != -1; i = next[i]) {
			if (to[i] != ff) {
				f[to[i]] = u;
				dfs_f(to[i], u);
			}
		}
	}

	public:
	void solve() {
		for (int i = 1; i <= n; ++i) {
			np[i].lc = np[i].rc = np[i].fa = NULL;
			np[i].val = np[i].rev = np[i].mx = np[i].mn = np[i].add_val = np[i].set_val = 0.0;
			np[i].aa = np[i].ss = false;
		}
		dfs_f(1, -1);
		for (int i = 1; i <= n; ++i) {
			np[i].fa = &np[f[i]];
		}

		int u, v;
		double c;
		while (q--) {
			scanf("%s", ope);
			if (ope[0] == 'N') {
				fr(u, v);
				scanf("%lf", &c);
				ln*a = &np[u], *b = &np[v];
				make_root(a);
				access(b);
				splay(a);
				a->aa = 1;
				a->add_val += c;
				a->set_val += c;
				a->val += c;
				a->sum += c*a->size;
				a->mx += c;
				a->mn += c;
			} else if (ope[0] == 'F') {
				fr(u, v);
				ln*a = &np[u], *b = &np[v];
				make_root(a);
				access(b);
				splay(a);
				double sum = a->sum;
				sum /= a->size;
				a->set_val = sum;
				a->ss = 1;
				a->val = sum;
				a->mx = a->mn = sum;
			} else if (ope[0] == 'C') {
				fr(u, v);
				ln*a = &np[u], *b = &np[v];
				make_root(a);
				access(b);
				splay(a);
				printf("%lf %lf %lf\n", a->mn, a->mx, a->sum);
			}
		}
	}
};


int id[maxn], dfi[maxn];
bool my_cmp(int x, int y) {
	return dfi[x] < dfi[y];
}
class SLPF {
	int sz[maxn], top[maxn], fa[maxn], son[maxn], pos[maxn], dep[maxn], chf[maxn], cnt;
	int dfl[maxn], dfs_clock;
	void dfs(int u) {
		sz[u] = 1;
		for (int i = head[u]; i != -1; i = next[i]) {
			if (to[i] != fa[u]) {
				fa[to[i]] = u;
				dep[to[i]] = dep[u]+1;
				dfs(to[i]);
				sz[u] += sz[to[i]];
			}
		}
	}
	void get_chain(int u) {
		top[u] = cnt;
		int hs = -1, son = -1;
		for (int i = head[u]; i != -1; i = next[i]) {
			if (to[i] != fa[u] && sz[to[i]] > hs) {
				hs = sz[to[i]];
				son = to[i];
			}
		}
		if (son != -1) {
			get_chain(son);
			for (int i = head[u]; i != -1; i = next[i]) {
				if (to[i] != fa[u] && to[i] != son) {
					++cnt;
					chf[cnt] = to[i];
					get_chain(to[i]);
				}
			}
		}
	}
	void get_dfn(int u) {
		dfi[u] = ++dfs_clock;
		int son = -1;
		for (int i = head[u]; i != -1; i = next[i]) {
			if (to[i] != fa[u] && top[to[i]] == top[u]) {
				son = to[i];
				break;
			}
		}
		if (son == -1) {
			dfl[u] = dfs_clock;
			return ;
		}
		get_dfn(son);
		for (int i = head[u]; i != -1; i = next[i]) {
			if (to[i] != fa[u] && to[i] != son) {
				get_dfn(to[i]);
			}
		}
		dfl[u] = dfs_clock;
	}

	double tr[maxn<<2], mx[maxn<<2], mn[maxn<<2], sum[maxn<<2], sv[maxn<<2], av[maxn<<2];
	bool ss[maxn<<2], aa[maxn<<2];
	int rg[maxn<<2];
	void up(int rt) {
		mx[rt] = max(mx[rt<<1], mx[rt<<1|1]);
		mn[rt] = min(mn[rt<<1], mn[rt<<1|1]);
		sum[rt] = sum[rt<<1] + sum[rt<<1|1];
	}
	void down(int rt) {
		if (aa[rt]) {
			aa[rt<<1] = 1;
			av[rt<<1] += av[rt];
			tr[rt<<1] += av[rt];
			mx[rt<<1] += av[rt];
			mn[rt<<1] += av[rt];
			sv[rt<<1] += av[rt];
			sum[rt<<1] += rg[rt<<1]*av[rt];
			aa[rt<<1|1] = 1;
			av[rt<<1|1] += av[rt];
			tr[rt<<1|1] += av[rt];
			mx[rt<<1|1] += av[rt];
			mn[rt<<1|1] += av[rt];
			sv[rt<<1|1] += av[rt];
			sum[rt<<1|1] += rg[rt<<1|1]*av[rt];
			aa[rt] = 0;
			av[rt] = 0.0;
		}
		if (ss[rt]) {
			ss[rt<<1] = 1;
			sv[rt<<1] = sv[rt];
			aa[rt<<1] = 0;
			av[rt<<1] = 0.0;
			mx[rt<<1] = sv[rt];
			mn[rt<<1] = sv[rt];
			tr[rt<<1] = sv[rt];
			sum[rt<<1] = rg[rt<<1]*sv[rt];
			ss[rt<<1|1] = 1;
			sv[rt<<1|1] = sv[rt];
			aa[rt<<1|1] = 0;
			av[rt<<1|1] = 0.0;
			mx[rt<<1|1] = sv[rt];
			mn[rt<<1|1] = sv[rt];
			tr[rt<<1|1] = sv[rt];
			sum[rt<<1|1] = rg[rt<<1|1]*sv[rt];
			ss[rt] = 0;
		}
	}
	void build_tree(int l, int r, int rt) {
		rg[rt] = r-l+1;
		if (l == r) {
			tr[rt] = mx[rt] = mn[rt] = sum[rt] = sv[rt] = av[rt] = 0.0;
			ss[rt] = aa[rt] = 0;
			return ;
		}
		int mid=(l+r)>>1;
		build_tree(l, mid, rt<<1);
		build_tree(mid+1, r, rt<<1|1);
		up(rt);
	}
	void s_val(int ql, int qr, double v, int l, int r, int rt) {
		if (ql <= l && r <= qr) {
			sv[rt] = v;
			ss[rt] = 1;
			aa[rt] = 0;
			av[rt] = 0;
			mx[rt] = mn[rt] = tr[rt] = v;
			sum[rt] = v*rg[rt];
			return ;
		}
		int mid=(l+r)>>1;
		down(rt);
		if (ql <= mid) {
			s_val(ql, qr, v, l, mid, rt<<1);
		}
		if (mid < qr) {
			s_val(ql, qr, v, mid+1, r, rt<<1|1);
		}
		up(rt);
	}
	void a_val(int ql, int qr, double v, int l, int r, int rt) {
		if (ql <= l && r <= qr) {
			sv[rt] += v;
			aa[rt] = 1;
			av[rt] += v;
			mx[rt] += v;
			mn[rt] += v;
			tr[rt] += v;
			sum[rt] += v*rg[rt];
			return ;
		}
		int mid=(l+r)>>1;
		down(rt);
		if (ql <= mid) {
			a_val(ql, qr, v, l, mid, rt<<1);
		}
		if (mid < qr) {
			a_val(ql, qr, v, mid+1, r, rt<<1|1);
		}
		up(rt);
	}
	double q_max(int ql, int qr, int l, int r, int rt) {
		if (ql <= l && r <= qr) {
			return mx[rt];
		}
		int mid=(l+r)>>1;
		down(rt);
		double ret = -1e30;
		if (ql <= mid) {
			ret = max(ret, q_max(ql, qr, l, mid, rt<<1));
		}
		if (mid < qr) {
			ret = max(ret, q_max(ql, qr, mid+1, r, rt<<1|1));
		}
		return ret;
	}
	double q_min(int ql, int qr, int l, int r, int rt) {
		if (ql <= l && r <= qr) {
			return mn[rt];
		}
		int mid=(l+r)>>1;
		down(rt);
		double ret = 1e30;
		if (ql <= mid) {
			ret = min(ret, q_min(ql, qr, l, mid, rt<<1));
		}
		if (mid < qr) {
			ret = min(ret, q_min(ql, qr, mid+1, r, rt<<1|1));
		}
		return ret;
	}
	double q_sum(int ql, int qr, int l, int r, int rt) {
		if (ql <= l && r <= qr) {
			return sum[rt];
		}
		int mid=(l+r)>>1;
		down(rt);
		double ret = 0.0;
		if (ql <= mid) {
			ret += q_sum(ql, qr, l, mid, rt<<1);
		}
		if (mid < qr) {
			ret += q_sum(ql, qr, mid+1, r, rt<<1|1);
		}
		return ret;
	}

	void a_road(int a, int b, double v) {
		if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		while (top[a] != top[b]) {
			a_val(pos[chf[top[a]]], pos[a], v, 1, n, 1);
			a = fa[chf[top[a]]];
			if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		}
		if (dep[a] < dep[b]) swap(a, b);
		a_val(pos[b], pos[a], v, 1, n, 1);
	}
	void s_road(int a, int b, double v) {
		if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		while (top[a] != top[b]) {
			s_val(pos[chf[top[a]]], pos[a], v, 1, n, 1);
			a = fa[chf[top[a]]];
			if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		}
		if (dep[a] < dep[b]) swap(a, b);
		s_val(pos[b], pos[a], v, 1, n, 1);
	}
	int q_road_len(int a, int b) {
		int len = 0;
		if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		while (top[a] != top[b]) {
			len += pos[a] - pos[chf[top[a]]] + 1;
			a = fa[chf[top[a]]];
			if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		}
		if (dep[a] < dep[b]) swap(a, b);
		len += pos[a] - pos[b] + 1;
		return len;
	}
	double q_road_min(int a, int b) {
		double ret = 1e30;
		if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		while (top[a] != top[b]) {
			ret = min(ret, q_min(pos[chf[top[a]]], pos[a], 1, n, 1));
			a = fa[chf[top[a]]];
			if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		}
		if (dep[a] < dep[b]) swap(a, b);
		ret = min(ret, q_min(pos[b], pos[a], 1, n, 1));
		return ret;
	}
	double q_road_max(int a, int b) {
		double ret = 0.0;
		if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		while (top[a] != top[b]) {
			ret = max(ret, q_max(pos[chf[top[a]]], pos[a], 1, n, 1));
			a = fa[chf[top[a]]];
			if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		}
		if (dep[a] < dep[b]) swap(a, b);
		ret = max(ret, q_max(pos[b], pos[a], 1, n, 1));
		return ret;
	}
	double q_road_sum(int a, int b) {
		double ret = 0.0;
		if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		while (top[a] != top[b]) {
			ret += q_sum(pos[chf[top[a]]], pos[a], 1, n, 1);
			a = fa[chf[top[a]]];
			if (dep[chf[top[a]]] < dep[chf[top[b]]]) swap(a, b);
		}
		if (dep[a] < dep[b]) swap(a, b);
		ret += q_sum(pos[b], pos[a], 1, n, 1);
		return ret;
	}


	public:
		void solve() {
			fa[1] = 0;
			dep[1] = dep[0] = 1;
			dfs(1);
			chf[1] = 1;
			cnt = 1;
			get_chain(1);
			top[0] = top[1];
			dfs_clock = 0;
			get_dfn(1);
			rep(i, 1, n)
				id[i] = i;
			sort(id+1, id+n+1, my_cmp);
			rep(i, 1, n) {
				pos[id[i]] = i;
			}
			build_tree(1, n, 1);
			int a, b;
			double c;
			while (q--) {
				scanf("%s", ope);
				if (ope[1] != '\0') {
					fr(a);
					if (ope[0] == 'N') {
						scanf("%lf", &c);
						a_val(dfi[a], dfl[a], c, 1, n, 1);
					}
					if (ope[0] == 'F') {
						double arv = q_sum(dfi[a], dfl[a], 1, n, 1)/(dfl[a]-dfi[a]+1);
						s_val(dfi[a], dfl[a], arv, 1, n, 1);
					}
					if (ope[0] == 'C') {
						printf("%lf %lf %lf\n", q_min(dfi[a], dfl[a], 1, n, 1), q_max(dfi[a], dfl[a], 1, n, 1), q_sum(dfi[a], dfl[a], 1, n, 1));
					}
				} else {
					fr(a, b);
					if (ope[0] == 'N') {
						scanf("%lf", &c);
						a_road(a, b, c);
					}
					if (ope[0] == 'F') {
						double arv = q_road_sum(a, b)/q_road_len(a, b);
						s_road(a, b, arv);
					}
					if (ope[0] == 'C') {
						printf("%lf %lf %lf\n", 
								q_road_min(a, b),
								q_road_max(a, b),
								q_road_sum(a, b));
					}
				}
			}
		}
};

int main() {
	freopen("rebd.in", "r", stdin);
	freopen("rebd.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif
	int pt;
	scanf("%d", &pt);
	fr(n, q);
	init();
	//pt = 7;
	rep(i, 2, n) {
		int u, v;
		fr(u, v);
		addEdge(u, v);
	}
	if (pt <= 2) {
		(new bf)->solve();
	} else if (pt <= 5) {
		(new TreeChainFrac)->solve();
	} else {
		(new SLPF)->solve();
	}
	return 0;
}
