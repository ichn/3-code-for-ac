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
};
using namespace my_useful_tools;

const int maxn = 100 + 10;

int n, m;
int a[maxn];
vector<pair<int, int> > fac[maxn];
vector<pair<ipir, int> > tmp;

void div(int v, vector<ipir>&ret) {
	int up=(int)sqrt((DB)v+.5);
	for (int i=2; i<=v && i<=up; ++i) {
		if (v%i != 0)
			continue;
		int cnt=0;
		while (v%i == 0) {
			v/=i, ++cnt;
		}
		ret.pb(mp(i, cnt));
	}
	if (v != 1) {
		ret.pb(mp(v, 1));
	}
}

void common(vector<pair<int, int> >&u, vector<pair<int, int> >&v, vector<pair<ipir, int> >&ret) {
	ret.clear();
	for (int i=0, j=0, sz1=u.size(), sz2=v.size(); i<sz1 && j<sz2;) {
		if (u[i].first==v[j].first) {
			ret.pb(mp(mp(i+1, j+1), min(u[i].second, v[j].second)));
			++i, ++j;
		} else {
			if (u[i].first < v[j].first)
				++i;
			else ++j;
		}
	}
}

const int maxv = 1000, maxe = maxv * 2;
struct MaxFlow {
	int edge, head[maxv], to[maxe], next[maxe];
	int cap[maxe];
	MaxFlow() { edge = 0; memset(head, -1, sizeof head); }
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
	int cur[maxv], dis[maxv], que[maxv], front, back;

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

	int MF() {
		int ret = 0;
		while (bfs()) {
			memcpy(cur, head, sizeof head);
			ret += dfs(s, INF);
		}
		return ret;
	}
} sol;
	
int base[maxn];

int main() {
#ifdef love_sbit
	file(498C);
#endif
	fr(n, m);
	sol.s=0, sol.t=990;
	rep(i, 1, n) {
		fr(a[i]);
		div(a[i], fac[i]);
		int sz=fac[i].size();
		base[i] = base[i-1]+sz;
		if (i&1) {
			for (int j=0; j<sz; ++j)
				sol.addEdge(sol.s, base[i-1]+j+1, fac[i][j].second);
		}
		else {
			for (int j=0; j<sz; ++j)
				sol.addEdge(base[i-1]+j+1, sol.t, fac[i][j].second);
		}
	}
	rep(i, 1, m) {
		int u, v;
		fr(u, v);
		if (v&1)
			swap(u, v);
		common(fac[u], fac[v], tmp);
		for (int j=0, sz=tmp.size(); j<sz; ++j) {
			sol.addEdge(base[u-1]+tmp[j].first.first, base[v-1]+tmp[j].first.second, tmp[j].second);
		}
	}


	printf("%d\n", sol.MF());

	return 0;
}

