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

const int maxn = 3000 + 100;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
struct Pair {
	int x, y;
	Pair() {}
	Pair(int x, int y):x(x), y(y) {}
};
struct Tuple {
	int x, y, z;
	Tuple() {}
	Tuple(int x, int y, int z):x(x), y(y), z(z) {}
};
char s[maxn][maxn];
int n, m, cnt, id, num[maxn][maxn], tr[maxn * maxn][4];
bool vis[maxn][maxn][4];
Pair st;
queue<Tuple> que;
vector<int> E[maxn], dir[maxn];
bool chk_in(int x, int y) {
	return 0 < x && 0 < y && x <= n && y <= m && s[x][y] != '#';
}

void dfs(int x, int y) {
	if (!chk_in(x, y) || num[x][y])
		return ;
	num[x][y] = ++cnt;
	for (int i = 0; i < 4; ++i)
		dfs(x + dx[i], y + dy[i]);
}

void add_status(Tuple x) {
	if (!vis[x.x][x.y][x.z]) {
		vis[x.x][x.y][x.z] = true;
		que.push(x);
	}
}

int size[maxn], dfs_clock, dfn[maxn], dfm[maxn], low[maxn], bl[maxn];
int fa[maxn];
int stk[maxn], top;

void tarjan(int u) {
	low[u] = dfn[u] = ++dfs_clock;
	stk[++top] = u;
	bl[u] = 1;
	size[u] = u > 1;
	for (int i = 0, sz = E[u].size(); i < sz; ++i) {
		int v = E[u][i];
		if (!dfn[v]) {
			fa[v] = u;
			tarjan(v);
			low[u] = min(low[u], low[v]);
			size[u] += size[v];
		} else if (bl[v])
			low[u] = min(low[u], dfn[v]);
	}
	dfm[u] = dfs_clock;
	if (low[u] == dfn[u]) {
		while (stk[top] != u)
			bl[stk[top--]] = 0;
		bl[stk[top--]] = 0;
	}
}
int get_child(int u, int v) {
	if (fa[u] == v)
		return v;
	for (int i = 0, sz = E[u].size(); i < sz; ++i) {
		if (fa[E[u][i]] == u && dfn[E[u][i]] <= dfn[v] && dfm[v] <= dfm[E[u][i]])
			return E[u][i];
	}
	return 0;
}
bool chk_link(int x, int y, int z) {
	if (x == y) return true;
	return low[x] < dfn[z] && low[y] < dfn[z];
}

int main() {
//#ifdef love_lhy
	file(box);
//#endif
	fr(n, m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (s[i][j] == 'X') {
				dfs(st.x = i, st.y = j);
				break;
			}
	for (int i = 0; i < 4; ++i) {
		if (chk_in(st.x + dx[i], st.y + dy[i]))
			add_status(Tuple(st.x, st.y, i));
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (num[i][j])
				for (int k = 0; k < 4; ++k) {
					int tx = i + dx[k], ty = j + dy[k];
					if (chk_in(tx, ty))
						E[num[i][j]].pb(num[tx][ty]);
				}
	++id;
	fa[1] = -1;
	tarjan(1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (num[i][j])
				for (int k = 0; k < 4; ++k) {
					int tx = i + dx[k], ty = j + dy[k];
					if (chk_in(tx, ty))
						tr[num[i][j]][k] = get_child(num[i][j], num[tx][ty]);
				}
	while (!que.empty()) {
		Tuple u = que.front();
		que.pop();
		u.x += dx[u.z], u.y += dy[u.z];
		int tx = u.x + dx[u.z], ty = u.y + dy[u.z];
		if (chk_in(tx, ty))	{
			int p = num[tx][ty];
			int q = num[u.x][u.y];
			if (q > 1)
				dir[q].pb(p);
			for (int i = 0; i < 4; ++i) {
				if (chk_in(u.x + dx[i], u.y + dy[i]) && chk_link(tr[q][u.z], tr[q][i], q))
					add_status(Tuple(u.x, u.y, i));
			}
		}
	}
	LL ans = 0;
	for (int i = 1; i <= cnt; ++i) {
		bool flg = 0;
		++id;
		for (int j = 0, sz = dir[i].size(); j < sz; ++j) {
			int t = dir[i][j];
			if (fa[i] == t) {
				flg = 1;
				continue;
			}
			int son = 0;
			for (int k = 0; k < E[i].size(); ++k) {
				if (fa[E[i][k]] == i && dfn[E[i][k]] <= dfn[t] && dfm[E[i][k]] >= dfm[t])
					son = E[i][k];
			}
			if (!son) {
				flg = 1;
				continue;
			}
			if (bl[son] != id) {
				bl[son] = id;
				ans += size[son];
			}
			if (low[son] < dfn[i])
				flg = 1;
		}
		if (flg) {
			ans += cnt - 1 - size[i];
			for (int k = 0; k < E[i].size(); ++k) {
				if (fa[E[i][k]] == i && bl[E[i][k]] != id && low[E[i][k]] < dfn[i])
					ans += size[E[i][k]];
			}
		}
	}
	printf("%lld\n", ans);

	return 0;
}

