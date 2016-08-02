#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;

#define rep(i, j, k) for (int i = j; i < k; ++i)
#define rgo(i, j, k) for (int i = j; i <= k; ++i)

const int maxNode = 20 * 50 + 100;
const int maxLen = 1000 + 100;
const int MAX = 100000000;

short ch[maxNode][4];
int val[maxNode], f[maxNode];
int last[maxNode];

int sz;

int id(char c) {
	if (c == 'A')
		return 0;
	if (c == 'T')
		return 1;
	if (c == 'G')
		return 2;
	return 3;
}

void insert(char *s, int v) {
	int u = 0, n = strlen(s);
	rep(i, 0, n) {
		int c = id(s[i]);
		if (ch[u][c] == 0) {
			memset(ch[sz], 0, sizeof ch[sz]);
			val[sz] = 0;
			ch[u][c] = sz++;
		}
		u = ch[u][c];
	}
	val[u] = v;
}

char str[maxLen];
int N, Len;

void getFail() {
	queue<int> q;
	f[0] = 0;
	for (int c = 0; c < 4; ++c) {
		int u = ch[0][c];
		if (u) {
			f[u] = 0, q.push(u), last[u] = 0;
		}
	}
	while (!q.empty()) {
		int r = q.front(); q.pop();
		for (int c = 0; c < 4; ++c) {
			int u = ch[r][c];
			if (!u) {
				ch[r][c] = ch[f[r]][c];
				continue;
			}
			q.push(u);
			int v = f[r];
			while (v && !ch[v][c]) v = f[v];
			f[u] = ch[v][c];
			last[u] = val[f[u]] ? f[u] : last[f[u]];
		}
	}
}

int dp[2][maxNode];

void clr(int p) {
	rep(i, 0, sz+10)
		dp[p][i] = MAX;
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	int tCase = 0;
	while (scanf("%d\n", &N) != EOF && N != 0) {
		memset(ch[0], 0, sizeof ch[0]);
		sz = 1;
		rep(i, 0, N) {
			gets(str);
			insert(str, i + 1);
		}
		gets(str);
		Len = strlen(str);
		getFail();
		

		int cur = 0, lst = 1;
		clr(cur), clr(lst);
		dp[lst][0] = 0;
		rgo(i, 1, Len) {
			int g = id(str[i-1]);
			rep(j, 0, sz)
				if (val[j] == 0 && last[j] == 0 && dp[lst][j] != MAX) {
					rep(c, 0, 4) {
						if (c == g) {
							dp[cur][ch[j][c]] = min(dp[cur][ch[j][c]], dp[lst][j]);
						} else {
							dp[cur][ch[j][c]] = min(dp[cur][ch[j][c]], dp[lst][j] + 1);
						}
					}
				}
			swap(lst, cur);
			clr(cur);
		}
		int ans = MAX;
		rep(i, 0, sz)
			if (val[i] == 0 && last[i] == 0)
				ans = min(ans, dp[lst][i]);
		printf("Case %d: %d\n", ++tCase, ans == MAX ? -1 : ans);
	}

	return 0;
}
