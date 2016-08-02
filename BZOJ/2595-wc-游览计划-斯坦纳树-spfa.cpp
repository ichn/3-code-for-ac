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

const int maxn = 10 + 1;
const int maxs = 1<<10;
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,-1,1};


int n, m, k;
int t, g[maxn][maxn];

void tobi(int i, bool pu=1) {
	if (i==0) return ;
	tobi(i>>1, 0);
	putchar('0'+(i&1));
	if (pu) puts("");
}

int f[maxn][maxn][maxs];
bool chs[maxn][maxn];

struct info {
	int x, y, s;
	info() {
		s = -1;
	}
	info(int x, int y, int s):x(x), y(y), s(s) {
	}
} pre[maxn][maxn][maxs];

void dfs(int i, int j, int s) {
	if (pre[i][j][s].s == -1)
		return ;
	info tmp = pre[i][j][s];
	chs[i][j] = true;
	dfs(tmp.x, tmp.y, tmp.s);
	if (tmp.x==i && tmp.y==j)
		dfs(tmp.x, tmp.y, s-tmp.s);
}

ipir que[maxs];
int vis[maxn][maxn];
int ft, bk;
void spfa(int s) {
	while (ft <= bk) {
		int u=que[ft].first, v=que[ft++].second;
		vis[u][v] = false;
		for (int i=0; i<4; ++i) {
			int tx=u+dx[i], ty=v+dy[i];
			if (tx <= 0 || ty <= 0 || n < tx || m < ty)
				continue;
			if (f[u][v][s]+g[tx][ty]<f[tx][ty][s]) {
				f[tx][ty][s] = f[u][v][s]+g[tx][ty];
				pre[tx][ty][s] = info(u, v, s);
				if (!vis[tx][ty]) {
					vis[tx][ty] = true;
					que[++bk] = mp(tx, ty);
				}
			}
		}
	}
	ft=0, bk=-1;
}

int main() {
#ifdef love_lhy
	file(2595);
#endif
	fr(n, m);
	memset(f, 0x0f, sizeof f);
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=m; ++j) {
			scanf("%d", &g[i][j]);
			if (g[i][j] == 0)
				f[i][j][1<<(t++)] = 0;
		}
	ft=0, bk=-1;
	for (int i=1, ms=1<<t; i<ms; ++i) {
		for (int x=1; x<=n; ++x)
			for (int y=1; y<=m; ++y) {
				for (int j=(i-1)&i; j; j=(j-1)&i) {
					if (f[x][y][j]+f[x][y][j^i]-g[x][y] < f[x][y][i]) {
						f[x][y][i] = f[x][y][j]+f[x][y][j^i]-g[x][y];
						pre[x][y][i] = info(x, y, j);
					}
				}
				if (f[x][y][i] != 0x0f0f0f0f) {
					que[++bk] = mp(x, y);
					vis[x][y] = 1;
				}
			}
		spfa(i);
	}
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=m; ++j)
			if (!g[i][j]) {
				printf("%d\n", f[i][j][(1<<t)-1]);
				dfs(i, j, (1<<t)-1);
				for (int x=1; x<=n; puts(""), ++x)
					for (int y=1; y<=m; ++y)
						if (!g[x][y]) {
							printf("%c", 'x');
						} else if (chs[x][y]) {
							printf("%c", 'o');
						} else printf("%c", '_');
				return 0;
			}
 
	return 0;
}
