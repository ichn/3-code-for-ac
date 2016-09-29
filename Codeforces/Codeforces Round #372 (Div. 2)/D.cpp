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


const int maxV = 1210;
const int maxE = 10010 * 3;

int h[maxV], to[maxE], nxt[maxE], wei[maxE];
int e;
int n, m, s, t, L;

int que[maxE * 20], qh, qt;
int dis[maxV];
bool inq[maxV];

int spfa() {
	memset(inq, 0, sizeof inq);
	memset(dis, INF, sizeof dis);
	dis[s] = 0;
	que[qh = qt = 0] = s;
	inq[s] = true;
	while (qh <= qt) {
		int u = que[qh++];
		inq[u] = false;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			int w = wei[i];
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				if (!inq[v]) {
					que[++qt] = v;
					inq[v] = true;
				}
			}
		}
	}
	return dis[t];
}

void p() {
	puts("YES");
	for (int i = 0; i < e; i += 2) {
		printf("%d %d %d\n", to[i], to[i^1], wei[i]);
	}
	return ;
}

void solve() {
	for (int i = 0; i < e; i += 2) {
		if (wei[i] != INF) continue;
		wei[i] = 1;
		wei[i^1] = 1;

		que[qh = qt = 0] = to[i];
		que[++qt] = to[i^1];

		inq[to[i^1]] = true;
		inq[to[i]] = true;

		while (qh <= qt) {
			int u = que[qh++];
			inq[u] = false;
			for (int i = h[u]; i != -1; i = nxt[i]) {
				int v = to[i];
				int w = wei[i];
				if (dis[u] + w < dis[v]) {
					dis[v] = dis[u] + w;
					if (!inq[v]) {
						que[++qt] = v;
						inq[v] = true;
					}
				}
			}
		}
		if (dis[t] <= L) {
			wei[i] += L - dis[t];
			wei[i^1] += L - dis[t];
			p();
			return ;
		}
	}
	puts("NO");
}

int main() {

#ifdef love_yxl
	file(D);
#endif

	e = 0;
	memset(h, -1, sizeof h);

	fr(n, m), fr(L), fr(s, t);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		fr(u, v, w);
		if (w == 0)
			w = INF;
		to[e] = v, nxt[e] = h[u], wei[e] = w, h[u] = e++;
		to[e] = u, nxt[e] = h[v], wei[e] = w, h[v] = e++;
	}

	int d = spfa();
	//printf("%d\n", d);
	if (d < L) {
		puts("NO");
	} else {
		if (d == L) {
			p();
			return 0;
		}
		solve();
	}


	return 0;
}

