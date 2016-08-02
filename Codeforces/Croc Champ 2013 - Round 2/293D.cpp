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

const int maxn = 1e5 + 100;
const int maxc = 1e6 + 10;
const int maxr = 2e6 + 100;
#define Range 1000000


int x[maxn], y[maxn];
DB x1[maxr], x2[maxr];

int n, cnt[maxr];

DB ans;

void calc() {
	int mi = INF, mx = -INF;
	reu(i, 0, maxr) {
		x1[i] = mx, x2[i] = mi;
	}
	rep(i, 1, n) {
		int ux = x[i], uy = y[i], 
			vx = x[i+1>n?1:i+1], vy = y[i+1>n?1:i+1];
		mi = min(mi, ux), mx = max(mx, ux);
		if (ux == vx) {
			x1[ux] = max(1.*max(uy, vy), x1[ux]);
			x2[ux] = min(1.*min(uy, vy), x2[ux]);
		} else {
			if (vx < ux) {
				swap(ux, vx), swap(uy, vy);
			}
			rep(r, ux, vx) {
				DB t = 1.*(uy-vy)/(ux-vx)*(r-ux)+uy;
				x1[r] = max(x1[r], t);
				x2[r] = min(x2[r], t);
			}
		}
	}
	LL tot = 0;
	rep(i, mi, mx) {
		int dn = (int)(x2[i]-1e-5)+1,
			up = (int)(x1[i]);
		tot += (cnt[i-mi] = up-dn+1);
	}
	DB sum = 0, s1 = 0, s2 = 0, s3 = 0;
	rep(i, 0, mx-mi) {
		sum += 1.*cnt[i]*(1.*i*i*s1-2.*i*s2+s3);
		s1 += cnt[i];
		s2 += 1.*i*cnt[i];
		s3 += 1.*i*i*cnt[i];
	}
	sum /= (1.*tot*(tot-1)/2);
	ans += sum;
}

int main() {
#ifdef love_sbit
	file(293D);
#endif
	fr(n);
	rep(i, 1, n) {
		fr(x[i], y[i]);
		x[i] += Range, y[i] += Range;
	}
	calc();
	rep(i, 1, n) {
		swap(x[i], y[i]);
	}
	calc();
	printf("%.10lf\n", ans/2);

	return 0;
}
