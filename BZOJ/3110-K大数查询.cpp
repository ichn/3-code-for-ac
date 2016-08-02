/*
 
   奇葩的写法
 
 */
#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define sqr(x) ((x) * (x))
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
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); } // warning!! slower than printf
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

const int maxn = 50000 + 100;
int ql, qr;

#define lc ch[0]
#define rc ch[1]
struct seg_node {
	int ch[2];
	int sum, lazy;
	seg_node() {
		lc = rc = 0;
		sum = lazy = 0;
	}
	inline void push_up();
	inline void push_down(int, int, int);
} T[maxn << 9];
int loc = 1;
inline void seg_node::push_up() {
	sum = T[lc].sum + T[rc].sum;
}
inline void seg_node::push_down(int l, int mid, int r) {
	if(lc == 0) lc = loc++;
	if(rc == 0) rc = loc++;
	if(lazy) {
		T[lc].sum += lazy * (mid-l+1);
		T[lc].lazy += lazy;
		T[rc].sum += lazy * (r-mid);
		T[rc].lazy += lazy;
		lazy = 0;
	}
}

struct seg_tree {

	int root;
	seg_tree () { root = 0; }
	inline int query(int l, int r, int rt) {
		if(rt == 0) return 0;
		if(ql <= l && r <= qr) {
			return T[rt].sum;
		}
		int mid = (l+r)>>1;
	//	T[rt].push_down(l, mid, r);
		int ret = 0;
		if(ql <= mid) ret += query(l, mid, T[rt].lc);
		if(mid < qr) ret += query(mid + 1, r, T[rt].rc);
		return ret + T[rt].lazy * (min(r, qr) - max(l, ql) + 1);
	}
	inline void insert(int l, int r, int &rt) {
		if(rt == 0) rt = loc++;
		if(ql <= l && r <= qr) {
			T[rt].sum += r - l + 1;
			++T[rt].lazy;
			return ;
		}
		int mid = (l+r)>>1;
	//	T[rt].push_down(l, mid, r);
		if(ql <= mid) insert(l, mid, T[rt].lc);
		if(mid < qr) insert(mid + 1, r, T[rt].rc);
		T[rt].sum = T[T[rt].lc].sum + T[T[rt].rc].sum + (r - l + 1) * T[rt].lazy;
	//	T[rt].push_up();
	}

} tree[maxn];

int n, m, upper;
inline int query(int p) {
	int sum = 0;
	for(; p; sum += tree[p].query(1, n, tree[p].root), p -= p&-p);
	return sum;
}
int main() {
#ifndef ONLINE_JUDGE
	file(3110);
#endif
	fr(n, m);
	rep(i, 1, m) {
		int t, c;
		fr(t, ql), fr(qr, c);
		if(t == 1) {
			c = n - c + 1;
			upper = max(upper, c);
			for(int p = c; p <= n; tree[p].insert(1, n, tree[p].root), p += p&-p);
		} else {
			int l = 1, r = upper, k = c;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(query(mid) < k)
					l = mid + 1;
				else r = mid;
			}
			printf("%d\n", n - l + 1);
		}
	}

	return 0;
}

