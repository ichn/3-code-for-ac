#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define _pir pair<int, int>
#define _vec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define pfile(x) freopen(#x".in", "r", stdin), freopen("_"#x".out", "w", stdout)
#define hfile freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define gfile(x) freopen(#x".in", "w", stdout);
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
};
using namespace my_useful_tools;

const int maxn = 2e6 + 100;

int n, m;
int c[maxn];
int fa[maxn];


int que[maxn], qh, qt;
vector<int> son[maxn];

bool cmp(const int &x, const int &y) {
	return c[x] < c[y];
}

int main() {

	freopen("4027.in", "r", stdin);
	freopen("4027.out", "w", stdout);

	fr(n, m);
	reu(i, 0, n)
		fr(c[i]);
	reu(i, 0, n) {
		int x = fr();
		c[i] += x;
		reu(j, 0, x) {
			int v = fr();
			fa[v] = i;
			son[i].pb(v);
		}
	}
	fa[0] = -1;

	que[qh = qt = 1] = 0;
	while (qh <= qt) {
		int u = que[qh++];
		foreach(j, son[u])
			que[++qt] = *j;
	}

	int cnt = 0;
	for (int i = qt; 1 <= i; --i) {
		int u = que[i];
		sort(son[u].begin(), son[u].end(), cmp);
		foreach(j, son[u]) {
			if (c[u] + c[*j] - 1 <= m) {
				++cnt;
				c[u] += c[*j];
				--c[u];
			}
		}
	}

	printf("%d\n", cnt);

	return 0;
}

