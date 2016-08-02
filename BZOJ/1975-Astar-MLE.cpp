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
#define rep(_i, _k, _j) for(short _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(short _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(short _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<short, short>
#define ivec vector<short>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
	const short INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef float DB;
	inline void pc(char c) { putchar(c); }
	template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
	template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
	template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
	template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
	inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
	template<class T> inline void fr(T&ret) { char c = ' '; short flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline short fr() { short x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
		return ret;
	}
};
using namespace my_useful_tools;

const int maxn = 5000 + 10;
const int maxe = 2e5 + 100;

short e, h[maxn], t[maxe], nxt[maxe];
float w[maxe];

void init() {
	e = 0;
	pse(h, -1);
}
vector<pair<float, pair<short, short> > > arc;
void addEdge(short u, short v, float _w) {
	nxt[e]=h[u], t[e]=v, w[e]=_w, h[u]=e++;
}

struct Node {
	short u;
	float d, a;
	bool operator < (const Node&rhs) const {
		return a > rhs.a;
	}
};

float dis[maxn], dis2[maxn];

priority_queue<Node> pq;

short n, a, b, m;
short cnt[maxn];
float r, c;

int main() {
	freopen("1975.in", "r", stdin);
	freopen("1975.out", "w", stdout);

	fr(n, m);
	scanf("%lf", &r);
	e = 0, pse(h, -1);
	rep(i, 1, m) {
		fr(a, b);
		scanf("%lf", &c);
		addEdge(b, a, c);
		arc.pb(mp(c, mp(a, b)));
	}
	while (!pq.empty()) pq.pop();
	rep(i, 1, n) dis[i] = 1e50;
	dis[n] = 0;
	pq.push((Node){n, 0.0, 0.0});
	while (!pq.empty()) {
		short u = pq.top().u;
		pq.pop();
		for (short i = h[u]; i != -1; i = nxt[i]) {
			short v = t[i];
			float d = dis[u] + w[i];
			if (d < dis[v]) {
				dis[v] = d;
				pq.push((Node){v, dis[v], dis[v]});
			}
		}
	}
	e = 0, pse(h, -1);
	foreach(i, arc) {
		addEdge(i->second.first, i->second.second, i->first);
	}
	while (!pq.empty()) pq.pop();
	pq.push((Node){1, 0, dis[1]});
	short ans = 0, k = (r/dis[1])+1;
	while (!pq.empty()) {
		short u = pq.top().u;
		float d = pq.top().d;
		pq.pop();
		++cnt[u];
		if (cnt[u] > k)
			continue;
		if (u == n) {
			if (d > r) {
				break;
			}
			r -= d;
			++ans;
			k = cnt[n]+(r/d)+1;
			continue;
		}
		for (short i = h[u]; i != -1; i = nxt[i]) {
			pq.push((Node){t[i], w[i]+d, w[i]+d+dis[t[i]]});
		}
	}
	printf("%d\n", ans);

	return 0;
}
