#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 70 + 5;
#define x first
#define y second

int n, A[maxn][maxn], B[maxn][maxn];
int g[maxn][maxn], link[maxn], lx[maxn], ly[maxn], slack;
bool visx[maxn], visy[maxn];

bool search(int u) {
	visx[u] = true;
	for(int v = 1; v <= n; ++v) {
		if(!visy[v]) {
			if(lx[u] + ly[v] == g[u][v]) {
				visy[v] = true;
				if(link[v] == 0 || search(link[v])) {
					link[v] = u;
					return true;
				}
			} else {
				slack = min(slack,lx[u] + ly[v] - g[u][v]);
			}
		}
	}
	return false;
}

pair<int, int> KM() {
	memset(lx, -INF, sizeof lx);
	memset(ly, 0, sizeof ly);
	memset(link, 0, sizeof link);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			lx[i] = max(lx[i], g[i][j]);
		}
	}
	for(int i = 1; i <= n; ++i) {
		for( ; ; ) {
			slack = INF;
			memset(visx, false, sizeof visx);
			memset(visy, false, sizeof visy);
			if(search(i)) {
				break;
			} else {
				for(int j = 1; j <= n; ++j) {
					if(visx[j]) {
						lx[j] -= slack;
					}
					if(visy[j]) {
						ly[j] += slack;
					}
				}
			}
		}
	}
	int x = 0, y = 0;
	for(int i = 1; i <= n; ++i) {
		x += A[link[i]][i];
		y += B[link[i]][i];
	}
	return make_pair(x, y);
}

int work(pair<int, int> s, pair<int, int> t) {
	// ä¸¤ç¹å¼ (y - y2) / (y1 - y2) = (x - x2) / (x1 - x2)
	int a = s.x - t.x, b = t.y - s.y;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			g[i][j] = b * A[i][j] + a * B[i][j];
		}
	}
	pair<int, int> ret = KM();
	if(ret == s || ret == t) {
		return min(t.x * t.y, s.x * s.y);
	}
	return min(work(s, ret), work(ret, t));
}

int solve() {
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			g[i][j] = -A[i][j];
		}
	}
	pair<int, int> s = KM();
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			g[i][j] = -B[i][j];
		}
	}
	pair<int, int> t = KM();
	return work(s, t);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				scanf("%d", &A[i][j]);
			}
		}
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				scanf("%d", &B[i][j]);
			}
		}
		printf("%d\n", solve());

	}

	return 0;
}
