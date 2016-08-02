#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for (int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for (int _i = _k; _j <= _i; --_i)
#define reu(_i, _k, _j) for (int _i = _k; _i <  _j; ++_i)
#define Edges (_i, _u, _e) for (int _i = _e.head[_u]; _i != -1; _i = _e.next[_i])
#define foreach (_i, _s) for (typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr (t) memset(t, 0, sizeof t)
#define pse (t, v) memset(t, v, sizeof t)
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

const int maxd = 6;
const int maxn = 11;

/*
0: 正面
1: 左面
2: 背面
3: 右面
4: 上面
5: 下面
0面正对自己
正方体左前下脚为坐标原点
x横
y纵
z竖
X死出题人
    y
 **********
 **********
x***d******
 **********
 **********
 **********
 **********
 */

int n, cube[maxn][maxn][maxn];
 
inline void get(int f, int x, int y, int d, int &rx, int &ry, int &rz) {
	if (f == 0) {
		rx = y, ry = d, rz = n-x-1;	
	} else if (f == 1) {
		rx = d, ry = n-y-1, rz = n-x-1;
	} else if (f == 2) {
		rx = n-y-1, ry = n-d-1, rz = n-x-1;
	} else if (f == 3) {
		rx = n-d-1, ry = y, rz = n-x-1;
	} else if (f == 4) {
		rx = y, ry = n-x-1, rz = n-d-1;
	} else if (f == 5) {
		rx = y, ry = x, rz = d;
	}
}


char pre[maxd][maxn][maxn];

int main() {
	file(cube);
	//clock_t start = clock();
	while (scanf("%d", &n) != EOF && n != 0) {
		int x, y, z;
		reu(j, 0, n)
			reu(i, 0, 6)
				scanf("%s", pre[i][j]);
		reu(i, 0, n)
			reu(j, 0, n)
				reu(k, 0, n)
					cube[i][j][k] = '?';
		reu(f, 0, 6)
			reu(i, 0, n)
				reu(j, 0, n)
					if (pre[f][i][j] == '.')
						reu(d, 0, n) {
							get(f, i, j, d, x, y, z);
							cube[x][y][z] = '.';
						}
		bool con;
		do {
			con = false;
			reu(f, 0, 6) reu(i, 0, n) reu(j, 0, n) 
				if (pre[f][i][j] != '.') {
					reu(d, 0, n) {
						get(f, i, j, d, x, y, z);
						if (cube[x][y][z] != '.') {
							if (cube[x][y][z] == '?') {
								cube[x][y][z] = pre[f][i][j];
								con = true;
								break;
							} else if (cube[x][y][z] == pre[f][i][j]) {
								break;
							} else {
								cube[x][y][z] = '.';
								con = true;
							}
						}
					}
				}
		} while(con);
		int cnt = 0;
		reu(i, 0, n) reu(j, 0, n) reu(k, 0, n)
			cnt += (cube[i][j][k] != '.');
		printf("Maximum weight: %d gram(s)\n", cnt);
	}
	//printf("%lf\n", (DB)(clock() - start) / CLOCKS_PER_SEC);
	return 0;
}
