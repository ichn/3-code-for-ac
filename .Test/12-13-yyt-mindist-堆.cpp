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

const int maxn = 2e5 + 100;
const int dim = 2;
struct Heap {
	int n;
	int a[maxn], pos[maxn], w[maxn];
	// a 元素下标 pos 元素在堆中的位置 w 权值
	void build();
	void shift_down(int x);
	void shift_up(int x);
	void remove(int x);
	void insert(int x);
};

void Heap::shift_down(int x) {
	if (x<<1 > n)
		return ;
	int p = ((x<<1|1)>n ? x<<1 : (w[a[x<<1|1]]<w[a[x<<1]] ? x<<1|1 : x<<1));
	if (w[a[p]] < w[a[x]]) {
		swap(a[p], a[x]);
		pos[a[p]] = p, pos[a[x]] = x;
		shift_down(p);
	}
}

void Heap::shift_up(int x) {
	if (x == 1)
		return ;
	int p = x>>1;
	if (w[a[x]] < w[a[p]]) {
		swap(a[x], a[p]);
		pos[a[x]] = x, pos[a[p]] = p;
		shift_up(p);
	}
}

void Heap::remove(int x) {
	pos[a[x]] = 0;
	if (x == n) {
		--n;
		return ;
	}
	a[x] = a[n--];
	pos[a[x]] = x;
	shift_down(x);
	shift_up(x);
}

void Heap::insert(int x) {
	a[++n] = x;
	pos[a[n]] = n;
	shift_up(n);
}

void Heap::build() {
	memset(pos, 0, sizeof pos);
	for (int i=1; i<=n; ++i)
		pos[a[i]] = i;
	for (int i=n; 0<i; --i)
		shift_down(i);
}

int n;
int coord[dim][maxn];
Heap hp[dim];
int dir[dim][maxn], next[dim][maxn];

void init() {
	fr(n);
	for (int i=1; i<=n; ++i)
		for (int j=0; j<dim; ++j)
			fr(coord[j][i]);
}

int getans(const int *a, int *d) {
	int s = 0;
	int pre = -1;
	d[1] = pre;
	for (int i=2; i<=n; ++i) {
		int now = (a[i-1]<a[i] ? -1 : 1);
		d[i] = now;
		s -= (now != pre);
		pre = now;
	}
	return s;
}

void build_heap(const int *a, const int *d, Heap&h) {
	h.n = 0;
	for (int i=1; i<n; ++i)
		if (d[i] != d[i+1]) {
			h.a[++h.n] = i;
			h.w[i] = abs(a[i]-a[i+1]);
		}
	h.build();
}

int get_first() {
	int minv = INF;
	int ret = -1;
	for (int i=0; i<dim; ++i)
		if (hp[i].n && hp[i].w[hp[i].a[1]] < minv)
			minv = hp[i].w[hp[i].a[1]], ret = i;
	return ret;
}

void solve() {
	int k = 0;
	LL ss = 0;
	for (int i=0; i < dim; ++i)
		k = k+getans(coord[i], dir[i]);
	for (int i=0; i < dim; ++i) {
		int co = coord[i][1];
		for (int j=2; j<=n; ++j)
			ss += abs(co-coord[i][j]),
			co = coord[i][j];
	}

	for (int i=0; i<dim; ++i)
		build_heap(coord[i], dir[i], hp[i]);
	for (int i=0; i<dim; ++i) {
		for (int j=1; j<=n; ++j)
			next[i][j] = j+1;
	}


	int lastout = 0;
	int lastk = k;
	long long lastss = ss;
	int now = 1, xx;
	while ((xx = get_first()) != -1) {
		int x = hp[xx].a[1];
		now = hp[xx].w[x];

		int toadd = 0;
		hp[xx].remove(hp[xx].pos[x]);
		++toadd;
		int nx = next[xx][x];
		if (hp[xx].pos[nx]) {
			hp[xx].remove(hp[xx].pos[nx]);
			++toadd;
		}
		next[xx][x] = next[xx][nx];
		if (next[xx][x]<=n && dir[xx][x]!=dir[xx][next[xx][x]]) {
			hp[xx].w[x] = abs(coord[xx][x]-coord[xx][next[xx][x]]);
			hp[xx].insert(x);
			--toadd;
		}
		if (toadd) {
			if (now > lastout) {
				printf("%d %d %lld\n", lastout, -lastk, lastss);
			}
			k += toadd;
			ss -= toadd*now;
			lastout = now;
			lastk = k;
			lastss = ss;
		}
	//return ;
	}
	printf("%d %d %lld\n", lastout, -k, ss);
}

int main() {

	file(mindist);

	init();
	solve();

	return 0;
}
