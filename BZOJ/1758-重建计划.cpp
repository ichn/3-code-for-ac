#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
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
};
using namespace my_useful_tools;
const int maxv = 1e5 + 100, maxe = maxv << 1;
struct Edge {
	int edge, head[maxv], to[maxe], next[maxe];
	int w[maxe];
	bool exist[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v, int wei) {
		to[edge] = v, next[edge] = head[u];
		w[edge] = wei;
		exist[edge] = true;
		head[u] = edge++;
	}
}e;


int L, U, lim, n;
DB ans;

int d, Md, size[maxv];
void getD(int u, int f, int s) {
	size[u] = 1;
	int r = 0;
	Edges(i, u, e)
		if(e.exist[i] && e.to[i] != f) {
			getD(e.to[i], u, s);
			size[u] += size[e.to[i]];
			r = max(r, size[e.to[i]]);
		}
	r = max(r, s - size[u]);
	if(r < Md)
		Md = r, d = u;
}

DB dis[maxv], level[maxv], rec[maxv];
int que[maxv], h, t, stk[maxv], f, b;
int dep[maxv];
bool vis[maxv];
// h:head, t:tail, f:front, b:back
// que,bfs队列


bool jud(int u, DB w) {
	int recDep = 0, mxDep, v;
	rec[0] = 0.0;
	bool ret = false;
	vis[u] = true, dep[u] = 0;
	Edges(i, u, e)
		if(e.exist[i]) {
			v = que[h = t = 0] = e.to[i];
			dis[v] = e.w[i] - w;
			dep[v] = 1;
			vis[v] = true;
			level[0] = 0.0, level[1] = dis[v];
			mxDep = 1;
			while(h <= t) {
				int x = que[h++];
				Edges(j, x, e)
					if(e.exist[j] && !vis[v = e.to[j]]) {
						mxDep = max(mxDep, dep[v] = dep[x] + 1);
						dis[v] = dis[x] + e.w[j] - w;
						level[dep[v]] = max(level[dep[v]], dis[v]);
						que[++t] = v;
						vis[v] = true;
					}
			}
			rep(j, 0, t)
				vis[que[j]] = false;
			f = b = 0, v = recDep;
			rep(j, 0, mxDep) {
				while(v + j >= L) {
					while(f < b && rec[stk[b]] < rec[v])
						--b;
					stk[++b] = v;
					--v;
				}
				while(f < b && j + stk[f + 1] > U)
					++f;
				int g = stk[f + 1];
				if(f < b && rec[g] + level[j] > 0.0) {
					recDep = max(recDep, mxDep);
					ret = true;
					goto end;
				}
			}
			rep(j, 0, mxDep)
				rec[j] = max(rec[j], level[j]), level[j] = -INF;
			recDep = max(recDep, mxDep);
		}
end:
	rep(i, 0, recDep)
		rec[i] = level[i] = -INF;
	vis[u] = false;
	return ret;
}


void calc(int u) {
	DB l = ans, r = lim;
	while(r - l > 1e-5) {
		DB mid = (r + l) / 2;
		if(jud(u, mid))
			l = mid;
		else r = mid;
	}
	ans = l;
}

void dfs(int u, int f) {
	size[u] = 1;
	for(int i = e.head[u]; i != -1; i = e.next[i])
		if(e.exist[i] && e.to[i] != f)
			dfs(e.to[i], u), size[u] += size[e.to[i]];
}

void solve(int u, int s) {
	if(s < L) return ;
	Md = INF, d = u;
	getD(u, -1, s);
	calc(d);
	//dfs(d, -1);
	Edges(i, d, e)
		if(e.exist[i]) {
			e.exist[i] = e.exist[i ^ 1] = 0;
			solve(e.to[i], size[e.to[i]]);
		}
}

int main() {
	fr(n, L, U);
	rep(i, 2, n) {
		int u, v, w; fr(u, v, w);
		e.addedge(u, v, w), e.addedge(v, u, w);
		lim = max(lim, w);
	}
	ans = -INF;
	for(int i = 0; i <= n; ++i)
		level[i] = rec[i] = -INF;
	solve(1, n);
	printf("%.3lf\n", ans);

	return 0;
}
