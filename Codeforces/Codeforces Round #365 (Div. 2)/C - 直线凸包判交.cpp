#include <bits/stdc++.h>
using namespace std;
namespace my_zone {
#define rep(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define rgo(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define clr(t) memset(t, 0, sizeof t);
#define clo(t, v) memcpy(t, v, sizeof t);
#define cls(t, v) memset(t,v,sizeof t);
#define pc(c) putchar(c)
#define gc() getchar()
	typedef pair<int, int> ipir;
	typedef vector<int> ivec;
	typedef set<int> iset;
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline char gchar(char r=gc()) {
		for(;r==' '||r=='\n'||r=='\r';
				r=gc());return r;}
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }

};
using namespace my_zone;

const DB _PI = 3.1415926535897;

struct P {
	DB x, y;
	void read() {
		cin >> x >> y;
	}
	P() {}
	P(DB x, DB y):x(x), y(y) {}
} p[31111];

P operator - (P a, P b) {
	return P(a.x - b.x, a.y - b.y);
}

DB cross(P a, P b) {
	return a.x * b.y - a.y * b.x;
}

const DB eps = 1e-8;
int sgn(DB x) {
	return x < -eps ? -1 : eps < x;
}

bool Con(P a1, P a2, P b1, P b2) {
	DB c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
	DB c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
	int a = sgn(c1) * sgn(c2);
	int b = sgn(c3) * sgn(c4);
	return a < 0 && b < 0;
}

int n, m;
DB u, v;

DB dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}

bool onSeg(P a, P x, P y) {
	return sgn(cross(a - x, y - x)) == 0 && sgn(dot(a - x, y - x)) > 0 && sgn(dot(a - y, x - y)) > 0;
}

bool Con(P a, P b) {
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (Con(p[i], p[i+1], a, b)) {
			return true;
		} else {
			if (onSeg(p[i], a, b) && onSeg(p[i+1], a, b))
				return false;
			if (onSeg(p[i], a, b) || onSeg(p[i+1], a, b))
				++cnt;
		}
	}
	if (cnt > 1) return true;
	//DB k = (b - a).y / (b - a).x;
	int i = 1, j = i + 1;
	for (; i <= n; ++i) {
		P v1 = p[i+1] - p[i];
		while (j <= i + n && sgn(cross(p[j+1] - p[j], v1)) > 0) {
			if (Con(a, b, p[i], p[j])) return true;
			++j;
		}
	}
	return false;
}

int main() {
#ifdef lol
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif

	fr(n, m);
	DB w = m;
	cin >> v >> u;
	for (int i = 1; i <= n; ++i)
		p[i].read();
	p[0] = p[n];
	for (int i = 1; i <= n; ++i)
		p[n+i] = p[i];
	if (!Con(P(0, 0), P(w/u*v, w))) {
		printf("%.12lf\n", w / u);
	} else {
		DB ss = _PI;
		int id;
		for (int i = 1; i <= n; ++i) {
			DB tt = atan2(p[i].y, p[i].x);
			if (sgn(ss - tt) >= 0) {
				ss = tt;
				id = i;
			}
		}
		DB ans = max(p[id].x / v, p[id].y / u);
		for (int i = id; ; ++i) {
			P t = p[i+1] - p[i];
			if (sgn(t.x) <= 0) { // || sgn(t.y / u - t.x / v) >= 0) {
				ans += (w - p[i].y) / u;
				break;
			}
			ans += max(t.x / v, t.y / u);
			}
			printf("%.12lf\n", ans);
		}

		return 0;
	}

