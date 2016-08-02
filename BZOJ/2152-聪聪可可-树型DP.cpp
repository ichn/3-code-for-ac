#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define upu(_a, _b) if(_a < _b) { _a = _b; }
#define upd(_a, _b) if(_b < _a) { _a = _b; }
#define pb push_back
#define mp make_pair
#define i_pair pair<int, int>
#define i_vec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	inline void R(int &t) { scanf("%d", &t); }
	inline void R(LL &t) { scanf("%lld", &t); }
	inline void W(int t) { printf("%d\n", t); }
	inline void W(LL t) { printf("%lld\n", t); }
	template<class T> inline void FR(T &ret, char c = ' ') {
		for(c = getchar(); c < '0' || '9' < c; c = getchar());
		for(ret = 0; '0' <= c && c <= '9'; c = getchar()) {
		 ret = ret * 10 + c - '0';
		}
	}
	inline char gchar() {
		char ret = getchar();
		for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar());
		return ret;
	}
	template<class T> inline T gcd(T a, T b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) {
			if(index & 1) ret = ret * base % mod;
		}
		return ret;
	}
	const int maxv = 20000 + 100;
	const int maxe = 40000 + 200;
	struct Edge {
		int edge;
		int head[maxv], to[maxe], next[maxe], weight[maxe];
		Edge() {
			edge = 0;
			memset(head, -1, sizeof head);
		}
		void addedge(int u, int v, int w) {
			to[edge] = v;
			weight[edge] = w;
			next[edge] = head[u];
			head[u] = edge++;
		}
	};
};
using namespace my_useful_tools;
const int maxn = maxv;
Edge e;
int n, f[maxn][3], ans;
bool vis[maxn];
 
void dfs(int u) {
	vis[u] = 1, f[u][0] = 1;
	++ans;
	// 一个点也要算答案~
	for(int i = e.head[u]; i != -1; i = e.next[i]) {
		int v = e.to[i], w = e.weight[i];
		if(!vis[v]) {
			dfs(v);
			for(int j = 0; j < 3; ++j) {
				ans += f[u][j] * f[v][(6 - w - j) % 3] * 2;
			}
			for(int j = 0; j < 3; ++j) {
				f[u][j] += f[v][(3 - w + j) % 3];
			}
		}
	}
}
 
int main() {
	R(n);
	rep(i, 2, n) {
		int u, v, w;
		R(u), R(v), R(w);
		e.addedge(u, v, w % 3);
		e.addedge(v, u, w % 3);
	}
	dfs(1);
	printf("%d/%d\n", ans / gcd(ans, n * n), n * n / gcd(ans, n * n));
 
	return 0;
}
