#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define Edges(_i, _u, _e) for(int _i = _e.head[_u]; _i != -1; _i = _e.next[_i])
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

const int maxn = 200000 + 100;

int a[maxn], b[maxn];
int n;

struct BIT {
	int a[maxn], c[maxn];
	BIT() {
		memset(a, 0, sizeof a);
	}
	int get_sum(int p) {
		++p;
		int ret = 0;
		for (; p; ret += c[p], p -= p&-p);
		return ret;
	}
	void rev(int p) {
		++p;
		int add = 0;
		if (a[p] == 0) {
			add = 1;
		} else add = -1;
		a[p] ^= 1;
		for (; p <= n; c[p] += add, p += p&-p);
	}
} c, d, e;

int r[maxn];

int get(int p) {
	++p;
	int l = 0, r = n-1;
	while (l<r) {
		int mid = (l+r)>>1;
		if (e.get_sum(mid) < p)
			l = mid+1;
		else r = mid;
	}
	return l;
}

int main() {
#ifdef love_sbit
	file(504B);
#endif
	fr(n);
	reu(i, 0, n)
		fr(a[i]);
	reu(i, 0, n)
		fr(b[i]);
	reu(i, 0, n) {
		c.rev(i);
		d.rev(i);
	}
	reu(i, 0, n) {
		int x = c.get_sum(a[i]), y = d.get_sum(b[i]);
		r[i] = x+y-2;
		c.rev(a[i]), d.rev(b[i]);
	}
	red(i, n-1, 0) {
		int f = n-i;
		r[i-1] += r[i] / f;
		r[i] %= f;
	}
	reu(i, 0, n) {
		e.rev(i);
	}
	static int out[maxn];

	reu(i, 0, n) {
		out[i] = get(r[i]);
		e.rev(out[i]);
	}

	for(int i = 0; i < n; ++i) {
		printf("%d ", out[i]);
	}
	puts("");

	return 0;
}
