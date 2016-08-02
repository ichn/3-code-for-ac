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
 
const int maxn = 300000 + 10;
int n;
double a[maxn], len[maxn], sum[maxn];
int main() {
#ifdef love_lhy
	file(3450);
#endif
	fr(n);
	rep(i, 1, n) {
		scanf("%lf", &a[i]);
		char c = gchar();
		if (c == '?')
			a[i] = .5;
		else a[i] = (c=='x' ? 0 : 1);
	}
	len[0] = sum[0] = 0.0;
	for (int i = 1; i <= n; ++i) {
		len[i] = a[i]*(len[i-1]+1);
		sum[i] = sum[i-1] + a[i]*(2*len[i-1]+1);
	}
	printf("%.4lf\n", sum[n]);
	return 0;
}

/*
 * ps: 乔明达的《osu!》比这不知道高到哪里去了！
 * 考虑递推，我们用len[i]表示到第i次操作后缀全为1的期望长度，sum[i]表示到第i次操作的期望得分，显然
 * len[0] = 0, sum[0] = 0;
 * 考虑len[i]，在第i次操作以a[i]的概率得分的情况下，以a[i]的概率长度增加1，以1-a[i]的概率为0，所以len[i]=a[i]*(len[i-1]+1)（等于0对期望无贡献）
 * 考虑sum[i]，在长度增加1的时候增加(len[i-1]+1)^2-len[i-1]^2=2len[i-1]+1，以a[i]的概率增加所以sum[i] = sum[i-1] + a[i]*(2*len[i-1]+1)（等于0对期望无贡献）
 * */

