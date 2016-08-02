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

	const int maxE = 10000, maxV = 10000;
	struct Edge {
		int e, h[maxV], to[maxE], nxt[maxE];
		void init() {
			cls(h,-1);
			e=0;
		}
		void addEdge(int u,int v) {
			to[e] = v, nxt[e] = h[u], h[u] = e++;
		}
	};
};
using namespace my_zone;

const int maxN = 1e5 + 1000;
int nl[maxN<<1];
int n, n2;

int val[maxN<<1];

int ans;

int tr[maxN<<1];
int f1[maxN<<1], f2[maxN<<1];

inline void add(int t, int v) {
	for (; t<=10000; tr[t] = max(tr[t], v), t+=t&-t);
}
inline int get(int p) {
	int r = 0;
	for (; p>0; r=max(r, tr[p]), p-=p&-p);
	return r;
}

int cc = 0;
int solve(int pos) {
	clr(tr); clr(f1); clr(f2);

	rgo(i, pos+1, n2) {
		if (nl[i] == 10000) continue;
		f1[i] = get(10000 - nl[i]) + nl[i];
		add(10000 - nl[i], f1[i]);
	}

	reverse(nl+1, nl+n2+1);
	clr(tr);
	rgo(i, n2-pos+1, n2) {
		if (nl[i] == 10000) continue;
		f2[i] = get(10000 - nl[i]) + nl[i];
		add(10000 - nl[i], f2[i]);
	}
	reverse(nl+1, nl+n2+1);
	reverse(f2+1, f2+n2+1);

	int j = pos+1, val = 0;
	int ret = 0;
	rgo(i, 1, pos) {
		if (i + n - 1 < pos) continue;
		while (j <= min(n2, i+n-1))
			val = max(val, f1[j]), ++j;
		ret = max(ret, val+f2[i]);
	}
	++cc;
	return ret;
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	while (scanf("%d", &n) != EOF) {
		rgo(i, 1, n) {
			scanf("%d", &nl[i]);
			nl[i+n] = nl[i];
		}
		n2 = n<<1;
		ans = 0;
		cc = 0;
		rgo(i, 1, n2)
			if (nl[i] == 10000) {
				ans = max(ans, solve(i));
			}

		printf("%d\n", ans + 10000);
	}

	return 0;
}
