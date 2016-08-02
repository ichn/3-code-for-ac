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

const int alpha = 26;
const int maxn = 60 + 5;
const int maxl = 100 + 5;
const int maxm = maxn * maxl;
int ch[maxm][alpha], val[maxm], suf[maxm], pa[maxm];
int loc, n, m;
char str[maxl];

inline int idx(char c) {
	return c - 'A';
}

void insert(char *s) {
	int l = strlen(s);
	int u = 0, c;
	for (int i = 0; i < l; ++i) {
		c = idx(s[i]);
		if (!ch[u][c])
			ch[u][c] = ++loc;
		u = ch[u][c];
	}
	val[u] = 1;
}

int que[maxm];

void build_aho() {
	int f, b;
	f = b = 0;
	reu(i, 0, alpha)
		if (ch[0][i]) {
			que[b++] = ch[0][i];
			pa[ch[0][i]] = 0;
			suf[ch[0][i]] = 0;
		}

	while (f < b) {
		int c = que[f++];
		reu(i, 0, alpha) {
			int u = ch[c][i];
			if (!u) {
				ch[c][i] = ch[pa[c]][i];
				continue;
			}
			que[b++] = u;
			int v = pa[c]; // instead of : v = pa[u] !!
			while (v && !ch[v][i])
				v = pa[v];
			pa[u] = ch[v][i];
			suf[u] = val[pa[u]] ? pa[u] : suf[pa[u]];
		}
	}
}
 
int f[maxl][maxm];

const int mod = 10007;

inline void Mod(int &x) {
	while (x < 0)
		x += mod;
	while (x >= mod)
		x -= mod;
}

int main() {
#ifdef love_lhy
	file(1030);
#endif
	fr(n, m);
	loc = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		insert(str);
	}
	build_aho();
	f[0][0] = 1;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j <= loc; ++j) {
			if (f[i][j]) {
				reu(c, 0, alpha) {
					f[i+1][ch[j][c]] += (val[ch[j][c]] || suf[ch[j][c]]) ? 0 : f[i][j];
					Mod(f[i+1][ch[j][c]]);
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= loc; ++i) {
		ans += f[m][i];
		Mod(ans);
	}
	int p = 1;
	for (int i = 1; i <= m; ++i)
		(p *= 26) %= mod;
	//printf("%d\n", p);
 
	ans = p - ans + mod;
	Mod(ans);
	printf("%d\n", ans);
	
	return 0;
}

