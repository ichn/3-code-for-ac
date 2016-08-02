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
#define rep(_i, _k, _j) for(LL _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(LL _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(LL _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<LL, LL>
#define ivec vector<LL>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
	template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
	template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
	template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
	inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
	template<class T> inline void fr(T&ret) { char c = ' '; LL flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline LL fr() { LL x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
		return ret;
	}
};
using namespace my_useful_tools;
//#define generator_sbit

namespace bf30 {

const LL maxn = 10000 + 10;

LL n, m, ope, x, to;

set<LL> c[maxn];
LL col[maxn];
LL ans;

LL ban[maxn];

void solve() {
	ans = 0;
	memset(ban, 0, sizeof ban);
	rep(i, 1, n) {
		if (1 < c[i].size()) {
			set<LL>::iterator pre = c[i].begin(), suc = pre;
			for(++suc; suc != c[i].end(); ++pre, ++suc)
				ban[*suc] = max(ban[*suc], *pre);
		}
	}
	LL last = 1;
	for (LL i=1; i<=n; ++i) {
		last = max(last, ban[i]+1);
		ans += i - last + 1;
	}
}


LL main() {
	rep(i, 1, n) {
		c[col[i] = fr()].insert(i);
	}
	fr(m);
	while (m--) {
		fr(ope);
		if (ope == 0) {
			solve();
			printf("%lld\n", ans);
		} else {
			fr(x, to);
			c[col[x]].erase(x);
			c[col[x] = to].insert(x);
		}
	}

	return 0;
}

}

namespace orzkzf {
	const LL maxn = 1e6 + 100;
	const LL maxm = maxn<<2;
	LL sum[maxm], mn[maxn], mx[maxn], sp[maxn];
	LL n, m, ans, p[maxn], last[maxn], next[maxn], col[maxn];
	set<LL> has[maxn];
	typedef set<LL>::iterator si;
	LL ql, qr, pos, get, q1;

	void find(LL l, LL r, LL rt) {
		if (l == r) {
			pos = l;
			return ;
		}
		LL mid = (l+r)>>1;
		if (p[mn[rt<<1|1]] < q1) 
			find(mid+1, r, rt<<1|1);
		else {
			get += sum[rt<<1|1]+sp[rt];
			find(l, mid, rt<<1);
		}
	}
	
	void modify(LL l, LL r, LL rt) {
		if (p[mn[rt<<1|1]] <= p[mn[rt<<1]]) {
			mn[rt] = mn[rt<<1|1];
			sum[rt] = sum[rt<<1|1];
			return ;
		}
		LL mid = (l+r)>>1;
		mn[rt] = mn[rt<<1];
		get = pos = 0;
		q1 = p[mn[rt<<1|1]], find(l, mid, rt<<1);
		sp[rt] = p[mn[rt<<1|1]]*(mn[rt<<1|1]-pos);
		sum[rt] = sum[rt<<1|1]+sum[rt<<1]-get+sp[rt];
		sp[rt] -= get;
	//	printf("%lld %lld %lld\n", sum[rt], mn[rt], sp[rt]);
	}
	void build(LL l, LL r, LL rt) {
		if (l == r) {
			mn[rt]=l, sum[rt]=0;
			return ;
		}
		LL mid = (l+r)>>1;
		build(l, mid, rt<<1), build(mid+1, r, rt<<1|1);
		modify(l, r, rt);
	}

	void change(LL l, LL r, LL rt) {
		if (l == r)
			return ;
		LL mid = (l+r)>>1;
		if (ql <= mid)
			change(l, mid, rt<<1);
		else change(mid+1, r, rt<<1|1);
		modify(l, r, rt);
	}

	void fresh(LL x, LL to) {
		p[x] = to;
		ql = x;
		change(1, n, 1);
	}


	LL main() {
		rep(i, 1, n) {
			fr(col[i]);
			has[col[i]].insert(i);
			last[i] = p[col[i]];
			if (p[col[i]]) next[p[col[i]]] = i;
			p[col[i]] = i;
		}
		rep(i, 1, n) {
			if (!next[i]) next[i] = n+1;
			p[i] = n+1;
		}
		rep(i, 1, n)
			if (last[i] != 0)
				p[last[i]] = i;
		fr(m);
		build(1, n, 1);
	//	printf("%lld %lld %lld\n", sum[1], mn[1], sp[1]);
		while (m--) {
			LL type, x, to;
			fr(type);
			if (!type) {
				ans = sum[1] + p[mn[1]]*mn[1];
				ans -= n*(n+1)/2;
				printf("%lld\n", ans);
			} else {
				fr(x, to);
				if (last[x]) fresh(last[x], next[x]);
				fresh(x, n+1);
				if (last[x])
					next[last[x]] = next[x];
				if (next[x])
					last[next[x]] = last[x];
				has[col[x]].erase(x);

				si it;
				col[x]=to, it=has[col[x]].lower_bound(x);
				if (it == has[col[x]].end())
					next[x] = n+1;
				else next[x]=*it, last[next[x]]=x;
				if (it == has[col[x]].begin())
					last[x] = 0;
				else last[x]=*(--it), next[last[x]]=x;
				has[col[x]].insert(x);
				if (last[x]) fresh(last[x], x);
				fresh(x, next[x]);
			}
		}

		return 0;
	}
}

int main() {
	freopen("array.in", "r", stdin), freopen("array.out", "w", stdout);
	LL n;
	fr(n);
	if (false && n <= 3000) {
		bf30::n = n;
		bf30::main();
	} else {
		orzkzf::n = n;
		orzkzf::main();
	}

	return 0;
}

