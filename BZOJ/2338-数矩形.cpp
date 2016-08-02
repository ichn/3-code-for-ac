#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define rer(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define sqr(x) ((x) * (x))
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
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); } // warning!! slower than printf
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

const int maxn = 1500 + 10;
struct Point {
	LL x, y;
	void read() {
		fr(x, y);
	}
	bool operator < (const Point&rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
	bool operator == (const Point&rhs) const {
		return x == rhs.x && y == rhs.y;
	}
} P[maxn];
struct Segment {
	Point x, y, m;
	LL len;
	Segment() {}
	Segment(Point x, Point y):x(x), y(y) {
		m.x = x.x + y.x, m.y = x.y + y.y;
		len = sqr(x.x - y.x) + sqr(x.y - y.y);
	}
	bool operator < (const Segment&rhs) const {
		return len < rhs.len || (len == rhs.len && m < rhs.m);
	}
} S[maxn * maxn];
int n, cnt;

inline void update(LL &a, LL b) {
	if(a < b) a = b;
}
inline LL cross(LL a, LL b, LL c, LL d) {
	return a * d - b * c;
}

int main() {
	fr(n);
	rep(i, 1, n)
		P[i].read();
	rep(i, 1, n) {
		rep(j, i + 1, n)
			S[++cnt] = Segment(P[i], P[j]);
	}
	sort(S + 1, S + cnt + 1);
	LL ans = 0;
	rep(i, 1, cnt) {
		int s = i, e = i + 1;
		while(e <= cnt && S[e].len == S[s].len && S[e].m == S[s].m) ++e;
		rer(j, s, e)
			rer(k, j + 1, e)
				update(ans, abs(cross(S[j].x.x - S[k].x.x, S[j].x.y - S[k].x.y, S[j].y.x - S[k].x.x, S[j].y.y - S[k].x.y)));
		i = e - 1;
	}
	Wn(ans);

	return 0;
}

