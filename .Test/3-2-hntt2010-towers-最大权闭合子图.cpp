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
};
using namespace my_useful_tools;

// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你所深爱着的
//
// 永远不要相信自己的意志力

const int maxv = 500 + 10;
const int maxe = maxv * maxv * 2;
struct Point {
	int x, y, r, w;
} p[maxv];
int n;

//class MaxFlow {
//	public:
//
//	int head[maxv], to[maxe], next[maxe], cap[maxe], edge;
//	int s, t, cur[maxv];
//
//	void init() {
//		memset(head, -1, sizeof head);
//		edge = 0;
//	}
//	void addEdge(int u, int v, int c) {
//		next[edge] = head[u], to[edge] = v, cap[edge] = c, head[u] = edge++;
//		next[edge] = head[v], to[edge] = u, cap[edge] = 0, head[v] = edge++;
//	}
//
//	int que[maxe], f, b, dis[maxv];
//	bool bfs() {
//		que[f = b = 0] = s;
//	//	for (register int i = 0; i <= t; ++i) dis[i] = INF;
//		memset(dis, INF, sizeof dis);
//		dis[s] = 0;
//		while (f <= b) {
//			int u = que[f++];
//			for (register int i = head[u]; i != -1; i = next[i]) {
//				int v = to[i];
//				if (cap[i] > 0 && dis[u]+1 < dis[v])
//					dis[v] = dis[u]+1, que[++b] = v;
//			}
//		}
//		return dis[t] != INF;
//	}
//
//	int dfs(int u, int a) {
//		if (u == t || a == 0)
//			return a;
//		int f, flow = 0;
//		for (register int&i = cur[u]; i != -1; i = next[i]) {
//			int v = to[i];
//			if (dis[v] == dis[u] + 1 && cap[i] > 0) {
//				f = dfs(v, min(a, cap[i]));
//				flow += f, cap[i] -= f, cap[i^1] += f, a -= f;
//				if (a == 0 || f == 0) break;
//			}
//		}
//		return flow;
//	}
//
//	int max_flow() {
//		int flow = 0;
//		while (bfs()) {
//			for (register int i = 0; i <= t; ++i)
//				cur[i] = head[i];
//			flow += dfs(s, INF);
//		}
//		return flow;
//	}
//} mf;


//const int maxv = 1000, maxe = maxv * 2;
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
	int cur[maxv], dis[maxv], que[maxv*maxv], front, back;

	bool bfs() {
		que[front=back=0] = s;
		memset(dis, INF, sizeof dis);
	//	for (register int i = 0; i <= t; ++i) dis[i] = INF;
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
		return dis[t]!=INF;
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
	//		for (register int i = 0; i <= t; ++i) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
} mf;


#define sqr(x) (1LL*(x)*(x))
long long dis2(Point a, Point b) {
	return sqr(a.x-b.x)+sqr(a.y-b.y);
}
 
int main() {
	file(towers);
	int T;
	fr(T);
	rep(TC, 1, T) {
		printf("Case #%d:", TC);
		fr(n);
		int sum = 0;
		mf.init();
		mf.s = 0, mf.t = n+1;
		rep(i, 1, n) {
			fr(p[i].x, p[i].y);
			fr(p[i].r, p[i].w);
			if (p[i].w > 0) {
				sum += p[i].w;
				mf.addEdge(mf.s, i, p[i].w);
			}
			if (p[i].w <= 0) {
				mf.addEdge(i, mf.t, -p[i].w);
			}
		}
		rep(i, 1, n) {
			rep(j, 1, n)
				if (i != j) {
					if (dis2(p[i], p[j]) <= sqr(p[i].r)) {
		//				printf("%d %d\n", i, j);
						mf.addEdge(i, j, INF);
					}
				}
		}
		printf("%d\n", sum - mf.max_flow());
	}
 
	return 0;
}

