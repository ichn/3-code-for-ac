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

const int maxn = 300 + 10;

int n, m, q;
int g[maxn][maxn];
struct BIT_2D {
	int c[maxn][maxn];
	void modify2d(int x, int y, int d) {
		for(int i = x; i <= n; i += i&-i)
			for(int j = y; j <= m; j += j&-j)
				c[i][j] += d;
	}
	int get_sum2d(int x, int y) {
		int ret = 0;
		for(int i = x; i; i -= i&-i)
			for(int j = y; j; j -= j & -j)
				ret += c[i][j];
		return ret;
	}
} T[102];

int main() {
#ifdef love_sbit
	file(1452);
#endif
	fr(n, m);
	rep(i, 1, n)
		rep(j, 1, m)
			T[g[i][j] = fr()].modify2d(i, j, 1);
	fr(q);
	int t, x, y, x1, x2, y1, y2, c;
	while(q--) {
		fr(t);
		if(t == 1) {
			fr(x, y);
			T[g[x][y]].modify2d(x, y, -1);
			T[g[x][y] = fr()].modify2d(x, y, 1);
		} else {
			fr(x1, x2), fr(y1, y2), fr(c);
			--x1, --y1;
			Wn(T[c].get_sum2d(x2, y2) + T[c].get_sum2d(x1, y1) - T[c].get_sum2d(x1, y2) - T[c].get_sum2d(x2, y1));
		}
	}

	return 0;
}
