#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define _pir pair<int, int>
#define _vec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define cpy(t, g) memcpy(t, g, sizeof g)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define pfile(x) freopen(#x".in", "r", stdin), freopen("_"#x".out", "w", stdout)
#define hfile freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define gfile(x) freopen(#x".in", "w", stdout);
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
};
using namespace my_useful_tools;

const int maxn = 101;

int f[maxn][maxn];

int n, m;

_pir que[maxn*maxn*maxn];
int qh, qt;

int go[maxn][maxn], d[maxn][maxn], ans[maxn][maxn];

#define x first
#define y second

bool inq[maxn][maxn];

int main() {
	file(graph);

	int cnt = 0;
	while (scanf("%d %d", &n, &m) != EOF) {
		if (n == 0 && m == 0) break;
		pse(go, 0);
		pse(ans, INF);
		pse(d, INF);
		for (int i = 1; i <= m; ++i) {
			int u, v;
			fr(u, v);
			go[u][v] = 1;
			d[u][v] = 1;
		}
		rep(k, 1, n)
			rep(i, 1, n)
				rep(j, 1, n)
					if (d[i][k] + d[k][j] < d[i][j])
						d[i][j] = d[i][k] + d[k][j];
		pse(inq, 0);
		que[qh = qt = 1] = mp(1, 1);
		inq[1][1] = 1;
		ans[1][1] = 1;
		for (int i = 1; i <= n; ++i)
			go[i][i] = 1;
		while (qh <= qt) {
			_pir u = que[qh++];
			inq[u.x][u.y] = 0;
			for (int i = 1; i <= n; ++i) {
				if (go[u.x][i] && go[i][u.y] && ans[u.x][u.y] + 1 < ans[i][i]) {
					ans[i][i] = ans[u.x][u.y] + 1;
					if (!inq[i][i]) {
						que[++qt] = mp(i, i);
						inq[i][i] = 1;
					}
				}
			}
			for (int i = 1; i <= n; ++i) {
				if (go[u.x][i] && ans[u.x][u.y] + 1 < ans[i][u.y]) {
					ans[i][u.y] = ans[u.x][u.y]+1;
					if (!inq[i][u.y]) {
						que[++qt] = mp(i, u.y);
						inq[i][u.y] = 1;
					}
				}
			}
			for (int i = 1; i <= n; ++i) {
				if (go[i][u.y] && ans[u.x][u.y] + 1 < ans[u.x][i]) {
					ans[u.x][i] = ans[u.x][u.y]+1;
					if (!inq[u.x][i]) {
						que[++qt] = mp(u.x, i);
						inq[u.x][i] = 1;
					}
				}
			}
			if (u.x != u.y && ans[u.x][u.y] + d[u.x][u.y] - 1 < ans[u.y][u.x]) {
				ans[u.y][u.x] = ans[u.x][u.y] + d[u.x][u.y] - 1;
				if (!inq[u.y][u.x]) {
					que[++qt] = mp(u.y, u.x);
					inq[u.y][u.x] = 1;
				}
			}
		}
		printf("Network %d\n", ++cnt);
		if (ans[2][2] == INF) {
			puts("Impossible");
		} else {
			printf("Minimum number of nodes = %d\n", ans[2][2]);
		}
		puts("");
	}
 
	return 0;
}


