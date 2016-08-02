#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
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
 
class DistinctPaths {
	static const int mod = 1e9 + 7;
	static const int maxn = 10 + 1;
	static const int maxs = 1 << 15;
	int n, m, k;
	int a[maxn][maxn], ans, log2[maxs], f[maxn][maxn];
	int cnt[maxn];
	int dfs(int x, int y) {
		if(y == m + 1) {
			y = 1;
			++x;
		}
		if(x == n + 1) {
			return 1;
		}
		int s = f[x - 1][y] | f[x][y - 1];
		int ret = 0;
		int calced = -1;
		for(int t = (~s) & ((1 << k) - 1); t; t -= t & (-t)) {
			int p = log2[t & -t] + 1;
			if(a[x][y] == 0 || a[x][y] == p) {
				++cnt[p];
				f[x][y] = s | (t & -t);
				if(cnt[p] == 1) {
					if(calced == -1) calced = dfs(x, y + 1);
					ret += calced;
				} else if(cnt[p]) {
					ret += dfs(x, y + 1);
				}
				--cnt[p];
				if(ret >= mod) ret -= mod;
			}
		}
		return ret;
	}
	int solve() {
		fr(n, m, k);
		if(k < n + m - 1)
			return 0;
		rep(i, 1, n) rep(j, 1, m)
			fr(a[i][j]), ++cnt[a[i][j]];
		rep(i, 1, k) log2[1 << i] = i;
		return dfs(1, 1);
	}

public:
	void run() {
		Wn(solve());
	}
} solver;


int main() {
	solver.run();
 
	return 0;
}
