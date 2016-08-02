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
	template<class T> inline void fr(T&ret) { char c; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
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

const int maxn = 51 + 3;
const int maxm = 2000 + 10;

int n, m;

int lim[maxn], cost[maxn], fa[maxn], w[maxn], need[maxn];
const int maxv = maxn, maxe = maxv * 2;
struct Edge {
	int edge, head[maxv], to[maxe], next[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v) {
		to[edge] = v, next[edge] = head[u];
		head[u] = edge++;
	}
} e;

int f[maxn][maxn * 2][maxm], mxp[maxn], tmp[maxm];
int ans;

inline void up(int &x, int y) { if(y > x) x = y; }
inline void down(int &x, int y) { if(y < x) x = y; }

void dp(int x) {
	int (*now)[maxm] = f[x], v;
	if(e.head[x] == -1) {
		mxp[x] = min(lim[x], m / cost[x]);
		rep(i, 0, mxp[x])
			rep(j, i, mxp[x])
				up(now[i][j * cost[x]], (j - i) * w[x]);
		return ;
	}
	mxp[x] = maxm;
	Edges(i, x, e) {
		dp(v = e.to[i]);
		down(mxp[x], mxp[v] / need[v]);
	}
	rep(i, 0, mxp[x]) now[i][0] = 0;
	Edges(z, x, e)
		rep(i, 0, mxp[x]) {
			int (*sub)[maxm] = f[v = e.to[z]];
			int c = i * need[v];
			memcpy(tmp, now[i], sizeof tmp);
			memset(now[i], -INF, sizeof now[i]);
			red(j, m, 0)
				red(k, j, 0)
					if(tmp[j - k] != -INF && sub[c][k] != -INF) {
						up(now[i][j], tmp[j - k] + sub[c][k]);
						up(ans, now[i][j]);
					}
		}
	reu(i, 0, mxp[x])
		red(j, mxp[x], i + 1)
			red(k, m, 0)
				if(now[j][k] != -INF) {
					up(now[i][k], now[j][k] + (j - i) * w[x]);
					up(ans, now[i][k]);
				}
}



int main() {
#ifdef love_sbit
	file(1017);
#endif
	
	fr(n, m);
	memset(f, -INF, sizeof f);
	rep(i, 1, n) {
		fr(w[i]);
		if(gchar() == 'B') fr(cost[i], lim[i]);
		else for(int j = fr(), l; j--; ) {
			e.addedge(i, l = fr());
			fa[l] = i;
			fr(need[l]);
		}
	}
	rep(i, 1, n) if(!fa[i])
		dp(i);
	Wn(ans);

	return 0;
}
