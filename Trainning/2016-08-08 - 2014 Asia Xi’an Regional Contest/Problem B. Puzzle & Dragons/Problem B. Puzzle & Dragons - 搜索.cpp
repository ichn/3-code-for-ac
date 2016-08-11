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

const int R = 5;
const int C = 6;

char g[R+2][C+2], f[R+2][C+2];
bool vis[R+2][C+2];
bool mrk[R+2][C+2];
bool inG(int a, int b) {
	return g[a][b] != '.';
}
bool inF(int a, int b) {
	return f[a][b] != '.';
}

const int Dx[] = {0 ,0, 1, -1};
const int Dy[] = {1, -1, 0, 0};
const char Dir[] = "RLDU";

struct Answer {
	int dir[10], stp, cmb, x, y, eli;
	bool operator < (const Answer &rhs) const {
		return cmb < rhs.cmb || (cmb == rhs.cmb && (eli < rhs.eli || (eli == rhs.eli && stp > rhs.stp)));
	}
	bool findEli() {
		memset(mrk, 0, sizeof mrk);
		bool ok = false;
		for (int i = 1; i <= R; ++i)
			for (int j = 1; j <= C; ++j) {
				if (inF(i, j) && inF(i-1, j) && inF(i+1, j) && (f[i][j] == f[i-1][j] && f[i-1][j] == f[i+1][j]))
					mrk[i][j] = mrk[i-1][j] = mrk[i+1][j] = ok = true;
				if (inF(i, j) && inF(i, j-1) && inF(i, j+1) && (f[i][j] == f[i][j-1] && f[i][j-1] == f[i][j+1]))
					mrk[i][j] = mrk[i][j-1] = mrk[i][j+1] = ok = true;
			}
		return ok;
	}
	void Eli(int x, int y, char c) {
		mrk[x][y] = false;
		f[x][y] = '.';
		for (int i = 0; i < 4; ++i) {
			int dx = x + Dx[i];
			int dy = y + Dy[i];
			if (inF(dx, dy) && mrk[dx][dy] && f[dx][dy] == c)
				Eli(dx, dy, c);
		}
	}
	void print() {
		printf("Combo:%d Length:%d\n", cmb, stp);
		printf("%d %d\n", x, y);
		for (int i = 0; i < stp; ++i)
			putchar(Dir[dir[i]]);
		puts("");
	}
	bool chk_ss() {
		if (stp != 9) return false;
		string t;
		for (int i = 0; i < stp; ++i)
			t += Dir[dir[i]];
		return t == "RURURDLDD";
	}
	void calc() {
		memcpy(f, g, sizeof g);
	//	print();
		cmb = 0;
		eli = 0;
		int tx = x;
		int ty = y;
		for (int i = 0; i < stp; ++i) {
			swap(f[tx][ty], f[tx+Dx[dir[i]]][ty+Dy[dir[i]]]);
			tx = tx+Dx[dir[i]];
			ty = ty+Dy[dir[i]];
		}
		while (findEli()) {
			for (int i = 1; i <= R; ++i)
				for (int j = 1; j <= C; ++j)
					if (mrk[i][j])
						Eli(i, j, f[i][j]), ++cmb;
			for (int i = 1; i <= C; ++i)
				for (int j = R-1; 0 < j; --j) {
					int x = j, y = i;
					while (f[x][y] != '.' && f[x+1][y] == '.' && x+1 <= R) {
						swap(f[x][y], f[x+1][y]);
						++x;
					}
				}
		}
		for (int i = 1; i <= R; ++i)
			for (int j = 1; j <= C; ++j)
				eli += f[i][j] == '.';
	}
	void clear() {
		stp = 0;
		cmb = 0;
		eli = 0;
	}
	void init(int _x, int _y) {
		x = _x;
		y = _y;
		stp = 0;
	}
} ans, tmp;

vector<Answer> Tmp;
void dfs(int x, int y, int lx, int ly) {
	if (tmp.stp == 10)
		return ;
	if (tmp.stp != 0)
		Tmp.pb(tmp);
	for (int i = 0; i < 4; ++i) {
		int dx = x + Dx[i];
		int dy = y + Dy[i];
		if (inG(dx, dy) && (dx != lx || dy != ly)) {
			tmp.dir[tmp.stp] = i;
			++tmp.stp;
			dfs(dx, dy, x, y);
			--tmp.stp;
		}
	}
}

int main() {
#ifdef lol
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif

	//clock_t st = clock();
	memset(g, '.', sizeof g);
	for (int i = 1; i <= R; ++i)
		for (int j = 1; j <= C; ++j)
			g[i][j] = 'A';
	for (int i = 1; i <= R; ++i)
		for (int j = 1; j <= C; ++j) {
			tmp.init(i, j);
			dfs(i, j, 0, 0);
		}
	//cout << Tmp.size() << endl;
	//return 0;
	int T = fr();
	for (int tt = 1; tt <= T; ++tt) {
		memset(g, '.', sizeof g);
		for (int i = 1; i <= R; ++i)
			for (int j = 1; j <= C; ++j)
				g[i][j] = gchar();
		tmp.clear();
		ans.clear();
		for (int i = 0; i < (int)Tmp.size(); ++i) {
			Tmp[i].calc();
			if (ans < Tmp[i])
				ans = Tmp[i];
		}
		printf("Case #%d:\n", tt);
		ans.print();
	}

	//cout << (DB)(clock() - st) / CLOCKS_PER_SEC << endl;
	return 0;
}

