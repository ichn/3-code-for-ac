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

const int maxn = 3e5 + 100;

#define ln lct_node
#define lc ch[0]
#define rc ch[1]
struct lct_node {
	ln*fa, *ch[2];
	int val, sum;
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
		if (lc) sum ^= lc->sum;
		if (rc) sum ^= rc->sum;
	}
	void down() {
		if (rev) swap(lc, rc);
		if (lc) lc->rev ^= rev;
		if (rc) rc->rev ^= rev;
		rev = false;
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

int n, m, t, a, b;
ln* x, * y;

int main() {
	freopen("Tree.in", "r", stdin);
	freopen("Tree.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif

	fr(n, m);
	for (int i = 1; i <= n; ++i) {
		np[i].lc = np[i].rc = np[i].fa = NULL;
		np[i].rev =0;
		np[i].val = np[i].sum = fr();
	}
	while (m--) {
		fr(t, a, b);
		x = &np[a];
		if (t == 0) {
			y = &np[b];
			make_root(x);
			access(y);
			splay(y);
			printf("%d\n", y->sum);
		} else if (t == 1) {
			y = &np[b];
			make_root(y);
			access(x);
			if (find_root(x) != y) {
				y->fa = x;
			}
		} else if (t == 2) {
			y = &np[b];
			cut(x, y);
		} else {
			modify(x, b);
		}
	}

	return 0;
}
