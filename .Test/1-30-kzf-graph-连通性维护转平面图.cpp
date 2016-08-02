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
 
const int maxn = 1e5 + 100;
const int maxm = maxn*4;
 
int n, m, ope, t;

#define x first
#define y second

int fa[maxn*2];
int to[maxn], s;
ipir c[maxn], e[maxn];
int ans;
int findfa(int x) {
	return fa[x]==x? x:fa[x]=findfa(fa[x]);
}
void add(int x, int y) {
	x = findfa(x), y = findfa(y);
	if (x == y)
		++ans;
	else fa[x] = y;
}


int main() {
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif
	fr(n);
	int l=1, r=0, s=1;
	rep(i, 1, n) {
		fr(to[i]);
		if (to[i] > i) {
			e[i] = mp(s, s+1);
			while (l < i) c[l].x=s, ++l;
			while (r < to[i]) c[r].y=s, ++r;
			++s;
		}
	}
	while (l < n) c[l].x = s, ++l;
	while (r < n) c[r].y = s, ++r;
	fr(m);
	rep(i, 1, s) fa[i] = i;
	int lastans = 1;
	ans = 1;
	while (m--) {
		fr(ope, t);
		t ^= lastans;
		if (!ope) {
			add(c[t].x, c[t].y);
		} else {
			if (to[t] < t)
				t = to[t];
			add(e[t].x, e[t].y);
		}
		printf("%d\n", lastans = ans);
	}

	return 0;
}
