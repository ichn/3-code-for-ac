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
 
const int maxn = 1e5 + 100;
const int maxv = maxn, maxe = maxn<<1;
struct Edge {
	int edge, head[maxv], to[maxe], next[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addEdge(int u, int v) {
		to[edge] = v, next[edge] = head[u];
		head[u] = edge++;
		to[edge] = u, next[edge] = head[v];
		head[v] = edge++;
	}
} e;

int Size, n, m, cntTask, cntChg, chg_pos[maxn], chg_to[maxn], q, cnt[maxn], col[maxn], val[maxn], wei[maxn];
bool vis[maxn];
int h, t, que[maxn];

int fa[maxn], dep[maxn], size[maxn], top[maxn];
const int maxt = maxn<<1;
int next[maxt], in[maxt], out[maxt], pid[maxt];
void bfs() {
	que[h = t = 0] = 1;
	while (h <= t) {
		int u = que[h++];
		next[u<<1] = u<<1|1;
		for (int i=e.head[u], v; i != -1; i=e.next[i])
			if ((v=e.to[i]) != fa[u]) {
				fa[v] = u;
				que[++t] = v;
				dep[v] = dep[u] + 1;
				next[v<<1|1] = next[u<<1];
				next[u<<1] = v<<1;
			}
	}
	for (int i=t, u=que[t]; 0 <= i; u=que[--i])
		size[fa[u]] += ++size[u];
	size[0] = 0;
	for (int i=0, u=que[i], w, k; i<=t; u=que[++i]) {
		if (!top[u]) top[u] = u;
		for (w=0, k=e.head[u]; k!=-1; k=e.next[k])
			if (fa[u] != e.to[k] && size[e.to[k]] > size[w])
				w = e.to[k];
		top[w] = top[u];
	}
	int tot, p;
	for (tot=0, p=2; p; p = next[p])
		pid[((p&1)? out[p>>1]:in[p>>1]) = ++tot] = p>>1;
}

struct Querys {
	int u, v, id, tim;
	Querys() {}
	Querys(int _u, int _v, int id, int tim): u(_u), v(_v), id(id), tim(tim) {
		if (in[v] < in[u]) swap(u, v);
	}
	bool operator < (const Querys&rhs) const {
		int tmp = in[u]/Size-in[rhs.u]/Size;
		if (tmp) return tmp<0;
		tmp = in[v]/Size-in[rhs.v]/Size;
		if (tmp) return tmp<0;
		return tim < rhs.tim;
	}
} task[maxn];

LL rem, ans[maxn];
int head=1, tail, at;

int lca(int u, int v) {
	while (top[u] != top[v])
		if (dep[top[u]] > dep[top[v]])
			u = fa[top[u]];
		else v = fa[top[v]];
	return dep[u]<dep[v]? u:v;
}

void jump(const int&p, int&t) {
	int &o=col[p];
	if (vis[p])
		rem += LL(wei[++cnt[t]])*val[t]-LL(wei[cnt[o]--])*val[o];
	swap(o, t);
}

void modify(int p) {
	int&o=col[p], &s=cnt[o];
	if (vis[p])
		vis[p]=false, rem-=LL(wei[s--])*val[o];
	else vis[p]=true, rem+=LL(wei[++s])*val[o];
}

void adjast(int u, int v, int tim) {
	int s=in[u], e=in[v];
	if (head>tail) head=s, tail=s-1;
	while (tail<e) modify(pid[++tail]);
	while (s<head) modify(pid[--head]);
	while (e<tail) modify(pid[tail--]);
	while (head<s) modify(pid[head++]);
	while (at<tim) ++at, jump(chg_pos[at], chg_to[at]);
	while (tim<at) jump(chg_pos[at], chg_to[at]), --at;
}

 
int main() {
#ifdef love_lhy
	file(3052);
#endif

	fr(n, m, q);
	rep(i, 1, m)
		fr(val[i]);
	rep(i, 1, n)
		fr(wei[i]);
	rep(i, 2, n)
		e.addEdge(fr(), fr());
	rep(i, 1, n)
		fr(col[i]);
	for (Size=0; Size*Size*Size<=n; ++Size);
	Size *= Size;
	bfs();

	rep(i, 1, q) {
		fr(t);
		if (!t) {
			++cntChg, fr(chg_pos[cntChg], chg_to[cntChg]);
		} else {
			++cntTask;
			task[cntTask] = Querys(fr(), fr(), cntTask, cntChg);
		}
	}

	sort(task+1, task+cntTask+1);
	rep(i, 1, cntTask) {
		int&u=task[i].u,&v=task[i].v;
		adjast(u, v, task[i].tim);
		int t = lca(u, v);
		if (out[u] < in[v]) modify(u);
		if (t!=u && t!=v) modify(t);
		ans[task[i].id] = rem;
		if (out[u] < in[v]) modify(u);
		if (t!=u && t!=v) modify(t);
	}
 
	rep(i, 1, cntTask) {
		printf("%lld\n", ans[i]);
	}
 
	return 0;
}
