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

const int maxn = 5e3 + 10;
#define x first
#define y second
int n, q, cnt;
vector<int> ans;
ipir apt[maxn];

int fa[maxn], rk[maxn];
int findfa(int u) {
	return fa[u] == u ? u : fa[u] = findfa(fa[u]);
}

bool inter(pair<int, int> x, pair<int, int> y)
{
	if (x.x > y.x) swap(x, y);
	if (x.x == y.x) return 0;
	if (x.y > y.x && x.y < y.y) return 1;
	return 0;
}


int vis[maxn], rev[maxn], col[maxn];
bool chk(int u, int v) {
	if (v < u) swap(u, v);
	apt[cnt+1] = mp(u, v);
	fa[cnt+1] = cnt+1;
	clr(vis);
	clr(rev);
	rep(i, 1, cnt)
		if (inter(apt[i], apt[cnt+1])) {
			int f = findfa(i);
			if (!vis[f]) {
				vis[f] = 1;
				if (!col[i]) rev[f] = 1;
			} else if (!(col[i]^rev[f]))
				return false;
		}
	rep(i, 1, cnt) {
		int f = findfa(i);
		if (vis[f]) col[i] ^= rev[f];
	}
	rep(i, 1, cnt) {
		if (vis[i]) {
			int fi = findfa(cnt+1), fj = i;
			if (rk[fi] < rk[fj])
				swap(fi, fj);
			fa[fj] = fi;
			rk[fi] += rk[fi] == rk[fj];
		}
	}
	++cnt;
	return true;
}


int u, v;
int main() {
	freopen("traf.in", "r", stdin);
	freopen("traf.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif

	fr(n, q);
	rep(i, 1, q) {
		fr(u, v);
		if (!chk(u, v)) {
			ans.pb(i);
		}
	}
	printf("%d\n", (int)ans.size());
	if (ans.size() > 0) {
		printf("%d\n", ans[0]);
		for (int i = 1; i < (int)ans.size(); ++i) {
			printf("%d\n", ans[i]);
		}
	}
 
	return 0;
}
