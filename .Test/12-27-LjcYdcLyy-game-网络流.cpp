#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
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
};
using namespace my_useful_tools;

#define valid "valid"
#define invalid "invalid"
 
const int maxSize = 30 + 2;
const int maxNode = 1000 + 10;
const int maxEdge = 8 * maxNode + 100;


class MaxFlow {
	public:
	int head[maxNode], edge, to[maxEdge], next[maxEdge], cap[maxEdge];
	int cur[maxNode], dis[maxNode], que[maxNode], f, b;
	bool vis[maxNode];

	bool bfs() {
		memset(vis, false, sizeof vis);
		que[f = b = 0] = s, dis[s] = 0, vis[s] = true;
		while(f <= b) {
			int u = que[f++];
			for(int i = head[u]; i != -1; i = next[i]) {
				int v = to[i];
				if(!vis[v] && cap[i] > 0)
					que[++b] = v, vis[v] = true, dis[v] = dis[u] + 1;
			}
		}
		return vis[t];
	}
	int dfs(int u, int a) {
		if(u == t || a == 0)
			return a;
		int flow = 0, f;
		for(int &i = cur[u]; i != -1; i = next[i]) {
			int v = to[i], &c = cap[i];
			if(c > 0 && dis[v] == dis[u] + 1 && (f = dfs(v, min(c, a))) > 0) {
				c -= f, a -= f, cap[i ^ 1] += f, flow += f;
				if(a == 0) break;
			}
		}
		return flow;
	}


	public:
	static const int Max = 0x3f3f3f3f;
	int s, t;

	MaxFlow() { 
		edge = 0; memset(head, -1, sizeof head);
	}

	void addEdge(int u, int v, int c) {
		to[edge] = v, cap[edge] = c, next[edge] = head[u], head[u] = edge++;
		to[edge] = u, cap[edge] = 0, next[edge] = head[v], head[v] = edge++;
	}

	int get_flow() {
		int flow = 0;
		while(bfs()) {
			memcpy(cur, head, sizeof cur);
			flow += dfs(s, Max);
		}
		return flow;
	}
};

class ConnectingGame {
	int n, m, cnt;
	public:
	string isValid(vector <string> board) {
		cnt = 0, n = board.size(); m = board[0].size();
		static map<char, int> id;
		bool adj[maxNode][maxNode];
		int region[maxSize][maxSize];

		id.clear();
		memset(adj, false, sizeof adj);
		
		reu(i, 0, n)
			reu(j, 0, m) {
				char ch = board[i][j];
				if(id.count(ch) == 0)
					id[ch] = cnt++;
				region[i][j] = id[ch];
			}

		reu(i, 0, n)
			reu(j, 0, m)
				rep(x, max(0, i-1), min(n-1, i+1))
					rep(y, max(0, j-1), min(m-1, j+1))
						if(region[i][j] != region[x][y])
							adj[region[i][j]][region[x][y]] = true;
		reu(i, 0, n) {
			adj[region[i][0]][cnt] = true;
			adj[region[i][m-1]][cnt+1] = true;
		}
		reu(i, 0, m) {
			adj[region[0][i]][cnt+2] = true;
			adj[region[n-1][i]][cnt+3] = true;
		}


		reu(i, 0, n-1)
			reu(j, 0, m-1) {
				int a = region[i][j], b = region[i][j+1],
					c = region[i+1][j], d = region[i+1][j+1];
				if(a == b || a == c || a == d || b == c || b == d || c == d)
					continue;

				MaxFlow *g = new MaxFlow();

				reu(k, 0, cnt + 4)
					g->addEdge(k<<1, k<<1|1, 1);

				g->s = (cnt+4)<<1, g->t = (cnt+4)<<1|1;
				g->addEdge(g->s, a<<1, 1);
				g->addEdge(g->s, b<<1, 1);
				g->addEdge(g->s, c<<1, 1);
				g->addEdge(g->s, d<<1, 1);

				reu(p, 0, cnt+4)
					reu(q, 0, cnt+4)
						if(adj[p][q])
							g->addEdge(p<<1|1, q<<1, MaxFlow::Max);

				g->addEdge((cnt)  <<1|1, g->t, 1);
				g->addEdge((cnt+1)<<1|1, g->t, 1);
				g->addEdge((cnt+2)<<1|1, g->t, 1);
				g->addEdge((cnt+3)<<1|1, g->t, 1);

				
				if(g->get_flow() == 4)
					return invalid;
			}
		return valid;
	}
} solver;

int main() {
	file(game);
	for(int test = fr(); test--; ) {
		int n = fr();
		vector<string> str;
		string tmp;
		while(n--)
			cin >> tmp, str.pb(tmp);
		cout << solver.isValid(str) << endl;
	}
	return 0;
}
 


