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



const int maxN = 200 + 100;
int n, m;
DB a, b, c, d, r;


vector<DB> equ[maxN], res, rec[maxN];
int eCnt;

const DB eps = 1e-7;
int sgn(DB x) {
	return x < -eps ? -1 : eps < x;
}

void solve() {
	int N = m*2 + 1;
	for (int i = 0; i < N; ++i) {
		int j = i;
		DB t = 0.0;
		for (int k = i; k < N; ++k)
			if (fabs(equ[k][i]) > t) {
				t = fabs(equ[k][i]);
				j = k;
			}
		if (sgn(t) == 0) continue;
		swap(equ[i], equ[j]);
		for (int k = 0; k < N; ++k)
			if (k != i) {
				DB t = equ[k][i] / equ[i][i];
				for (int w = 0; w < N+1; ++w)
					equ[k][w] -= t * equ[i][w];
			}
		//for (int k = i + 1; k < N; ++k)
		//	if (sgn(equ[k][i]) != 0) {
		//		DB t = equ[k][i] / equ[i][i];
		//		for (int w = i; w < N+1; ++w)
		//			equ[k][w] -= t * equ[i][w];
		//	}
	}
	for (int i = N-1; 0 <= i; --i) {
		//for (int j = i+1; j < N; ++j) {
		//	equ[i][N] -= equ[i][j] * res[j];
		//}
		for (int j = 0; j < N; ++j)
			if (sgn(equ[i][j]) != 0) {
				res[j] = equ[i][N] / equ[i][j];
			}
	}
}

bool chk() {
	for (int i = 0; i < m*2+1; ++i) {
		DB tt = 0;
		for (int j = 0; j < m*2+1; ++j)
			tt += rec[i][j] * res[j];
	//	printf("%.12lf\n", tt-rec[i][m*2+1]);
		if (sgn(tt-rec[i][m*2+1]) != 0) {
			return false;
		}
	}
	return true;
}

int main() {
#ifdef lol
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif

	int tCase = fr();
	while (tCase--) {
		fr(n, m);
		cin >> a >> b >> c >> d >> r;
		eCnt = 0;
		for (int i = 0; i <= (m<<1|1); ++i) {
			equ[i].resize(m*2 + 3);
			int sz = equ[i].size();
			for (int j = 0; j < sz; ++j)
				equ[i][j] = 0.0;
		}
		res.resize(m*3+3);
		int sz = res.size();
		for (int j = 0; j < sz; ++j)
			res[j] = 0.0;

		for (int i = -m; i <= m; ++i) {
			if (i <= 0) {
				//if (-m-2*i == i) {
				//	equ[i+m][m+i] = 1.0 - b / r - (1.0 * i * i) / (1.0 * m * m) / r;
				//	equ[i+m][m+m+1] = a / r;
				//	continue;
				//}
				equ[i+m][m+(-m-2*i)] -= (b / r + (1.0 * i * i) / (1.0 * m * m));
				equ[i+m][m+i] += 1;
				equ[i+m][m+m+1] += 1.0 * a / r;
			} else {
				//if (m+(m-2*i) == m+i) {
				//	equ[i+m][m+i] = 1.0 - d / r - (1.0 * i * i) / (1.0 * m * m) / r;
				//	equ[i+m][m+m+1] = c / r;
				//	continue;
			    //
				//}
				equ[i+m][m+(m-2*i)] -= (d / r + (1.0 * i * i) / (1.0 * m * m));
				equ[i+m][m+i] += 1;
				equ[i+m][m+m+1] += c / r;
			}
		}
		for (int i = 0; i < m*2+1; ++i) {
			rec[i] = equ[i];
		}

		solve();
	//	printf("%d\n", chk());

	//	foreach(i, res) {
	//		printf("%.2lf ", (*i));
	//	}
	//	puts("");
	//	for (int i = 0; i < m*2+1; ++i) {
	//		for (int j = 0; j <= m*2+1; ++j)
	//			printf("%.2lf ", rec[i][j]);
	//		puts("");
	//	}


		printf("%.9lf\n", res[m+n]);
	}


	return 0;
}
