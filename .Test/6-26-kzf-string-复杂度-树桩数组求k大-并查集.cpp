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

const int maxn = 3000000 + 111;

char str[maxn], tmp[maxn];
int n, k;

int l[maxn], r[maxn];

const int ip = 1<<22;
int c[ip+100];

void mdf(int p, int v) {
	for (; p <= ip; c[p] += v, p += p&-p);
}

int qrk(int k) {
	int p = ip;
	int gt = 0;
	for (int i = ip>>1; i; i>>=1) {
		if (gt + c[p - i] >= k)
			p -= i;
		else gt += c[p - i];
	}
	return p;
}

int fa[maxn];

int findfa(int p) {
	return fa[p] == p ? p : fa[p] = findfa(fa[p]);
}

int main() {
	file(string);

	scanf("%s", str + 1);
	fr(k, n);
	rep(i, 1, n)
		fr(l[i], r[i]);
	rep(i, 1, k) {
		mdf(i, 1);
		fa[i] = i;
	}
	int rec = k;
	red(i, n, 1) {
		if (r[i] >= k) continue;
		int len = r[i] - l[i] + 1;
		int p = 1;
		while (r[i] < k && (p<<1) <= len) {
			int w = qrk(r[i]+1);
			fa[w] = qrk(l[i] + (p<<1) - 1);
			mdf(w, -1);
			--k;
			++p;
		}
		p = 0;
		while (r[i] < k && (p<<1|1) <= len) {
			int w = qrk(r[i]+1);
			fa[w] = qrk(l[i] + (p<<1));
			mdf(w, -1);
			--k;
			++p;
		}
	}
	for (int i = 1; i <= k; ++i)
		tmp[qrk(i)] = str[i];
	for (int i = 1; i <= rec; ++i)
		tmp[i] = tmp[findfa(i)];
	for (int i = 1; i <= rec; ++i)
		pc(tmp[i]);
	puts("");
	return 0;
}


