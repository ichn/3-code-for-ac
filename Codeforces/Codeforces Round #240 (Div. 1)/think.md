
继续CF之旅， 专心搞CF吧。

##【Codeforces Round #240 (Div. 1)】A. Mashmokh and Numbers

>求$n$个不同的数使得$$\sum_{i=2j,i+1\le n}gcd(a_i,a_{i+1})$$等于给定的数

利用$gcd(i,i+1)=1$构造答案，注意特判边界情况。

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

int n, k;
vector<int> out;
map<int, int> s;
bool check() {
	foreach(i, out) {
		if ((*i) >= 1e9) {
			return false;
		}
		if (s.count((*i))) {
			return false;
		}
		++s[(*i)];
	}
	return true;
}
int main() {
#ifdef love_sbit
	file(414A);
#endif
	fr(n, k);
	if (n==1) {
		if (k==0) {
			puts("1");
		} else puts("-1");
	} else if (k==0) {
		if (n==1) {
			puts("1");
		} else puts("-1");
	} else if (n/2 > k)
		puts("-1");
	else {
		int j = n/2-1, top=(j)<<1|1;
		for (int i=0; i<j; ++i)
			out.pb(i<<1|1), out.pb((i+1)<<1);
		k -= j;
		for (int i=1; i<=n; ++i) 
			if (i*k >= top) {
				out.pb(i*k), out.pb((i+1)*k);
				break;
			}
		if (n&1) {
			out.pb(out.back()<1e9 ? out.back()+1:out.back()-1);
		}
		if (!check()) {
			puts("-1");
		} else {
			for(int i=0, sz=out.size(); i<sz; ++i) {
				printf("%d ", out[i]);
			}
			puts("");
		}
	}

	return 0;
}
```


##【Codeforces Round #240 (Div. 1)】B. Mashmokh and ACM

>求$n$长序列，满足$b_i|b_{i+1},b_i\le k$的数量

dp水

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

const int Mod = 1e9+7;
const int maxn = 2000 + 10;
int n, k;
LL f[maxn][maxn];
vector<int> fac[maxn];
int main() {
#ifdef love_sbit
	file(414B);
#endif
	for (int i=1; i<maxn; ++i)
		for (int j=1; j<=i; ++j)
			if (i%j == 0)
				fac[i].pb(j);
	fr(n, k);
	f[0][1]=1;
	for (int i=1; i<=k; ++i)
		for (int j=1; j<=n; ++j)
			foreach(k, fac[j])
				(f[i][j]+=f[i-1][*k])%=Mod;
	LL ans=0;
	for (int i=1; i<=n; ++i)
		(ans+=f[k][i])%=Mod;
	Wn(ans);
	return 0;
}

```

##【Codeforces Round #240 (Div. 1)】C. Mashmokh and Reverse Operation

>$2^n$长序列，支持询问$m$次把区间依次按$2^{p_i}$分成$2^{n-p_i}$个部分每个部分反转后依次插回的逆序对数量，每次操作保留影响

我太弱了啊，不过相信经过磨砺之后一定可以笑傲HNTSC的！

VP的时候想着想着就没控制住了，一个人在机房里想题就容易崩溃心里防线导致发生令自己后悔的事情，我要想办法啊。——冥想是个好办法，出去散散步是个好办法！

回到这道题。有几个性质：逆序对只会在块内发生变化，对块外没有影响；全部反转

于是想像一颗完全二叉树，叶子节点为权值，通过merge_sort可以求出每层的正反inverse_numbers数量，每次修改交换从叶子向上h每层的正反inverse_numbers就行了。没想到这点的原因是忽视了修改是全局性的。

代码写起来非常漂亮。

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

const int maxn = 20 + 1;
int status[maxn], n;
LL num[maxn][2];
vector<int> build(int n) {
	if (n==0) {
		return vector<int>(1, fr());
	} else {
		vector<int> l=build(n-1), r=build(n-1);
		for (int x=0; x<2; swap(l, r), ++x) {
			for (int i=0, j=0; i<(1<<(n-1)); ++i) {
				while (j<(1<<(n-1)) && l[i] > r[j])
					++j;
				num[n-1][x] += j;
			}
		}
		vector<int> ret(1<<n);
		merge(l.begin(), l.end(), r.begin(), r.end(), ret.begin());
		return ret;
	}
}


int main() {
#ifdef love_sbit
	file(414C);
#endif
	
	build(n = fr());
	for (int m=fr(), q; m--; ) {
		fr(q);
		for (int j=0; j<q; ++j)
			status[j] ^= 1;
		LL res = 0;
		for (int j=0; j<n; ++j)
			res += num[j][status[j]];
		Wn(res);
	}

	return 0;
}


```

##【Codeforces Round #240 (Div. 1)】D. Mashmokh and Water Tanks


出题人英语老师死的早。

我tm看日文都看懂了啊！

n頂点からなる木が与えられる。根は0番のノード。
各頂点には水槽がついている。お金をp円もっている。

最初にk個以下の好きなノードを選び、そのノードの水槽に1リットルずつ水を入れる。
次から全ての水槽が空になるまで以下の操作を繰り返す。
水槽のふたを全部あける
好きな水槽を（複数でもよい）選び、ふたを閉める。wリットル水が入った水槽のふたを閉めるのにかかる料金はw円
根の水槽を空にする
木の深さ1の頂点の水槽の水を、その親の水槽に移し変える。その水槽のふたが閉まっていたら飛ばす。親のふたは閉まっていても関係ない。

一つの水槽に（操作の途中の状態も含む）入っていた水の量の最大値を求めよ。


##学英语

一个小节目


vertex
'vɜːteks
n. 顶点


