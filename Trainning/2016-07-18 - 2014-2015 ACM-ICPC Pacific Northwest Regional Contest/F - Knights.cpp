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
	inline char gchar(char r=gc()) {
		for(;r==' '||r=='\n'||r=='\r';
				r=gc());return r;}
	template<class T> inline void fr(T&r) {
		char c=gc();
		for(;c<'0'||'9'<c;c=gc());
		for(r=0;'0'<=c&&c<='9';c=getchar())
			r=r*10+c-'0';
	}
	template<class T> inline void fr(T&a,T&b) {
		fr(a), fr(b);
	}
	template<class T> inline void fr(T&a,T&b,T&c) {
		fr(a), fr(b), fr(c);
	}
	int fr() {
		int r=0;char c=gc();
		for(;c<'0'||'9'<c;c=gc());
		for(r=0;'0'<=c&&c<='9';c=getchar())
			r=r*10+c-'0';
		return r;
	}
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




int n, m;

int mat[256][256], ret[256][256];
int ini[256], res[256];
const int mod = 1e9 + 9;

bool ok1(int a, int b) {
	bool ret = ((a<<2)&b)==0&&((b<<2)&a)==0;
	return ret && (((a>>2)&b)==0&&((b>>2)&a)==0);
}
bool ok2(int a, int b) {
	bool ret = ((a<<1)&b)==0&&((b<<1)&a)==0;
	return ret && (((a>>1)&b)==0&&((b>>1)&a)==0);
}

int mult(LL a, LL b) {
	return a * b % mod;
}

void add(int&x, int y) {
	(x+=y)%=mod;
}

string to_bin(int a, int d = 4) {
	if (d == 0) return "";
	string ret = "";
	ret+=('0'+(a&1));
	return to_bin(a>>1, d-1)+ret;
}

int r[256][256];
int M;
void mult(int (*a)[256], int (*b)[256]) {
	memset(r, 0, sizeof r);
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < M; ++j)
			for (int k = 0; k < M; ++k)
				add(r[i][j], mult(a[i][k], b[k][j]));
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < M; ++j)
			a[i][j] = r[i][j];
}

int solve() {
	if (n == 1)
		return 1<<m;
	n -= 2;
	M = (1<<(2*m));
	memset(res, 0, sizeof res);
	if (n != 0) {
		for (int i = 0; i < M; ++i)
			ret[i][i] = 1;
		for (; n; mult(mat, mat), n>>=1)
			if (n&1) mult(ret, mat);
		rep(i, 0, M)
			rep(j, 0, M)
				add(res[i], mult(ini[j], ret[i][j]));
	} else {
		rep(i, 0, 1<<(2*m))
			res[i] = ini[i];
	}
	int ans = 0;
	rep(i, 0, 1<<(2*m))
		add(ans, res[i]);
	return ans;
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	int tCase = fr();
	while (tCase--) {
		fr(m, n);
		memset(ini, 0, sizeof ini);
		memset(mat, 0, sizeof mat);
		memset(ret, 0, sizeof ret);
		for (int i = 0; i < 1<<m; ++i)
			for (int j = 0; j < 1<<m; ++j)
				if (ok1(i, j)) {
		//			cout << to_bin(i) << "\n" << to_bin(j) << endl;
					ini[(i<<m)|j] = 1;
					for (int k = 0; k < 1<<m; ++k)
						if (ok1(j, k) && ok2(i, k))
							mat[(i<<m)|j][(j<<m)|k] = 1;
				}
		cout << solve() % mod << endl;
	}
	return 0;
}
