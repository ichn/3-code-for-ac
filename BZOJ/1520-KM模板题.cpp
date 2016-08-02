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

const int maxv = 200*2+10;
const int maxe = maxv*maxv*2;

class KM {

	public:

		int e, h[maxv], t[maxe], nxt[maxe], w[maxe], n, m, chg;

		KM() {
			e = 0;
			memset(h, -1, sizeof h);
		}

		void addEdge(int u, int v, int _w) {
			nxt[e]=h[u], t[e]=v, w[e]=_w, h[u]=e++;
		}

		int lx[maxv], ly[maxv], vis_x[maxv], vis_y[maxv], lnk[maxv];

		bool dfs(int u) {
			vis_x[u] = 1;
			for (int i=h[u]; i != -1; i=nxt[i]) 
				if (!vis_y[t[i]]) {
					int v = t[i], r = lx[u]+ly[v]-w[i];
					if (!r) {
						vis_y[v] = 1;
						if (!lnk[v] || dfs(lnk[v])) {
							lnk[v] = u;
							return true;
						}
					} //else chg = min(chg, r);
				}
			return false;
		}

		int KuhnMunkres(int _n, int _m) {
			n = _n, m = _m;
			rep(u, 1, n) {
				ly[u] = lnk[u] = 0;
				lx[u] = INT_MIN;
				for (int j=h[u]; j != -1; j=nxt[j])
					lx[u] = max(lx[u], w[j]);
			}
			rep(i, 1, n) {
				for (;;) {
					rep(j, 1, n) vis_x[j] = vis_y[j] = 0;
					chg = INT_MAX;
					if (dfs(i)) break;
					chg = INT_MAX;
					rep(u, 1, n) if (vis_x[u])
						for (int j=h[u]; j!=-1; j=nxt[j])
							if (!vis_y[t[j]])
								chg = min(chg, lx[u]+ly[t[j]]-w[j]);
	//				printf("%d\n", chg);
					if (chg == INT_MAX) {
						return INT_MIN;
					}
					rep(u, 1, n) {
						if (vis_x[u]) lx[u] -= chg;
						if (vis_y[u]) ly[u] += chg;
					}
				}
			}
			int ret = 0;
			rep(i, 1, n)
				ret += lx[i]+ly[i];
			return ret;
		}
};

int n, m, a, b, k;

int main() {
	freopen("1520.in", "r", stdin);
	freopen("1520.out", "w", stdout);

	fr(n);
	KM *sol = (new KM);
	rep(i, 1, n) {
		fr(m), fr(a, b, k);
		rep(j, a, b)
			sol->addEdge(i, j, -abs(m-j)*k);
	}

	int ans = sol->KuhnMunkres(n, n);

	if (ans == INT_MIN) {
		puts("NIE");
	} else 
		printf("%d\n", -ans);

	return 0;
}
