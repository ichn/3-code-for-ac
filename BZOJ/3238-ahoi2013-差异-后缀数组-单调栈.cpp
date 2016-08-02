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

const int maxn = 500000 + 100;

char s[maxn];

struct SuffixArray {
	static const int maxl = maxn;
	static const int maxm = maxl;
	typedef int _arr[maxl];
	int n, m;
	_arr str, rank, sa, height, tmp1, tmp2, sum;
	int *x, *y;

	void construct() {
		x=tmp1, y=tmp2;
		for (int i=0; i<m; ++i)
			sum[i] = 0;
		for (int i=0; i<n; ++i)
			++sum[x[i]=str[i]];
		for (int i=1; i<m; ++i)
			sum[i] += sum[i-1];
		for (int i=n-1; 0<=i; --i)
			sa[--sum[x[i]]] = i;
		for (int k=1; k<=n; k<<=1) {
			int p = 0;
			for (int i=n-k; i<n; ++i)
				y[p++] = i;
			for (int i=0; i<n; ++i)
				if (sa[i]>=k)
					y[p++] = sa[i]-k;
			for (int i=0; i<m; ++i)
				sum[i] = 0;
			for (int i=0; i<n; ++i)
				++sum[x[y[i]]];
			for (int i=1; i<m; ++i)
				sum[i] += sum[i-1];
			for (int i=n-1; 0<=i; --i)
				sa[--sum[x[y[i]]]] = y[i];
			swap(x, y);
			p=1, x[sa[0]]=0;
			for (int i=1; i<n; ++i)
				x[sa[i]] = y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
			if (p >= n) break;
			m = p;
		}
    
		for (int i=0; i<n; ++i)
			rank[sa[i]] = i;
		for (int i=0, k=0, j; i<n; ++i) {
			if (0 < k) --k;
			j = sa[rank[i]-1];
			while (str[i+k] == str[j+k])
				++k;
			height[rank[i]] = k;
		}
	}
} SA;

int n;
int f[maxn];

LL ans;
struct Info {
	LL pos, val;
	LL cst;
} h[maxn];

int top;
LL sum;
#define x first
#define y second

int main() {

	scanf("%s", s);
	n = strlen(s);
	//s[n+1] = 'a'-1;
	for (int i = 0; i < n; ++i)
		SA.str[i] = s[i] - 'a' + 1;
	SA.str[n] = 0;
	SA.n = n+1, SA.m = 30;
	SA.construct();
	--n;
	//for (int i = 0; i <= n; ++i) {
	//	printf("%d ", SA.sa[i]);
	//} puts("");
	//return 0;
	for (int i = 2; i <= n+1; ++i)
		f[i-1] = SA.height[i];
	//for (int i = 1; i <= n; ++i) {
	//	printf("%d\n", f[i]);
	//}
	for (int i = 1; i <= n+1; ++i) {
		ans += (LL)i*(i-1) + (LL)(i-1)*i/2;
	}
	//printf("%lld\n", ans);
	sum = 0;
	top = 0;
	LL tmp = 0;
	h[top].val = 0;
	h[top].pos = 0;
	for (int i = 1; i <= n; ++i) {
		while (top && f[i] < h[top].val) {
			tmp -= h[top].cst;
			--top;
		}
		++top;
		h[top] = (Info){i, f[i], (LL)(i - h[top-1].pos) * f[i]};
		tmp += (i - h[top-1].pos) * f[i];
		sum += tmp;
	}
	printf("%lld\n", ans - 2*sum);

	return 0;
}

