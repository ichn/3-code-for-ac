#include <cstdio>
#include <cstring>
#include <algorithm>
using std::sort;
using std::pair;
using std::swap;
using std::max;
using std::make_pair;
const int INF = 0x3f3f3f3f;
const int maxn = 300000 + 200;
const int maxe = maxn * 2;
#define x first
#define y second
struct Edge {
    int edge;
    int head[maxn], to[maxe], next[maxe];
    Edge() {
        edge = 0;
        memset(head, -1, sizeof head);
    }
    void addedge(int u, int v) {
        to[edge] = v;
        next[edge] = head[u];
        head[u] = edge++;
    }
} E;
int n, dep[maxn], anc[maxn][20], size[maxn];

int dfn[maxn], dfs_clock = 0;
void dfs(int x) {
	size[x] = 1;
	dfn[x] = ++dfs_clock;
	for(int i = E.head[x]; i != -1; i =E.next[i]) {
		if(E.to[i] != anc[x][0]) {
			anc[E.to[i]][0] = x;
			dep[E.to[i]] = dep[x] + 1;
			for(int j = 1; j <= 19; ++j) {
				anc[E.to[i]][j] = anc[anc[E.to[i]][j - 1]][j - 1];
			}
			dfs(E.to[i]);
			size[x] += size[E.to[i]];
		}
	}
}
bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}
int get(int u, int d) {
	for(int i = 19; 0 <= i; --i) {
		if(dep[anc[u][i]] >= d) {
			u = anc[u][i];
		}
	}
	return u;
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) {
		swap(x, y);
	}
	for(int i = 19; 0 <= i; --i) {
		if(dep[anc[x][i]] >= dep[y]) {
			x = anc[x][i];
		}
	}
	if(x == y) return x;
	for(int i = 19; 0 <= i; --i) {
		if(anc[x][i] != anc[y][i]) {
			x = anc[x][i];
			y = anc[y][i];
		}
	}
	return anc[x][0];
}

int fa[maxn], h[maxn], m, tot, ans[maxn], rec[maxn], w[maxn], t[maxn], val[maxn], stack[maxn];
pair<int, int> g[maxn];
void solve() {
	scanf("%d", &m);
	tot = m;
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &h[i]);
		t[i] = rec[i] = h[i];
		g[h[i]] = make_pair(0, h[i]);
		ans[h[i]] = 0;
	}
	sort(h + 1, h + m + 1, cmp);
	for(int top = 0, i = 1; i <= m; ++i) {
		if(!top) {
			stack[++top] = h[i];
			fa[h[i]] = 0;
		} else {
			int u = h[i], p = lca(u, stack[top]);
			for(; dep[stack[top]] > dep[p] && 0 < top; --top) {
				if(dep[stack[top - 1]] <= dep[p]) {
					fa[stack[top]] = p;
				}
			}
			if(stack[top] != p) {
				fa[p] = stack[top];
				stack[++top] = p;
				t[++tot] = p;
				g[p] = make_pair(INF, 0);
			}
			fa[u] = p;
			stack[++top] = u;
		}
	}
	sort(t + 1, t + tot + 1, cmp);			
	for(int i = 1; i <= tot; ++i) {
		int p = t[i];
		val[p] = size[p];
		if(i != 1) {
			w[p] = dep[p] - dep[fa[p]];
		}
	}
	for(int i = tot; 1 < i; --i) {
		int u = t[i], p = fa[u];
		g[p] = min(g[p], make_pair(g[u].x + w[u], g[u].y));
	}
	for(int i = 2; i <= tot; ++i) {
		int u = t[i], p = fa[u];
		g[u] = min(g[u], make_pair(g[p].x + w[u], g[p].y));
	}
	for(int i = 1; i <= tot; ++i) {
		int u = t[i], p = fa[u];
		if(i == 1) {
			ans[g[u].y] = n - size[u];
		} else {
			int x = get(u, dep[p] + 1), sum = size[x] - size[u];
			val[p] -= size[x];
			if(g[p].y == g[u].y) {
				ans[g[u].y] += sum;
			} else {
				int mid = dep[u] - ((g[p].x + g[u].x + w[u]) / 2 - g[u].first);
				if((g[p].x + g[u].x + w[u]) % 2 == 0 && g[u].y > g[p].y) {
					++mid;
				}
				int y = size[get(u, mid)] - size[u];
				ans[g[u].second] += y;
				ans[g[p].second] += sum - y;
			}
		}
	}
	for(int i = 1; i <= tot; ++i) {
		ans[g[t[i]].second] += val[t[i]];
	}
	for(int i = 1; i <= m; ++i) {
		printf("%d ", ans[rec[i]]);
	}
	puts("");
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		E.addedge(u, v);
		E.addedge(v, u);
	}
	dep[1] = 1;
	dfs(1);
	int test_case;
	for(scanf("%d", &test_case); test_case; --test_case) {
		solve();
	}

	return 0;
}
