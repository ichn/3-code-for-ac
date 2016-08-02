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

// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你深爱着的

const int maxn = 3e5 + 10000;
struct Edge {
	int u, v, w;
	bool operator < (const Edge&rhs) const {
		return w < rhs.w;
	}
} e[maxn*2];

int n, m, q, t;
int pos[maxn];
LL last_ans, ans;

namespace LinkCutTree {
	const int maxNode = 2e5 + 10000;

#define ln lct_node
	//#define np np
#define lc ch[0]
#define rc ch[1]

	struct lct_node {
		ln *ch[2], *fa, *mx; // 儿子，父亲，splay树中子树的最大值
		int val, rev, x; // 权值，翻转标记，如果是边节点，代表边的编号
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
		}
		void up() {
			mx = this;
			if (lc && lc->mx->val > mx->val)
				mx = lc->mx;
			if (rc && rc->mx->val > mx->val)
				mx = rc->mx;
		}
		void set_c(ln*son, int d) {
			ch[d] = son;
			if (son) son->fa = this;
		}
	} np[maxNode];

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

	queue<int> que;
	int pt[maxn];

	void add_edge(ln*a, ln*b, int i) {
		make_root(a);
		access(b);
		splay(a);
		if (find_root(b) == a) {
			ln*p = a->mx;
			cut(p, &np[e[pt[p->x]].u]);
			cut(p, &np[e[pt[p->x]].v]);
			que.push(p->x);
			pos[pt[p->x]] = i;
		}
		int p = que.front();
		que.pop();
		np[p].x = p;
		np[p].val = i;
		np[p].ch[0] = np[p].ch[1] = np[p].fa = NULL;
		np[p].rev = 0;
		link(a, &np[p]);
		link(b, &np[p]);
		pt[p] = i;
	}

	void pretreatment() {
		for (int i = 0; i <= n*2; ++i) {
			np[i].lc = np[i].rc = np[i].fa = np[i].mx = NULL;
			np[i].val = np[i].rev = 0;
		}
		while (!que.empty()) que.pop();
		for (int i = n+1; i < 2*n; ++i) {
			que.push(i);
		}
		red(i, m, 1) {
			int u = e[i].u, v = e[i].v;
			add_edge(&np[u], &np[v], i);
		}
	}
};

namespace ChairManTree {
#define cn cmt_node
#define lc ch[0]
#define rc ch[1]

	struct cmt_node {
		cn*ch[2];
		LL w;
	} np[maxn*30], *root[maxn], *loc = np;

	cn*new_node() {
		loc->lc = loc->rc = 0;
		loc->w = 0;
		return loc++;
	}

	cn* build_tree(int l, int r) {
		cn*x = new_node();
		if (l == r) return x;
		int mid=(l+r)>>1;
		x->lc = build_tree(l, mid);
		x->rc = build_tree(mid+1, r);
		return x;
	}

	cn* make_chg(int l, int r, int pos, int add, cn*u) {
		cn* v = new_node();
		v->lc = u->lc, v->rc = u->rc, v->w = u->w + add;
		if (l == r) return v;
		int mid = (l+r)>>1;
		if (pos <= mid) {
			v->lc = make_chg(l, mid, pos, add, v->lc);
		} else {
			v->rc = make_chg(mid+1, r, pos, add, v->rc);
		}
		return v;
	}

	LL query(cn*a, cn*b, int q, int l, int r) {
		if (l == r) return b->w - a->w;
		int mid = (l+r)>>1;
		if (q <= mid) return query(a->lc, b->lc, q, l, mid);
		return query(a->rc, b->rc, q, mid+1, r)+b->lc->w-a->lc->w;
	}

	LL query(int l, int r) {
		return query(root[l-1], root[r], l-1, 0, m);
	}
};

class _3_14_xllend3_road {

	int b[maxn];

	public:
		void solve() {
			fr(t);
			fr(n, m, q);
			rep(i, 1, m) {
				fr(e[i].u, e[i].v, e[i].w);
			}
			sort(e+1, e+m+1);
			rep(i, 1, m)
				b[i] = e[i].w;
			LinkCutTree::pretreatment();
			using namespace ChairManTree;
			root[0] = build_tree(0, m);
			rep(i, 1, m) {
				root[i] = make_chg(0, m, pos[i], e[i].w, root[i-1]);
			}
			last_ans = 0;
			int u, v;
			rep(i, 1, q) {
				fr(u, v);
				if (t) {
					u ^= last_ans;
					v ^= last_ans;
				}
				u = upper_bound(b+1, b+m+1, u-1)-b;
				v = upper_bound(b+1, b+m+1, v)-b-1;
				printf("%lld\n", last_ans = query(u, v));
			}
		}
};

int main() {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);

	(new _3_14_xllend3_road)->solve();

	return 0;

}

