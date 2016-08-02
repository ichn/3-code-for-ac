#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
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
};
using namespace my_useful_tools;
//#define generator_sbit

// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你所深爱着的
// 永远不要相信自己的意志力

const int maxv = (1000 + 10)*(1000 + 10);
const int maxe = maxv * 4 + 100;

struct MaxFlow {
	int edge, head[maxv], to[maxe], next[maxe];
	int cap[maxe];
	void init() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v, int c) {
		to[edge] = v, next[edge] = head[u];
		cap[edge] = c;
		head[u] = edge++;
	}
	void addEdge(int u, int v, int c) {
	//	printf("%d %d %d\n", u, v, c);
		addedge(u, v, c);
		addedge(v, u, 0);
	}

	int s, t;
	int cur[maxv], dis[maxv], que[maxe], front, back;

	bool bfs() {
		que[front=back=0] = s;
		memset(dis, INF, sizeof dis);
		dis[s] = 0;
		while (front <= back) {
			int u = que[front++];
			for (int i=head[u]; i!=-1; i=next[i]) {
				if (cap[i]>0 && dis[to[i]]>dis[u]+1) {
					dis[to[i]] = dis[u]+1;
					que[++back] = to[i];
				}
			}
		}
		return dis[t] < INF;
	}

	int dfs(int u, int a) {
		if (u==t || a==0)
			return a;
		int flow=0, f;
		for (int &i=cur[u], v; i!=-1; i=next[i])
			if (cap[i]>0 && dis[v=to[i]]==dis[u]+1 && (f=dfs(v, min(a, cap[i])))>0) {
				cap[i]-=f, cap[i^1]+=f;
				flow+=f, a-=f;
				if (a==0) break;
			}
		return flow;
	}

	int max_flow() {
		int ret = 0;
		while (bfs()) {
			memcpy(cur, head, sizeof head);
			ret += dfs(s, INF);
		}
		return ret;
	}
};

int n, m;

class ViaFlow {
	MaxFlow mf;

	public:
	void solve() {
		int c;
		mf.init();
		reu(i, 0, n)
			reu(j, 0, m-1) {
				fr(c);
				mf.addEdge(i*m+j, i*m+j+1, c);
				mf.addEdge(i*m+j+1, i*m+j, c);
			}
		reu(i, 0, n-1)
			reu(j, 0, m) {
				fr(c);
				mf.addEdge(i*m+j, (i+1)*m+j, c);
				mf.addEdge((i+1)*m+j, i*m+j, c);
			}
		mf.s = 0, mf.t = n*m-1;
		printf("%d\n", mf.max_flow());
	}
};

struct DijNode {
	int u, d;
	DijNode() {}
	DijNode(int u, int d):u(u), d(d) {}
	bool operator < (const DijNode&rhs) const {
		return d > rhs.d;
	}
};
class ShortestPath {
	public:
	int edge, head[maxv], to[maxe], next[maxe];
	int wei[maxe];
	int s, t;
	int dis[maxv];
	priority_queue<DijNode> q;

	void init() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v, int c) {
		to[edge] = v, next[edge] = head[u];
		wei[edge] = c;
		head[u] = edge++;
	}
	void addEdge(int u, int v, int c) {
	//	printf("%d %d %d\n", u, v, c);
		addedge(u, v, c);
		addedge(v, u, c);
	}

	int shortest_path() {
		memset(dis, INF, sizeof dis);
		dis[s] = 0;
		q.push(DijNode(s, 0));
		while (!q.empty()) {
			int u = q.top().u;
			if (u == t) break;
			q.pop();
			for (int i = head[u]; i != -1; i = next[i]) {
				int v = to[i], w = wei[i];
				if (dis[u] + w < dis[v]) {
					dis[v] = dis[u] + w;
					q.push(DijNode(v, dis[v]));
				}
			}
		}
	//	for (int i = 0; i <= t; ++i) {
	//		printf("%d ", dis[i]);
	//	} puts("");
		return dis[t];
	}
};

class ViaShortestPaths {
	ShortestPath sp;

	public:
	void solve() {
		int c;
		sp.init();
		sp.s = (n-1)*(m-1), sp.t = sp.s+1;
		reu(i, 0, n)
			reu(j, 0, m-1) {
				fr(c);
				if (i == 0) {
					sp.addEdge(sp.s, i*(m-1)+j, c);
				} else if (i == n-1) {
					sp.addEdge((i-1)*(m-1)+j, sp.t, c);
				} else {
					sp.addEdge((i-1)*(m-1)+j, i*(m-1)+j, c);
				}
			}
		reu(i, 0, n-1)
			reu(j, 0, m) {
				fr(c);
				if (j == 0) {
					sp.addEdge(i*(m-1)+j, sp.t, c);
				} else if (j == m-1) {
					sp.addEdge(sp.s, i*(m-1)+j-1, c);
				} else {
					sp.addEdge(i*(m-1)+j-1, i*(m-1)+j, c);
				}
			}
		printf("%d\n", sp.shortest_path());
	}
};

int main() {
	freopen("cguo.in", "r", stdin);
	freopen("cguo.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif
	fr(n, m);
	(new ViaShortestPaths)->solve();
 
	return 0;
}
