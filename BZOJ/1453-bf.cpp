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
 
const int maxn = 200 + 10;

int g[maxn][maxn];
int n, m;

int cnt[2];
int vis[maxn][maxn];

ipir que[maxn*maxn];
int h, t;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

void mark(int x, int y) {
	h = 1, t = 0;
	que[++t] = mp(x, y);
	while(h <= t) {
		int ux = que[h].first, uy = que[h++].second;
		for(int i = 0; i < 4; ++i) {
			int vx = ux + dx[i],
				vy = uy + dy[i];
			if(0 < vx && vx <= n && 0 < vy && vy <= n && !vis[vx][vy] && g[vx][vy] == g[ux][uy]) {
				vis[vx][vy] = 1;
				que[++t] = mp(vx, vy);
			}
		}
	}
}

void calc() {
	memset(vis, false, sizeof vis);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(!vis[i][j]) {
				vis[i][j] = 1;
				++cnt[g[i][j]];
				mark(i, j);
			}
		}
	}
}

int main() {
#ifdef love_sbit
	freopen("1453.in", "r", stdin), freopen("1453-bf.out", "w", stdout);
#endif

	fr(n);
	rep(i, 1, n)
		rep(j, 1, n)
			g[i][j] = fr();
	fr(m);
	while(m--) {
		g[fr()][fr()] ^= 1;
		cnt[0] = cnt[1] = 0;
		calc();
		printf("%d %d\n", cnt[1], cnt[0]);
	}

	return 0;
}
