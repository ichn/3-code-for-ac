/*
 * 缩边与缩点
 *
 * 1. 把询问边变成INF，做MST，那么不在MST中的非询问边就可以删除。称Reduction
 *
 * 2. 把询问边变成-INF，做MST，在MST中的非询问边一定在MST中，可以缩，把边权累计起来。称Contraction
 *
 * 通过这些方式（R-C-R）可以把图规模变成和(r-l+1)同阶的，保证复杂度（回忆主定理）
 * 
 * 实现方式
 *
 * 写出这道题的最大的问题就是缩图后信息的处理，如何把上一层的信息放到这一层来
 *
 * 程序框架是这样的：
 *
 * solve(l, r)
 * 如果 l=r 
 *	让修改生效，之后所有询问这条边的边权返回修改后的值
 * 拷贝图，修改不发生在分到这层的图上，边权考虑生效后的
 * 缩边
 * 缩点
 * 如果 l=r
 *	计算MST返回
 * 把缩后的图传递给下一层
 * 递归解决左
 * 递归解决右
 * */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 20000+10;
const int maxm = 50000+10;
const int maxq = 50000+10;
const int INF = 0x3f3f3f3f;

struct Edge {
	int u, v, w, id;
	bool operator < (const Edge&rhs) const {
		return w < rhs.w;
	}
} e[20][maxm], d[maxm]; // 每层的边；注意的是，在进行Re&Co操作时，把图Copy到tmp上进行，然后传给下一层
#define x first
#define y second
pair<int, int> chg[maxq];
int nCnt[20], tot, n, m, q, a[maxm], b[maxm]; // 记录每层图边数；全局边数量，表示解决某一层下边的数量；输入；每条边的实际权值，使用val[e.id]获取
LL ans[maxq];

int fa[maxn];
void clear() {
	for (int i = 1; i <= tot; ++i) {
		fa[d[i].u] = d[i].u;
		fa[d[i].v] = d[i].v;
	}
}
int findfa(int u) {
	return fa[u]==u ? u : fa[u]=findfa(fa[u]);
}
void merge(int u, int v) {
	fa[findfa(u)] = findfa(v);
} // 欢迎神犇把我卡成nlogn

void solve(int l, int r, int lvl, LL sum) {
	if (l == r)
		a[chg[l].x] = chg[l].y;
	tot = nCnt[lvl];
	int tmpT;

	//printf("%d %d %d %lld %d\n", l, r, lvl, sum, tot);
	for (int i = 1; i <= tot; ++i)
		d[i] = (Edge){e[lvl][i].u, e[lvl][i].v, a[e[lvl][i].id], e[lvl][i].id};

	if (l == r) {
		sort(d+1, d+tot+1);
		ans[l] = sum;
		clear();
		for (int i = 1; i <= tot; ++i)
			if (findfa(d[i].u) != findfa(d[i].v)) {
				ans[l] += d[i].w;
				merge(d[i].u, d[i].v);
			}
		return ;
	}

	for (int i = l; i <= r; ++i) {
		b[chg[i].x] = a[chg[i].x];
	}

	// Co
	for (int i = l; i <= r; ++i) {
		a[chg[i].x] = -INF;
	}
	for (int i = 1; i <= tot; ++i) {
		d[i].w = a[d[i].id];
	}
	clear();
	sort(d+1, d+tot+1);
	for (int i = 1; i <= tot; ++i)
		if (findfa(d[i].u) != findfa(d[i].v)) {
			merge(d[i].u, d[i].v);
			if (d[i].w != -INF)
				sum += d[i].w;
		} else d[i].w = -INF;
	clear();
	for (int i = 1; i <= tot; ++i) {
		if (d[i].w != -INF)
			merge(d[i].u, d[i].v);
	}
	for (int i = 1; i <= tot; ++i) {
		d[i].u = findfa(d[i].u);
		d[i].v = findfa(d[i].v);
	}
	tmpT = 0;
	for (int i = 1; i <= tot; ++i)
		if (d[i].u != d[i].v)
			d[++tmpT] = d[i];
	tot = tmpT;

	// Re
	for (int i = l; i <= r; ++i) {
		a[chg[i].x] = INF;
	}
	for (int i = 1; i <= tot; ++i)
		d[i].w = a[d[i].id];
	clear();
	sort(d+1, d+tot+1);
	tmpT = 0;
	for (int i = 1; i <= tot; ++i)
		if (d[i].w != INF && findfa(d[i].u) != findfa(d[i].v)) {
			merge(d[i].u, d[i].v);
			d[++tmpT] = d[i];
		} else if (d[i].w == INF) {
			d[++tmpT] = d[i];
		}
	tot = tmpT;
	
	
	for (int i = l; i <= r; ++i)
		a[chg[i].x] = b[chg[i].x];
	for (int i = 1; i <= tot; ++i)
		d[i].w = a[d[i].id];
	nCnt[lvl+1] = tot;
	for (int i = 1; i <= tot; ++i)
		e[lvl+1][i] = d[i];
	int mid((l+r)>>1);
	solve(l, mid, lvl+1, sum);
	solve(mid+1, r, lvl+1, sum);
}

int main() {
	freopen("2001.in", "r", stdin);
	freopen("2001.out", "w", stdout);

	scanf("%d %d %d", &n, &m, &q);
	nCnt[0] = m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d %d %d", &u, &v, &a[i]);
		e[0][i] = (Edge){u, v, a[i], i};
	}
	for (int i = 1; i <= q; ++i) {
		scanf("%d %d", &chg[i].x, &chg[i].y);
	}
	solve(1, q, 0, 0ll);
	for (int i = 1; i <= q; ++i) {
		printf("%lld\n", ans[i]);
	}

	return 0;
}

