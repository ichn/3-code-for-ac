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

const int maxn = 1000 + 10;

int n, m, q;

int a[maxn][maxn], l[maxn][maxn], r[maxn][maxn], u[maxn][maxn], d[maxn][maxn];

int calc1(int x, int y, int h[][maxn]) {
	int L=y, R=y, h0, s=0;
	while (h0 = max(h[x][L], h[x][R])) {
		while (h[x][L] >= h0) --L;
		while (h[x][R] >= h0) ++R;
		s = max(s, (R-L-1)*h0);
	}
	return s;
}
int calc2(int x, int y, int h[][maxn]) {
	int L=x, R=x, h0, s=0;
	while (h0 = max(h[L][y], h[R][y])) {
		while (h[L][y] >= h0) --L;
		while (h[R][y] >= h0) ++R;
		s = max(s, (R-L-1)*h0);
	}
	return s;
}

int main() {
#ifdef love_sbit
	file(434B);
#endif
	fr(n, m, q);
	rep(i, 1, n)
		rep(j, 1, m)
			fr(a[i][j]);
	rep(i, 1, n)
		rep(j, 1, m) {
			u[i][j] = (1+u[i-1][j])*a[i][j];
			l[i][j] = (1+l[i][j-1])*a[i][j];
		}
	red(i, n, 1)
		red(j, m, 1) {
			d[i][j] = (1+d[i+1][j])*a[i][j];
			r[i][j] = (1+r[i][j+1])*a[i][j];
		}
	int t, x, y;
	rep(i, 1, q) {
		fr(t, x, y);
		if (t==1) {
			a[x][y] ^= 1;
			rep(j, 1, n) u[j][y] = (1+u[j-1][y])*a[j][y];
			red(j, n, 1) d[j][y] = (1+d[j+1][y])*a[j][y];
			rep(j, 1, m) l[x][j] = (1+l[x][j-1])*a[x][j];
			red(j, m, 1) r[x][j] = (1+r[x][j+1])*a[x][j];
		} else {
			Wn(max(max(calc1(x, y, u), calc1(x, y, d)), max(calc2(x, y, l), calc2(x, y, r))));
		}
	}

	return 0;
}
