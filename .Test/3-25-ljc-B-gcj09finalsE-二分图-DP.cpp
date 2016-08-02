#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 10;
const int INF = 0x3f3f3f3f;
map<string, int> M;
int nxt[maxn], lst[maxn], ans[maxn], fa[maxn], f[maxn][maxn>>1], cl[maxn];
int n;

bool dfs(int u, int r, int c) {
	if (fa[u]) {
		return cl[u] == c;
	}
	lst[r] = max(lst[r], nxt[u]);
	fa[nxt[u]] = fa[u] = r;
	cl[nxt[u]] = cl[u] = c;
	for (int i=1; i < u; ++i)
		if (nxt[i] && nxt[i]>u && nxt[u]>nxt[i])
			if (!dfs(i, r, c^1))
				return false;
	for (int i=u+1; i <= n+n; ++i) {
		if (nxt[i] && nxt[i]>nxt[u] && nxt[u]>i)
			if (!dfs(i, r, c^1))
				return false;
	}
	return true;
}

int calc(int x, int y) {
	if (y < 0) return INF;
	if (f[x][y] != -1) return f[x][y];
	int &ans=f[x][y];
	ans = INF;
	for (int c=0, t; c<2; ++c) {
		t = 0;
		for (int i=x, up=y, dn=0; ; ++i) {
			if (fa[i] == x) {
				if (cl[i] == c) {
					if (nxt[i]) --up;
					else ++up;
				} else {
					if (nxt[i]) ++dn;
					else --dn;
				}
			} else {
				t = max(t, dn+calc(i, up));
				i = lst[i];
			}
			if (up < 0) goto brk; // notice!
			if (up == y && !dn) break;
			t = max(t, dn);
		}
		ans = min(ans, t);
brk:;
	}
	return ans;
}

int main() {
	freopen("B.in", "r", stdin), freopen("B.out", "w", stdout);
	int T, ts;
	static string s;
	scanf("%d", &T);
	for (ts=1; ts <= T; ++ts) {
		int res = INF;
		printf("Case #%d: ", ts);
		scanf("%d", &n);
		M.erase(M.begin(), M.end());
		memset(nxt, 0, sizeof nxt);
		memset(lst, 0, sizeof lst);
		memset(ans, 0, sizeof ans);
		memset(cl, -1, sizeof cl);
		memset(fa, 0, sizeof fa);
		memset(f, -1, sizeof f);
		for (int i=1; i <= n+n; ++i) {
			cin >> s;
			if (M.count(s))
				nxt[M[s]] = i;
			else M[s] = i;
		}
		for (int i=1; i <= n+n; ++i)
			if (nxt[i] && !fa[i])
				if (!dfs(i, i, 0)) {
					puts("-1");
					goto stop;
				}
		for (int i=1; i <= n+n; ++i) 
			if (fa[i]==i)
				for (int j=1; j <= n; ++j)
					ans[j] = max(ans[j], calc(i, j));
		for (int i=1; i <= n; ++i)
			res = min(res, ans[i]+i);
		printf("%d\n", res);
stop:;
	}
	return 0;
}
