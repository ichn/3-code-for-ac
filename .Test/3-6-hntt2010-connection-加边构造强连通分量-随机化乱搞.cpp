#include <bits/stdc++.h>
using namespace std;


const int maxn = 1000 + 100;
const int maxe = maxn * maxn;
struct Edge {
	int edge, head[maxn], to[maxe], next[maxe];
	Edge() {
		edge = 0;
		memset(head, -1, sizeof head);
	}
	void init() {
		edge = 0;
		memset(head, -1, sizeof head);
	}
	void addEdge(int u, int v) {
		next[edge] = head[u], to[edge] = v, head[u] = edge++;
	}
} e, E, c;



int n, m;
int pre[maxn], low[maxn], cl, bl[maxn], cnt, sta[maxn];
int top, stk[maxn];
vector<int> ele[maxn];
int in_d[maxn], out_d[maxn];

void dfs(int u) {
	int v;
	pre[u] = low[u] = ++cl;
	stk[++top] = u;
	for (int i = e.head[u]; i != -1; i = e.next[i]) {
		if (!pre[v = e.to[i]]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (!bl[v]) {
			low[u] = min(low[u], pre[v]);
		}
	}
	if (low[u] == pre[u]) {
		for (++cnt, stk[top+1] = -1; stk[top+1] != u; --top)
			bl[stk[top]] = cnt, ele[cnt].push_back(stk[top]);
		sta[cnt] = u;
	}
}

void dfs2(int u) {
	int v;
	pre[u] = low[u] = ++cl;
	stk[++top] = u;
	for (int i = E.head[u]; i != -1; i = E.next[i]) {
		if (!pre[v = E.to[i]]) {
			dfs2(v);
			low[u] = min(low[u], low[v]);
		} else if (!bl[v]) {
			low[u] = min(low[u], pre[v]);
		}
	}
	if (low[u] == pre[u]) {
		for (++cnt, stk[top+1] = -1; stk[top+1] != u; --top)
			bl[stk[top]] = cnt, ele[cnt].push_back(stk[top]);
		sta[cnt] = u;
	}
}
vector<pair<int, int> > block;
int get0(int u) {
	pre[u] = 1;
	if (in_d[u] == 0)
		return u;
	for (int i = c.head[u]; i != -1; i = c.next[i]) {
		if (pre[c.to[i]] == 0) {
			int v = get0(c.to[i]);
			if (v != 0)
				return v;
		}
	}
	return 0;
}
int get1(int u) {
	pre[u] = 2;
	if (out_d[u] == 0)
		return u;
	for (int i = c.head[u]; i != -1; i = c.next[i]) {
		if (pre[c.to[u]] == 0 || pre[c.to[u]] == 1) {
			int v = get1(c.to[i]);
			if (v != 0)
				return v;
		}
	}
	return 0;
}
void mark(int u) {
	for (int i = c.head[u]; i != -1; i = c.next[i]) {
		int v = c.to[i];
		if (pre[v] != 3) {
			pre[v] = 3;
			mark(v);
		}
	}
}
pair<int, int> get(int u) {
	int ret0 = get0(u);
	int ret1 = get1(u);
	mark(u);
	return make_pair(ret0, ret1);
}

vector<pair<int, int> > ans;
vector<int> in_d0, out_d0;
bool make_graph() {
	cl = cnt = top = 0;
	memset(bl, 0, sizeof bl);
	memset(in_d, 0, sizeof in_d);
	memset(out_d, 0, sizeof out_d);
	memset(pre, 0, sizeof pre);
	memset(sta, 0, sizeof sta);
	for (int i = 1; i <= n; ++i)
		ele[i].clear();
	block.clear();
	in_d0.clear();
	out_d0.clear();
	for (int i = 1; i <= n; ++i) {
		if (!pre[i]) {
			dfs(i);
		}
	}
	if (cnt == 1) {
		puts("0");
		exit(0);
	}
	c.init();
	E.init();

	for (int i = 1; i <= cnt; ++i) {
		int u = sta[i];
		for (int j = 0, sz = ele[i].size(); j < sz; ++j)
			for (int k = e.head[ele[i][j]]; k != -1; k = e.next[k]) {
				if (bl[e.to[k]] == i) continue;
		   		//printf("%d %d\n", sta[bl[e.to[k]]], u);
				E.addEdge(u, sta[bl[e.to[k]]]), ++in_d[sta[bl[e.to[k]]]], ++out_d[u];
				c.addEdge(u, sta[bl[e.to[k]]]), c.addEdge(sta[bl[e.to[k]]], u);
			}
	}
	memset(pre, 0, sizeof pre);
	for (int i = 1; i <= cnt; ++i) {
		int u = sta[i];
		if (!pre[u]) {
			block.push_back(get(u));
		}
	}
//	printf("%d\n", block.size());
	ans.clear();
	for (int i = 0, sz = block.size(); i < sz-1; ++i) {
		E.addEdge(block[i].second, block[i+1].first);
		ans.push_back(make_pair(block[i].second, block[i+1].first));
		++out_d[block[i].second];
		++in_d[block[i+1].first];
	}
	int in0 = 0, out0 = 0;
	for (int i = 1; i <= cnt; ++i) {
		if (out_d[sta[i]] == 0) ++out0, out_d0.push_back(sta[i]);
		if (in_d[sta[i]] == 0) ++in0, in_d0.push_back(sta[i]);
	}
	random_shuffle(out_d0.begin(), out_d0.end());
	random_shuffle(in_d0.begin(), in_d0.end());
	int i = 0, j = 0;
	while (true) {
		E.addEdge(out_d0[i], in_d0[j]);
		ans.push_back(make_pair(out_d0[i], in_d0[j]));
		++out_d[out_d0[i]];
		++in_d[in_d0[j]];
		++i, ++j;
		if (i == out0 && j == in0)
			break;
		if (i == out0 && j < in0)
			--i;
		if (j == in0 && i < out0)
			--j;
	}
	//printf("%d\n", num = min(in0, out0));
	memset(bl, 0, sizeof bl);
	memset(pre, 0, sizeof pre);
	int tmp = cnt;
	cl = cnt = top = 0;
	for (int i = 1; i <= tmp; ++i) {
		if (!pre[sta[i]]) {
			dfs2(sta[i]);
		}
	}

	//printf("%d\n", cnt);

	//printf("%d\n", (int)ans.size());
	if (cnt == 1) {
		return true;
	}
	return false;
	for (int i = 0, sz = ans.size(); i < sz; ++i)
		printf("%d %d\n", ans[i].first, ans[i].second);
}


int main() {
	freopen("connection.in", "r", stdin);
	freopen("connection.out", "w", stdout);
	//srand((int)time(NULL));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e.addEdge(u, v);
	}
	while (!make_graph()) {
	}
	//puts("");
	printf("%d\n", (int)ans.size());
	for (int i = 0, sz = ans.size(); i < sz; ++i)
		printf("%d %d\n", ans[i].first, ans[i].second);


	return 0;
}


