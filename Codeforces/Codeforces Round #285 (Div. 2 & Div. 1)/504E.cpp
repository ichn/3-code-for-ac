%:include <bits/stdc++.h>
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
 
const int maxn = 300000 + 100;
const int maxv = maxn, maxe = maxv*2;
struct Edge {
	int edge, head[maxv], to[maxe], next[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v) {
		to[edge] = v, next[edge] = head[u];
		head[u] = edge++;
	}
	void addEdge(int u, int v) {
		addedge(u, v);
		addedge(v, u);
	}
} e;


const int SuffixArray_maxLen = 300000 + 100;
const int SuffixArray_maxSize = 256;
typedef int arrN[SuffixArray_maxLen];
typedef int arrS[SuffixArray_maxSize+1];
struct SuffixArray {
	arrN s, sum, sa, rank, height, rmq[22], log_2;
	int l;
	
	void sort(int *a, int *b, int *c, int n, int m) {
		for (int i=0; i<=m; ++i)
			sum[i] = 0;
		for (int i=1; i<=n; ++i)
			++sum[c[i]];
		for (int i=1; i<=m; ++i)
			sum[i] += sum[i-1];
		for (int i=n; 0<i; --i)
			b[sum[c[a[i]]]--] = a[i];
	}

	void get_sa() {
		int n=l;
		static int x[maxn], y[maxn];
		for (int i=1; i<=n; ++i)
			rank[i]=i, x[i]=s[i];
		sort(rank, sa, x, n, 256);
		rank[sa[1]] = 1;
		for (int i=2; i<=n; ++i)
			rank[sa[i]] = rank[sa[i-1]]+(x[sa[i-1]]!=x[sa[i]]);
		for (int i=1; i<=n; i<<=1) {
			for (int j=1; j<=n; ++j)
				sa[j]=j, x[j]=rank[j], y[j]=j+i<=n?rank[i+j]:0;
			sort(sa, rank, y, n, n), sort(rank, sa, x, n, n);
			rank[sa[1]] = 1;
			for (int j=2; j<=n; ++j)
				rank[sa[j]] = rank[sa[j-1]]+(x[sa[j]]!=x[sa[j-1]] || y[sa[j]]!=y[sa[j-1]]);
			if (rank[sa[n]] == n)
				break;
		}
	}

	void get_height() {
		for (int i=1, j=0; i<=l; ++i) {
			j -= (j>0);
			if (rank[i] != 1)
				while (s[i+j] == s[sa[rank[i]-1]+j])
					++j;
			height[rank[i]] = j;
		}
	}

	void init_rmq() {
		for (int i=1; i<=l; ++i)
			rmq[0][i] = height[i];
		log_2[1] = 0;
		for (int i=2; i<=l; ++i)
			log_2[i] = log_2[i>>1]+1;
		for (int i=1; i<22; ++i) {
			for (int j=1; j<=l; ++j)
				rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);
		}
	}

	int get_min(int u, int v) {
		if (v < u) swap(u, v);
		int k = log_2[v-u+1]-1;
		return min(rmq[u][k], rmq[v-(1<<k)+1][k]);
	}

	int get_lcp(int u, int v) {
		return get_min(rank[u], rank[v]);
	}

	void append(char c) {
		s[++l] = c;
	}
	void build() {
		get_sa();
		for (int i=1; i<=l; ++i) {
			printf("%c", s[i]);
		} puts("");
		for (int i=1; i<=l; ++i) {
			printf("%d ", sa[i]);
		} puts("");
		get_height();
		init_rmq();

	}
} SA, rSA;

int n, q;
char str[maxn];
int top[maxn], son[maxn], chain[maxn], size[maxn], dep[maxn], fa[maxn], cnt_top, tmp;

void dfs(int u) {
	size[u]=1, tmp=0;
	for (int i=e.head[u], v; i!=-1; i=e.next[i]) {
		if ((v=e.to[i]) != fa[u]) {
			fa[v]=u, dfs(v);
			if (size[v] > tmp) {
				tmp = size[v];
				son[u] = v;
			}
			size[u] += size[v];
		}
	}
}

void get_chain(int u, int tp, int dp) {
	if (u == 0) return ;
	chain[u]=tp, dep[u]=dp;
	SA.append(str[u]);
	get_chain(son[u], tp, dp+1);
	for (int i=e.head[u], v; i!=-1; i=e.next[i]) {
		if ((v=e.to[i])!=fa[u] && v!=son[u]) {
			get_chain(v, ++tp, 0);
			top[tp] = u;
		}
	}
}

int solve() {
	
	return 0;
}
 
int main() {
#ifdef love_sbit
	file(504E);
#endif
	fr(n);
	scanf("%s", str+1);
	for (int i=1; i<n; ++i) {
		int u, v;
		fr(u, v);
		e.addEdge(u, v);
	}
	fa[1]=0, dfs(1);
	top[1]=1, get_chain(1, 1, 0);
	for (int i=1; i<=SA.l; ++i)
		rSA.append(SA.s[SA.l-i+1]);
	SA.build(), rSA.build();
	fr(q);
	while (q--) {
		int a, b, c, d;
		fr(a, b), fr(c, d);
		int ans = solve();
		printf("%d\n", ans);
	}

	return 0;
}
