
##Codeforces Round #248 (Div. 1) A. Ryouko's Memory Note

>给$n$和$m$，一行$m$个$1\le x\le n$的数。记$c=\sum_{i=2}^{m}|a[i]-a[i-1]|$.现在只能选择一个数$x$变成$y$，序列中所有等于$x$的值都变成$y$，求最小的$c$

本人当年第二场CF，做到这题以为所有的数都是distinct的直接贪心，交了多发掉rating了。。


比当年还是有点进步的吧，起码看出中位数了。

```
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

int n, m;

const int maxn = 1e5 + 10;
vector<int> piv[maxn];
int a[maxn];

int main() {
#ifdef love_sbit
	file(434A);
#endif
	fr(n, m);
	rep(i, 1, m) fr(a[i]);
	a[0]=a[1], a[m+1]=a[m];
	m = unique(a+1, a+m+1)-a-1;
	LL ans = 0;
	rep(i, 2, m) {
		ans += abs(a[i]-a[i-1]);
	}
	if (m>1) {
		piv[a[1]].pb(a[2]);
		piv[a[m]].pb(a[m-1]);
	}
	rep(i, 2, m-1) {
		piv[a[i]].pb(a[i-1]);
		piv[a[i]].pb(a[i+1]);
	}
	LL mxc = 0;
	rep(i, 1, n) {
		int s = piv[i].size();
		if (!s)
			continue;
		sort(piv[i].begin(), piv[i].end());
		int t = piv[i][s/2];
		LL sc=0, ts=0;
		reu(j, 0, s)
			ts += abs(piv[i][j]-i),
			sc += abs(t-piv[i][j]);
		if (ts-sc > mxc)
			mxc = ts-sc;
	}
	Wn(ans-mxc);

	return 0;
}
```

##Codeforces Round #248 (Div. 1) B. Nanami's Digital Board

>给$n\times m$的01矩阵，$q$次操作，每次有两种：1）将$(x,y)$位置值翻转 2）计算以$(x,y)$在边界上的矩形的面积最大值（$1\le n, m, q \le 1000$）

考虑无修改，求最大子矩阵维护up,down,right,left，使用单调队列或并查集是近乎$O(n)$的；有修改？暴力修改$4n$个元素即可。次奥。没想出来不是不会，而是没认真想。

```
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

const int maxn = 1000 + 10;

int n, m, q;

int a[maxn][maxn], l[maxn][maxn], r[maxn][maxn], u[maxn][maxn], d[maxn][maxn];

int calc1(int x, int y, int h[][maxn]) {
	int L=y, R=y, h0, s=0;
	while (h0 = max(h[x][L], h[x][R])) {
		while (h[x][L] >= h0) --L;
		while (h[x][R] >= h0) ++R;
		s = max(s, (R-L-1)*h0);
	}
	return s;
}
int calc2(int x, int y, int h[][maxn]) {
	int L=x, R=x, h0, s=0;
	while (h0 = max(h[L][y], h[R][y])) {
		while (h[L][y] >= h0) --L;
		while (h[R][y] >= h0) ++R;
		s = max(s, (R-L-1)*h0);
	}
	return s;
}

int main() {
#ifdef love_sbit
	file(434B);
#endif
	fr(n, m, q);
	rep(i, 1, n)
		rep(j, 1, m)
			fr(a[i][j]);
	rep(i, 1, n)
		rep(j, 1, m) {
			u[i][j] = (1+u[i-1][j])*a[i][j];
			l[i][j] = (1+l[i][j-1])*a[i][j];
		}
	red(i, n, 1)
		red(j, m, 1) {
			d[i][j] = (1+d[i+1][j])*a[i][j];
			r[i][j] = (1+r[i][j+1])*a[i][j];
		}
	int t, x, y;
	rep(i, 1, q) {
		fr(t, x, y);
		if (t==1) {
			a[x][y] ^= 1;
			rep(j, 1, n) u[j][y] = (1+u[j-1][y])*a[j][y];
			red(j, n, 1) d[j][y] = (1+d[j+1][y])*a[j][y];
			rep(j, 1, m) l[x][j] = (1+l[x][j-1])*a[x][j];
			red(j, m, 1) r[x][j] = (1+r[x][j+1])*a[x][j];
		} else {
			Wn(max(max(calc1(x, y, u), calc1(x, y, d)), max(calc2(x, y, l), calc2(x, y, r))));
		}
	}

	return 0;
}
```


##Codeforces Round #248 (Div. 1) C. Tachibana Kanade's Tofu

>$m$进制下有$n$个带权字符串，一个字符串的权值定义为子串权值之和，求$[l,r]$内所有权值小于$k$的字符串个数（$1\le n\le 200,2\le m \le 20,1\le k\le 500,1\le l\le r\le 10^{200}）

##Codeforces Round #248 (Div. 1)


##Codeforces Round #248 (Div. 1)


##学英语

一个小节目，把英语单词搞下来哈哈。

verdict
'vɜːdɪkt
n. 结论；裁定

stretch
stretʃ
n. 伸展，延伸
vt. 伸展,张开
adj. 可伸缩的
vi. 伸展

quadratic
kwɒ'drætɪk
n. 二次方程式
adj. [数] 二次的

spicy
'spaɪsɪ
adj. 辛辣的；香的，多香料的；下流的

canteen
kæn'tiːn
n. 食堂，小卖部；水壶

assign
ə'saɪn
vt. 分配；指派；[计][数] 赋值
vi. 将财产过户（尤指过户给债权人）
